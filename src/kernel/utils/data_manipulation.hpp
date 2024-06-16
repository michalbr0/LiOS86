#pragma once

#include <stdint.h>
#include <cstddef>
#include <type_traits>

namespace LiOS86 {

    template<typename T>
    requires std::is_trivial_v<T>
    auto readFromMemoryAndPun(const volatile uint8_t* source) -> T {
        T result{};
        auto resultPtr = reinterpret_cast<uint8_t*>(&result);
        auto count = sizeof(T);
        while(count--) {
            *(resultPtr++) = *(source++);
        }
        return result;
    } 

    template<typename T>
    auto readFromMemoryAndPun(const volatile uint8_t* source, std::size_t offset) -> T {
        return readFromMemoryAndPun<T>(source + offset);
    }

}
