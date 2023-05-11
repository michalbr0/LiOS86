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

SRCS_KERNEL := $(shell find $(SRC_DIR_KERNEL) -name '*.cpp' -or -name '*.asm')
OBJS_KERNEL := $(patsubst $(SRC_DIR_KERNEL)%,$(BUILD_DIR_KERNEL)%.o,$(SRCS_KERNEL))
BINS_BOOT := $(addprefix $(BUILD_DIR_BOOT)/,mbr_part1.bin mbr_part2.bin vbr.bin loader.bin)

CRTI_OBJ := $(BUILD_DIR)/crti.asm.o
CRTBEGIN_OBJ := $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)
CRTN_OBJ := $(BUILD_DIR)/crtn.asm.o

OBJ_KERNEL_LINK_LIST := $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS_KERNEL) $(CRTEND_OBJ) $(CRTN_OBJ)

.PHONY: run
run: all
	qemu-system-x86_64 -drive format=raw,file=$(TARGET_IMG)

.PHONY: all
all: $(TARGET_IMG)

$(TARGET_IMG): $(BINS_BOOT) $(BUILD_DIR_KERNEL)/kernel.bin
	cp $(BUILD_DIR_BOOT)/mbr_part1.bin $(TARGET_IMG)
	dd bs=1 count=408 seek=32 conv=notrunc if=$(BUILD_DIR_BOOT)/mbr_part2.bin of=$(TARGET_IMG)
	dd seek=63 conv=notrunc if=$(BUILD_DIR_BOOT)/vbr.bin of=$(TARGET_IMG)
	dd seek=64 conv=notrunc if=$(BUILD_DIR_BOOT)/loader.bin of=$(TARGET_IMG)
	dd seek=65 count=48 conv=notrunc if=$(BUILD_DIR_KERNEL)/kernel.bin of=$(TARGET_IMG)

$(BUILD_DIR_KERNEL)/kernel.bin: $(BUILD_DIR_KERNEL)/kernel.elf
	objcopy -O binary $< $@
$(BUILD_DIR_KERNEL)/kernel.elf: $(OBJ_KERNEL_LINK_LIST)
	$(LD) $(LDFLAGS) -T link.ld -o $@ $(OBJ_KERNEL_LINK_LIST)

$(BUILD_DIR_KERNEL)/%.cpp.o: $(SRC_DIR_KERNEL)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(BUILD_DIR_KERNEL)/%.asm.o: $(SRC_DIR_KERNEL)/%.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) -f elf32 $< -o $@

$(BUILD_DIR_BOOT)/%.bin: $(SRC_DIR_BOOT)/%.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) -f bin $< -o $@

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
