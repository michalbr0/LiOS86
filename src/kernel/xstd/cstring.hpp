#pragma once

#include <cstddef>

namespace LiOS86::xstd {

    auto strcmp(const char* lhs, const char* rhs) -> int;
    auto memcpy(void* dest, const void* src, std::size_t count) -> void*;

}
