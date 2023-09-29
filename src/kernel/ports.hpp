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
        VGA_REGISTER_DATA_3D5 = 0x3d5,

        ATA_PRIMARY_DATA_REG = 0x1f0,
        ATA_PRIMARY_ERROR_REG = ATA_PRIMARY_DATA_REG+1,
        ATA_PRIMARY_FEATURES_REG = ATA_PRIMARY_DATA_REG+1,
        ATA_PRIMARY_SECTOR_COUNT_REG = ATA_PRIMARY_DATA_REG+2,
        ATA_PRIMARY_LBA_LO = ATA_PRIMARY_DATA_REG+3,
        ATA_PRIMARY_LBA_MID = ATA_PRIMARY_DATA_REG+4,
        ATA_PRIMARY_LBA_HI = ATA_PRIMARY_DATA_REG+5,
        ATA_PRIMARY_DRIVE_REG = ATA_PRIMARY_DATA_REG+6,
        ATA_PRIMARY_STATUS_REG = ATA_PRIMARY_DATA_REG+7,
        ATA_PRIMARY_COMMAND_REG = ATA_PRIMARY_DATA_REG+7,
        ATA_PRIMARY_ALTERNATE_STATUS_REG = 0x3f6,
        ATA_PRIMARY_DEVICE_CONTROL_REG = ATA_PRIMARY_ALTERNATE_STATUS_REG,
        ATA_PRIMARY_DRIVE_ADDRESS_REG = ATA_PRIMARY_ALTERNATE_STATUS_REG+1
    };

    static inline auto outb(Port port, uint8_t val) -> void {
        __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(static_cast<uint16_t>(port)));
    }

    static inline auto inb(Port port) -> uint8_t {
        uint8_t ret;
        __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(static_cast<uint16_t>(port)));
        return ret;
    }

    static inline auto outw(Port port, uint16_t val) -> void {
        __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(static_cast<uint16_t>(port)));
    }

    static inline auto inw(Port port) -> uint16_t {
        uint16_t ret;
        __asm__ volatile ("inw %1, %0" : "=a"(ret) : "Nd"(static_cast<uint16_t>(port)));
        return ret;
    }

    static inline auto io_wait() -> void {
        outb(static_cast<Port>(0x80), 0);
    }
    
}
