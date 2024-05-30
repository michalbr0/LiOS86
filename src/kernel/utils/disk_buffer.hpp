#pragma once

#include <cstddef>

#include "../xstd/array.hpp"
#include "../xstd/cstring.hpp"
#include "../ata.hpp"

namespace LiOS86 {

    constexpr std::size_t DEFAULT_SECTOR_SIZE = 512;

    template<bool writeable, std::size_t numberOfSectors, std::size_t sectorSize = DEFAULT_SECTOR_SIZE>
    class DiskBuffer {
        public:
            explicit DiskBuffer(std::size_t startingSectorNumber) : sectorNumber{startingSectorNumber} {
                reload();
            }

            auto reload() -> void;

        protected:
            auto bufferData() const -> const uint8_t* {
                return buffer.data();
            }

        private:
            xstd::array<uint8_t, numberOfSectors * sectorSize> buffer{};
            std::size_t sectorNumber;
            bool dirty{false};
    };

    template<bool writeable, std::size_t numberOfSectors, std::size_t sectorSize>
    auto DiskBuffer<writeable, numberOfSectors, sectorSize>::reload() -> void {
        for(std::size_t i = 0; i < numberOfSectors; ++i) {
            const auto sector = readSectors(sectorNumber + i, 1);
            if(!sector) {
                // TODO error handling
                while(true) { }
            }
            xstd::memcpy(buffer.data() + i * sectorSize, (*sector).data(), sectorSize);
        }
        dirty = false;
    }

    template<std::size_t numberOfSectors, std::size_t sectorSize = DEFAULT_SECTOR_SIZE>
    using ReadonlyDiskBuffer = DiskBuffer<false, numberOfSectors, sectorSize>;

    template<std::size_t numberOfSectors, std::size_t sectorSize = DEFAULT_SECTOR_SIZE>
    using ReadWriteDiskBuffer = DiskBuffer<true, numberOfSectors, sectorSize>;

}
