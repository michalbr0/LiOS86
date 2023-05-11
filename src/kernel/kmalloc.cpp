#include "kmalloc.hpp"

#include <new>
#include "memory_manager.hpp"

namespace LiOS86 {

    auto kmalloc(std::size_t size) -> void* {
        if(size < 4) {
            size = 4;
        } else {
            const auto remainder = size % 4;
            size -= remainder;
            if(remainder > 0) size += 4;
        }
        const std::size_t total_size = size + sizeof(KernelAllocatedHeapBlockHeader);

        auto block_header = MemoryManager::get_kernel_heap_block_list_head();
        while(block_header) {
            if(block_header->block_size >= total_size) {
                const auto block_header_copy = *block_header;
                const auto allocated_block_header = new (block_header) KernelAllocatedHeapBlockHeader{size};
                const auto allocated_ptr = allocated_block_header->get_data_ptr();
                if(block_header_copy.block_size - total_size > 0) {
                    const auto remaining_free_block = new (reinterpret_cast<std::byte*>(allocated_ptr) + size) KernelFreeHeapBlockHeader{
                                                    block_header_copy.next_free_block, block_header_copy.block_size - total_size};
                    MemoryManager::set_kernel_heap_block_list_head(remaining_free_block);
                } else {
                    MemoryManager::set_kernel_heap_block_list_head(block_header_copy.next_free_block);
                }
                return allocated_ptr;
            }
            block_header = block_header->next_free_block;
        }
        return nullptr;
    }

    auto kfree(void* ptr) -> void {
        if(!ptr) return;
        const auto allocated_header = reinterpret_cast<KernelAllocatedHeapBlockHeader*>(
                                        reinterpret_cast<std::byte*>(ptr) - sizeof(KernelAllocatedHeapBlockHeader));
        const auto block_size = allocated_header->block_size;
        const auto free_header = new (allocated_header) KernelFreeHeapBlockHeader{MemoryManager::get_kernel_heap_block_list_head(), block_size};
        MemoryManager::set_kernel_heap_block_list_head(free_header);
    }

}
