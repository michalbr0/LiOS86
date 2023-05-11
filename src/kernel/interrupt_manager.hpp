#pragma once

#include <stdint.h>

extern "C" void general_interrupt_handler(uint32_t interrupt_number);

namespace LiOS86 {

    class InterruptManager {
        public:
            InterruptManager(const InterruptManager&) = delete;
            InterruptManager& operator=(const InterruptManager&) = delete;
            InterruptManager(InterruptManager&&) = delete;
            InterruptManager& operator=(InterruptManager&&) = delete;

            static auto& instance() {
                static InterruptManager interrupt_manager;
                return interrupt_manager;
            }

            using FunctionPointer = void (*)();
            static auto set_interrupt_handler(uint8_t interrupt_number, FunctionPointer handler) -> void {
                instance().set_interrupt_handler_impl(interrupt_number, handler);
            }

        private:
            InterruptManager();

            auto set_interrupt_handler_impl(uint8_t interrupt_number, FunctionPointer handler) -> void;

            FunctionPointer interrupt_handlers[256]{};

            enum class GateType : uint8_t { INTERRUPT_GATE = 0x8e, TRAP_GATE = 0x8f };
            class IdtEntry {
                public:
                    auto set(FunctionPointer isr, GateType gate_type) volatile -> void {
                        isr_low = reinterpret_cast<uint32_t>(isr) & 0xffff;
                        attributes = static_cast<uint8_t>(gate_type);
                        isr_high = static_cast<uint16_t>(reinterpret_cast<uint32_t>(isr) >> 16);
                    }
                private:
                    uint16_t isr_low = 0;
                    uint16_t kernel_code_selector = 0x08;
                    uint8_t reserved = 0;
                    uint8_t attributes = 0;
                    uint16_t isr_high = 0;
            } __attribute__((packed));
            volatile IdtEntry idt_entries[256] __attribute__((aligned(0x10)));

            static_assert( sizeof(IdtEntry) == 8, "IdtEntry has incorrect size" );

            class IdtReg {
                public:
                    explicit IdtReg(const volatile IdtEntry idt_entries[]) : base{reinterpret_cast<uint32_t>(&idt_entries[0])} { }
                private:
                    uint16_t limit = sizeof(IdtEntry)*256 - 1;
	                uint32_t base;
            } __attribute__((packed));
            IdtReg idtr;

            static_assert( sizeof(IdtReg) == 6, "IdtReg has incorrect size" );

            friend void ::general_interrupt_handler(uint32_t interrupt_number);
    };
    
}
