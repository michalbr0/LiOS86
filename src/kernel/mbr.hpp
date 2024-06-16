#pragma once

#include <stdint.h>

#include "utils/data_manipulation.hpp"
#include "utils/disk_buffer.hpp"
#include "xstd/utility.hpp"

namespace LiOS86 {

    class MBRHandle : ReadonlyDiskBuffer<1> {
        public:
            MBRHandle() : ReadonlyDiskBuffer<1>(0) { }

            class PartitionTableEntryHandle {
                public:
                    explicit PartitionTableEntryHandle(const uint8_t* partitionTableEntryPtr) :
                        entryPtr{partitionTableEntryPtr} { }

                    auto isActive() const -> bool {
                        return entryPtr[0] == 0x80;
                    }

                    auto getStartSector() const -> uint32_t {
                        return readFromMemoryAndPun<uint32_t>(entryPtr, 8);
                    }

                    auto getSizeInSectors() const -> uint32_t {
                        return readFromMemoryAndPun<uint32_t>(entryPtr, 12);
                    }
                
                private:
                    const uint8_t* entryPtr;
            };
            enum class Partition { Partition1 = 0, Partition2 = 1, Partition3 = 2, Partition4 = 3 };

            auto getPartitionTableEntryHandle(Partition partition) const -> PartitionTableEntryHandle {
                static constexpr auto FIRST_ENTRY_OFFSET = 446;
                static constexpr auto ENTRY_SIZE = 16;
                const auto offset = FIRST_ENTRY_OFFSET + static_cast<int>(partition) * ENTRY_SIZE;
                return PartitionTableEntryHandle(bufferData() + offset);
            }

            auto getActivePartitionTableEntryHandle() const -> PartitionTableEntryHandle {
                for(int i = 0; i < 4; ++i) {
                    const auto partition = static_cast<Partition>(i);
                    const auto entryHandle = getPartitionTableEntryHandle(partition);
                    if(entryHandle.isActive()) return entryHandle;
                }
                xstd::unreachable();
            }
    };

}
