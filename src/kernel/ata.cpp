#include "ata.hpp"

#include "ports.hpp"

namespace LiOS86 {

    namespace {
        class StatusRegisterValue {
            public:
                constexpr StatusRegisterValue(uint8_t val) : value{val} { }
                [[nodiscard]] constexpr auto error() const -> bool {
                    return value & 0x01;
                }
                [[nodiscard]] constexpr auto dataTransferRequested() const -> bool {
                    return value & 0x08;
                }
                [[nodiscard]] constexpr auto deviceReady() const -> bool {
                    return value & 0x40;
                }
                [[nodiscard]] constexpr auto busy() const -> bool {
                    return value & 0x80;
                }
            private:
                uint8_t value;
        };
        auto checkStatus() -> StatusRegisterValue {
            return inb(Port::ATA_PRIMARY_STATUS_REG);
        }   
    }

    auto readSectors(uint32_t logicalBlockAddress, uint8_t numberOfSectors) -> std::expected<std::array<uint8_t, 512>, int> {
        while(checkStatus().busy()) { }
        
        constexpr uint8_t slaveBit = 0;
        outb(Port::ATA_PRIMARY_FEATURES_REG, 0x00);
        outb(Port::ATA_PRIMARY_SECTOR_COUNT_REG, numberOfSectors);
        outb(Port::ATA_PRIMARY_LBA_LO, static_cast<uint8_t>(logicalBlockAddress));
        outb(Port::ATA_PRIMARY_LBA_MID, static_cast<uint8_t>(logicalBlockAddress >> 8));
        outb(Port::ATA_PRIMARY_LBA_HI, static_cast<uint8_t>(logicalBlockAddress >> 16));
        outb(Port::ATA_PRIMARY_DRIVE_REG, 0xE0 | (slaveBit << 4) | ((logicalBlockAddress >> 24) & 0x0f));
        outb(Port::ATA_PRIMARY_COMMAND_REG, 0x20);

        while(true) {
            auto status = checkStatus();
            if(status.error()) return std::unexpected<int>{-1};
            if(status.dataTransferRequested()) break;
        }

        std::expected<std::array<uint8_t, 512>, int> result;
        for(int i = 0; i < 256; ++i) {
            auto word = inw(Port::ATA_PRIMARY_DATA_REG);
            (*result)[2*i] = static_cast<uint8_t>(word);
            (*result)[2*i + 1] = static_cast<uint8_t>(word >> 8);
        }
        return result;
    }  

}
