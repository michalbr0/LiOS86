#pragma once

#include <stdint.h>
#include <type_traits>
#include "utils/static_vector.hpp"

namespace LiOS86 {

    class KernelFreeHeapBlockHeader;

    class MemoryManager {
        public:
            MemoryManager(const MemoryManager&) = delete;
            MemoryManager& operator=(const MemoryManager&) = delete;
            MemoryManager(MemoryManager&&) = delete;
            MemoryManager& operator=(MemoryManager&&) = delete;

            static auto& instance() {
                static MemoryManager memory_manager;
                return memory_manager;
            }

            static auto get_kernel_heap_block_list_head() {
                return instance().kernel_heap_block_list_head;
            }
            static auto set_kernel_heap_block_list_head(KernelFreeHeapBlockHeader* header) -> void {
                instance().kernel_heap_block_list_head = header;
            }

            static auto print_memory_map() -> void {
                instance().print_memory_map_impl();
            }

        private:
            MemoryManager();

            auto print_memory_map_impl() const -> void;

            enum class MemoryRegionType : uint8_t {
                USABLE, RESERVED, ACPI_RECLAIMABLE, ACPI_NVS, BAD_MEMORY, NON_VOLATILE, INVALID
            };
            struct MemoryRegion {
                uint32_t base;
                uint32_t length;
                MemoryRegionType type;
            };
            StaticVector<MemoryRegion, 32> memory_regions{};

            KernelFreeHeapBlockHeader* kernel_heap_block_list_head = nullptr;
    };

    class KernelFreeHeapBlockHeader {
        public:
            KernelFreeHeapBlockHeader(KernelFreeHeapBlockHeader* next, std::size_t size)
                : next_free_block{next}, block_size{size} { }

            KernelFreeHeapBlockHeader* next_free_block;
            std::size_t block_size;
    };
    // Standard-layout assertion so that a conversion to a pointer to the first member is allowed
    static_assert( std::is_standard_layout_v<KernelFreeHeapBlockHeader>, "KernelFreeHeapBlockHeader has to be standard-layout" );

    class KernelAllocatedHeapBlockHeader {
        public:
            explicit KernelAllocatedHeapBlockHeader(std::size_t size) : block_size{size} { }

            auto get_data_ptr() const -> std::byte* {
                return const_cast<std::byte*>(reinterpret_cast<const std::byte*>(this) + sizeof(KernelAllocatedHeapBlockHeader));
            }

            std::size_t block_size;
    };
    // Standard-layout assertion so that a conversion to a pointer to the first member is allowed
    static_assert( std::is_standard_layout_v<KernelAllocatedHeapBlockHeader>, "KernelAllocatedHeapBlockHeader has to be standard-layout" );

}
