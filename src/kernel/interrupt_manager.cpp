#include "interrupt_manager.hpp"

#include "ports.hpp"
#include "shell.hpp"

static constexpr uint8_t EXCEPTIONS_OFFSET = 0x00;
static constexpr uint8_t EXCEPTIONS_NUMBER = 32;
static constexpr uint8_t PIC1_VECTOR_OFFSET = 0x20;
static constexpr uint8_t PIC1_VECTOR_NUMBER = 8;
static constexpr uint8_t PIC2_VECTOR_OFFSET = 0x28;
static constexpr uint8_t PIC2_VECTOR_NUMBER = 8;

extern void (*isr_stub_table[])();

namespace LiOS86 {

	namespace {
		auto PIC_remap(uint8_t pic1_vector_offset, uint8_t pic2_vector_offset) -> void {

			constexpr uint8_t ICW1_ICW4 = 0x01;								// Initialization Command Word ICW4 needed
			constexpr uint8_t ICW1_INIT = 0x10;					
			constexpr uint8_t ICW4_8086 = 0x01;								// 8086/88 (MCS-80/85) mode

			const uint8_t pic1_mask = inb(Port::PIC1_DATA);
			const uint8_t pic2_mask = inb(Port::PIC2_DATA);

			outb(Port::PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  				// starts the initialization sequence (in cascade mode)
			io_wait();
			outb(Port::PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
			io_wait();
			outb(Port::PIC1_DATA, pic1_vector_offset);
			io_wait();
			outb(Port::PIC2_DATA, pic2_vector_offset);
			io_wait();
			outb(Port::PIC1_DATA, 4);                       				// ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
			io_wait();
			outb(Port::PIC2_DATA, 2);                       				// ICW3: tell Slave PIC its cascade identity (0000 0010)
			io_wait();

			outb(Port::PIC1_DATA, ICW4_8086);
			io_wait();
			outb(Port::PIC2_DATA, ICW4_8086);
			io_wait();

			outb(Port::PIC1_DATA, pic1_mask);
			outb(Port::PIC2_DATA, pic2_mask);
		}

		auto mask_all_pic_interrupts() -> void {
			outb(Port::PIC1_DATA, 0xff);
    		outb(Port::PIC2_DATA, 0xff);
		}

		auto mask_pic1_interrupt(uint8_t interrupt_number) -> void {
			uint8_t mask = inb(Port::PIC1_DATA);
			mask |= static_cast<uint8_t>(1 << (interrupt_number - PIC1_VECTOR_OFFSET));
			outb(Port::PIC1_DATA, mask);
		}

		auto unmask_pic1_interrupt(uint8_t interrupt_number) -> void {
			uint8_t mask = inb(Port::PIC1_DATA);
			mask &= ~static_cast<uint8_t>(1 << (interrupt_number - PIC1_VECTOR_OFFSET));
			outb(Port::PIC1_DATA, mask);
		}

		auto mask_pic2_interrupt(uint8_t interrupt_number) -> void {
			uint8_t mask = inb(Port::PIC2_DATA);
			mask |= static_cast<uint8_t>(1 << (interrupt_number - PIC1_VECTOR_OFFSET));
			outb(Port::PIC2_DATA, mask);
		}

		auto unmask_pic2_interrupt(uint8_t interrupt_number) -> void {
			uint8_t mask = inb(Port::PIC2_DATA);
			mask &= ~static_cast<uint8_t>(1 << (interrupt_number - PIC1_VECTOR_OFFSET));
			outb(Port::PIC2_DATA, mask);
		}
	}

	InterruptManager::InterruptManager() : idt_entries{}, idtr{idt_entries} {

		PIC_remap(PIC1_VECTOR_OFFSET, PIC2_VECTOR_OFFSET);
		mask_all_pic_interrupts();

		for(std::size_t i = EXCEPTIONS_OFFSET; i < EXCEPTIONS_OFFSET+EXCEPTIONS_NUMBER; ++i) {
			idt_entries[i].set(isr_stub_table[i], GateType::TRAP_GATE);
		}
		for(std::size_t i = PIC1_VECTOR_OFFSET; i < PIC1_VECTOR_OFFSET+PIC1_VECTOR_NUMBER; ++i) {
			idt_entries[i].set(isr_stub_table[i], GateType::INTERRUPT_GATE);
		}
		for(std::size_t i = PIC2_VECTOR_OFFSET; i < PIC2_VECTOR_OFFSET+PIC2_VECTOR_NUMBER; ++i) {
			idt_entries[i].set(isr_stub_table[i], GateType::INTERRUPT_GATE);
		}

		__asm__ volatile ("lidt %0" : : "m"(idtr));
		__asm__ volatile ("sti");
	}

	auto InterruptManager::set_interrupt_handler_impl(uint8_t interrupt_number, FunctionPointer handler) -> void {
		auto old_handler = interrupt_handlers[interrupt_number];
		interrupt_handlers[interrupt_number] = handler;
		
		if(interrupt_number >= PIC1_VECTOR_OFFSET && interrupt_number < PIC1_VECTOR_OFFSET+PIC1_VECTOR_NUMBER) {
			if(old_handler == nullptr && handler != nullptr) {
				unmask_pic1_interrupt(interrupt_number);
			} else if(old_handler != nullptr && handler == nullptr) {
				mask_pic1_interrupt(interrupt_number);
			}
		} else if(interrupt_number >= PIC2_VECTOR_OFFSET && interrupt_number < PIC2_VECTOR_OFFSET+PIC2_VECTOR_NUMBER) {
			if(old_handler == nullptr && handler != nullptr) {
				unmask_pic2_interrupt(interrupt_number);
			} else if(old_handler != nullptr && handler == nullptr) {
				mask_pic2_interrupt(interrupt_number);
			}
		}
	}
	
}

extern "C" void general_interrupt_handler(uint32_t interrupt_number) {
	auto handler = LiOS86::InterruptManager::instance().interrupt_handlers[interrupt_number];
	if(handler != nullptr) {
		handler();
	}

	if(interrupt_number >= PIC1_VECTOR_OFFSET && interrupt_number < PIC1_VECTOR_OFFSET+PIC1_VECTOR_NUMBER) {
		LiOS86::outb(LiOS86::Port::PIC1_COMMAND, 0x20);
	}
	if(interrupt_number >= PIC2_VECTOR_OFFSET && interrupt_number < PIC2_VECTOR_OFFSET+PIC2_VECTOR_NUMBER) {
		LiOS86::outb(LiOS86::Port::PIC1_COMMAND, 0x20);
		LiOS86::outb(LiOS86::Port::PIC2_COMMAND, 0x20);
	}

	if(interrupt_number >= EXCEPTIONS_OFFSET && interrupt_number < EXCEPTIONS_OFFSET+EXCEPTIONS_NUMBER) {
		LiOS86::Shell::print("Exception! Halting.");
		__asm__ volatile ("cli");
		__asm__ volatile ("hlt");
	}
}
