#pragma once

#include <stdint.h>

namespace LiOS86 {

    enum class Port : uint16_t {
        PIC1_COMMAND = 0x20,
        PIC1_DATA = PIC1_COMMAND+1,
        PIC2_COMMAND = 0xa0,
        PIC2_DATA = PIC2_COMMAND+1,
        PS2_DATA = 0x60,
        VGA_REGISTER_INDEX_3D4 = 0x3d4,
        VGA_REGISTER_DATA_3D5 = 0x3d5
    };

    static inline auto outb(Port port, uint8_t val) -> void {
        __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(static_cast<uint16_t>(port)));
    }

    static inline auto inb(Port port) -> uint8_t {
        uint8_t ret;
        __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(static_cast<uint16_t>(port)));
        return ret;
    }

    static inline auto io_wait() -> void {
        outb(static_cast<Port>(0x80), 0);
    }
    
}
