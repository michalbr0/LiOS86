#include "memory_manager.hpp"

#include <bit>
#include <new>
#include "shell.hpp"

namespace LiOS86 {

    namespace {

        // Memory map is loaded by the detect_memory routine in loader.asm
        // Layout of the memory map:
        // at the address MEMORY_MAP_ADDRESS there is an object of type MemoryMapSizeType denoting the number of entries
        // following that there are 24-byte entries of type MemoryMapEntry with no additional padding
        using MemoryMapSizeType = uint32_t;
        struct MemoryMapEntry {
            uint64_t base;
            uint64_t region_length;
            uint32_t region_type;
            uint32_t extended_attributes;
        } __attribute__((packed));
        static_assert( sizeof(MemoryMapEntry) == 24, "MemoryMapEntry has incorrect size" );
        constexpr auto MEMORY_MAP_ADDRESS = 0x1000;

    }

    MemoryManager::MemoryManager() {
        const auto memory_map_size = *reinterpret_cast<const MemoryMapSizeType*>(MEMORY_MAP_ADDRESS);
        for(uint32_t i=0; i<memory_map_size; ++i) {
            const auto entry = reinterpret_cast<const MemoryMapEntry*>(MEMORY_MAP_ADDRESS + sizeof(MemoryMapSizeType) + i*sizeof(MemoryMapEntry));

            if(!(entry->extended_attributes & 1)) continue; // entry ignored

            const auto region_type = [entry]() {
                if(entry->extended_attributes & 0b10) {
                    return MemoryRegionType::NON_VOLATILE;
                }
                switch(entry->region_type) {
                    case 1: return MemoryRegionType::USABLE;
                    case 2: return MemoryRegionType::RESERVED;
                    case 3: return MemoryRegionType::ACPI_RECLAIMABLE;
                    case 4: return MemoryRegionType::ACPI_NVS;
                    case 5: return MemoryRegionType::BAD_MEMORY;
                    default: return MemoryRegionType::INVALID;
                }
            }();

            memory_regions.emplace_back(static_cast<uint32_t>(entry->base), static_cast<uint32_t>(entry->region_length), region_type);
        }

        const MemoryRegion* heap_region = nullptr;
        for(const auto& entry : memory_regions) {
            if(entry.type != MemoryRegionType::USABLE) continue;
            if(heap_region == nullptr || entry.length > heap_region->length) {
                heap_region = &entry;
            }
        }
        kernel_heap_block_list_head = new (reinterpret_cast<void*>(heap_region->base)) KernelFreeHeapBlockHeader{
                                        nullptr, heap_region->length - sizeof(KernelAllocatedHeapBlockHeader)};
    }

    auto MemoryManager::print_memory_map_impl() const -> void {
        Shell::print("|-------BASE-------|------LENGTH------|-------TYPE-------|\n");
        for(const auto& entry : memory_regions) {
            Shell::print("|    ");
            Shell::printhex(entry.base);
            Shell::print("    |    ");
            Shell::printhex(entry.length);
            Shell::print("    |");
            switch(entry.type) {
                case MemoryRegionType::USABLE:
                    Shell::print("      USABLE      ");
                    break;
                case MemoryRegionType::RESERVED:
                    Shell::print("     RESERVED     ");
                    break;
                case MemoryRegionType::ACPI_RECLAIMABLE:
                    Shell::print(" ACPI RECLAIMABLE ");
                    break;
                case MemoryRegionType::ACPI_NVS:
                    Shell::print("     ACPI NVS     ");
                    break;
                case MemoryRegionType::BAD_MEMORY:
                    Shell::print("    BAD MEMORY    ");
                    break;
                case MemoryRegionType::NON_VOLATILE:
                    Shell::print("   NON-VOLATILE   ");
                    break;
                case MemoryRegionType::INVALID:
                    Shell::print("      INVALID     ");
                    break;
                default:
                    break;
            }
            Shell::print("|\n");
        }
        Shell::print("|------------------|------------------|------------------|\n");
    }

}
