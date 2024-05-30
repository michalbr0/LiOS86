#pragma once

#include <stdint.h>

#include "utils/data_manipulation.hpp"
#include "utils/disk_buffer.hpp"
#include "xstd/expected.hpp"
#include "xstd/utility.hpp"

namespace LiOS86 {

    class BPBHandle : ReadonlyDiskBuffer<1> {
        public:
            BPBHandle(std::size_t startingSectorNumber) : ReadonlyDiskBuffer<1>(startingSectorNumber) { }

            auto getBytesPerSector() const -> uint16_t {
                return readFromMemoryAndPun<uint16_t>(bufferData(), 11);
            }

            auto getSectorsPerCluster() const -> uint8_t {
                return readFromMemoryAndPun<uint8_t>(bufferData(), 13);
            }

            auto getReservedSectorCount() const -> uint16_t {
                return readFromMemoryAndPun<uint16_t>(bufferData(), 14);
            }

            auto getNumberOfFATs() const -> uint8_t {
                return readFromMemoryAndPun<uint8_t>(bufferData(), 16);
            }

            auto getNumberOfSectorsInVolume() const -> uint32_t {
                return readFromMemoryAndPun<uint32_t>(bufferData(), 32);
            }

            auto getFATSizeInSectors() const -> uint32_t {
                return readFromMemoryAndPun<uint32_t>(bufferData(), 36);
            }

            auto isFATMirrored() const -> bool {
                const auto flags = readFromMemoryAndPun<uint16_t>(bufferData(), 40);
                return (flags & (1 << 7)) == 0;
            }

            enum class InvalidActiveFATEntry : uint8_t { MIRRORING_MODE };
            auto getActiveFAT() const -> xstd::expected<uint8_t, InvalidActiveFATEntry> {
                if(isFATMirrored()) return xstd::unexpected(InvalidActiveFATEntry::MIRRORING_MODE);
                const auto flags = readFromMemoryAndPun<uint16_t>(bufferData(), 40);
                return static_cast<uint8_t>(flags & 0b1111);
            }

            auto getFirstActiveFAT() const -> uint8_t {
                const auto result = getActiveFAT();
                if(!result) return 0;
                return *result;
            }

            auto getFATOffsetInSectors(uint8_t fatNumber) const -> uint32_t {
                return getReservedSectorCount() + fatNumber * getFATSizeInSectors();
            }

            auto getFirstActiveFATOffsetInSectors() const -> uint32_t {
                return getFATOffsetInSectors(getFirstActiveFAT());
            }

            auto getRootDirectoryStartingCluster() const -> uint32_t {
                return readFromMemoryAndPun<uint32_t>(bufferData(), 44);
            }

            auto getFSInfoSectorNumber() const -> uint16_t {
                return readFromMemoryAndPun<uint16_t>(bufferData(), 48);
            }
            
            auto getBackupBootSectorNumber() const -> uint16_t {
                return readFromMemoryAndPun<uint16_t>(bufferData(), 50);
            }

            auto getDataSectionOffsetInSectors() const -> uint32_t {
                return getReservedSectorCount() + getNumberOfFATs() * getFATSizeInSectors();
            }
    };

}
