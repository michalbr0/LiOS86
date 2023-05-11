#pragma once

#include <cstddef>

namespace LiOS86 {

    auto kmalloc(std::size_t size) -> void*;
    auto kfree(void* ptr) -> void;

}
