TARGET_IMG := hd.img

BUILD_DIR := ./build
SRC_DIR := ./src
BUILD_DIR_KERNEL := $(BUILD_DIR)/kernel
SRC_DIR_KERNEL := $(SRC_DIR)/kernel
BUILD_DIR_BOOT := $(BUILD_DIR)/boot
SRC_DIR_BOOT := $(SRC_DIR)/boot

ASM := nasm
ASMFLAGS := -Wall -Werror
CXX := i386-elf-g++
CXXFLAGS := -std=c++20 -O3 -ffreestanding -fno-exceptions -fno-rtti -fstrict-enums -pedantic-errors -Werror -Wall -Wextra \
			-Wctor-dtor-privacy -Wnon-virtual-dtor -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual \
			-Wno-pmf-conversions -Wsign-promo -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wunused \
			-Wfloat-equal -Wundef -Wshadow -Wunsafe-loop-optimizations -Wcast-qual -Wcast-align -Wconversion -Wlogical-op \
			-Wmissing-noreturn -Wmissing-format-attribute -Wredundant-decls -Wunreachable-code -Winline -fno-threadsafe-statics
LD := i386-elf-ld
LDFLAGS := -O3 -nostdlib 

SRCS_BOOT := $(shell find $(SRC_DIR_BOOT) -name '*.asm')
BINS_BOOT := $(patsubst $(SRC_DIR_BOOT)%,$(BUILD_DIR_BOOT)%.bin,$(SRCS_BOOT))
SRCS_LOADER_STAGE_2 := $(shell find $(SRC_DIR_KERNEL)/loader -name '*.cpp' -or -name '*.asm') $(addprefix $(SRC_DIR_KERNEL)/,ata.cpp xstd/cstring.cpp)
OBJS_LOADER_STAGE_2 := $(patsubst $(SRC_DIR_KERNEL)%,$(BUILD_DIR_KERNEL)%.o,$(SRCS_LOADER_STAGE_2))
SRCS_KERNEL_ALL = $(shell find $(SRC_DIR_KERNEL) -name '*.cpp' -or -name '*.asm')
SRCS_KERNEL := $(filter-out $(shell find $(SRC_DIR_KERNEL)/loader -name '*.cpp' -or -name '*.asm'), $(SRCS_KERNEL_ALL))
OBJS_KERNEL := $(patsubst $(SRC_DIR_KERNEL)%,$(BUILD_DIR_KERNEL)%.o,$(SRCS_KERNEL))

CRTI_OBJ := $(BUILD_DIR)/crti.asm.o
CRTBEGIN_OBJ := $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)
CRTN_OBJ := $(BUILD_DIR)/crtn.asm.o

OBJ_KERNEL_LINK_LIST := $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS_KERNEL) $(CRTEND_OBJ) $(CRTN_OBJ)
OBJ_LOADER_STAGE2_LINK_LIST := $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS_LOADER_STAGE_2) $(CRTEND_OBJ) $(CRTN_OBJ)

.PHONY: run
run: all
	qemu-system-x86_64 -drive format=raw,file=$(TARGET_IMG)

.PHONY: all
all: $(TARGET_IMG)

$(TARGET_IMG): $(BINS_BOOT) $(BUILD_DIR)/kloader.bin $(BUILD_DIR_KERNEL)/kernel.bin
	./create_empty_img.sh
	dd bs=1 count=440 conv=notrunc if=$(BUILD_DIR_BOOT)/mbr_part1.asm.bin of=$(TARGET_IMG)
	dd bs=1 count=408 seek=32 conv=notrunc if=$(BUILD_DIR_BOOT)/mbr_part2.asm.bin of=$(TARGET_IMG)
	dd bs=1 count=420 seek=1048666 conv=notrunc if=$(BUILD_DIR_BOOT)/vbr.asm.bin of=$(TARGET_IMG)
	dd bs=1 count=420 seek=1051738 conv=notrunc if=$(BUILD_DIR_BOOT)/vbr.asm.bin of=$(TARGET_IMG)
	./cp_to_img.sh $(BUILD_DIR)/kloader.bin $(TARGET_IMG)
	./cp_to_img.sh $(BUILD_DIR_KERNEL)/kernel.bin $(TARGET_IMG)

$(BUILD_DIR)/kloader.bin: $(BUILD_DIR_BOOT)/loader.asm.bin $(BUILD_DIR_KERNEL)/loader_stage2.bin
	cp $(BUILD_DIR_BOOT)/loader.asm.bin $@
	cat $(BUILD_DIR_KERNEL)/loader_stage2.bin >> $@
	@filesize=$$(stat -c%s "$@") && \
	if [ $$filesize -gt 25088 ]; then \
	    echo "Error: $@ exceeds 25088 bytes (size is $$filesize bytes). Aborting."; \
	    exit 1; \
	fi
	truncate -s 25088 $@

$(BUILD_DIR_KERNEL)/kernel.bin: $(BUILD_DIR_KERNEL)/kernel.elf
	objcopy -O binary $< $@
$(BUILD_DIR_KERNEL)/kernel.elf: $(OBJ_KERNEL_LINK_LIST)
	$(LD) $(LDFLAGS) -T link.ld -o $@ $(OBJ_KERNEL_LINK_LIST)

$(BUILD_DIR_KERNEL)/loader_stage2.bin: $(BUILD_DIR_KERNEL)/loader_stage2.elf
	objcopy -O binary $< $@
$(BUILD_DIR_KERNEL)/loader_stage2.elf: $(OBJ_LOADER_STAGE2_LINK_LIST)
	$(LD) $(LDFLAGS) -T $(SRC_DIR_KERNEL)/loader/loader_stage2_link.ld -o $@ $(OBJ_LOADER_STAGE2_LINK_LIST)

$(BUILD_DIR_KERNEL)/%.cpp.o: $(SRC_DIR_KERNEL)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(BUILD_DIR_KERNEL)/%.asm.o: $(SRC_DIR_KERNEL)/%.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) -f elf32 $< -o $@

# .asm files assembled into flat raw binaries
$(BUILD_DIR_BOOT)/%.asm.bin: $(SRC_DIR_BOOT)/%.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) -f bin $< -o $@

# CRT files
$(BUILD_DIR)/crti.asm.o: $(SRC_DIR)/crti.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) -f elf32 $< -o $@
$(BUILD_DIR)/crtn.asm.o: $(SRC_DIR)/crtn.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) -f elf32 $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET_IMG)
	rm -rf $(BUILD_DIR)
