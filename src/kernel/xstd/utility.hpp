#pragma once

#include <type_traits>

namespace LiOS86::xstd {

    template<typename T>
    constexpr auto move(T&& t) noexcept {
        return static_cast<std::remove_reference_t<T>&&>(t);
    }

    template<typename T>
    constexpr auto forward(std::remove_reference_t<T>& t) noexcept {
        return static_cast<T&&>(t);
    }

    template<typename T>
    constexpr auto forward(std::remove_reference_t<T>&& t) noexcept {
        return static_cast<T&&>(t);
    }

}
