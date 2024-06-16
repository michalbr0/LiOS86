#pragma once

#include <cstddef>
#include <type_traits>

#include "../xstd/utility.hpp"

namespace LiOS86 {

    template<typename T, std::size_t Capacity>
    requires std::is_trivially_default_constructible_v<T> && std::is_trivially_destructible_v<T>
    class StaticVector {
        public:
            using value_type = T;
            using size_type = std::size_t;
            using reference = value_type&;
            using const_reference = const value_type&;

            using iterator = value_type*;
            using const_iterator = const value_type*;

            constexpr auto operator[](size_type pos) -> reference {
                return arr[pos];
            }
            constexpr auto operator[](size_type pos) const -> const_reference {
                return arr[pos];
            }

            constexpr auto front() -> reference {
                return arr[0];
            }
            constexpr auto front() const -> const_reference {
                return arr[0];
            }

            constexpr auto back() -> reference {
                return arr[current_size-1];
            }
            constexpr auto back() const -> const_reference {
                return arr[current_size-1];
            }

            constexpr auto data() noexcept -> T* {
                return arr;
            }
            constexpr auto data() const noexcept -> const T* {
                return arr;
            }

            constexpr auto begin() noexcept -> iterator {
                return &arr[0];
            }
            constexpr auto begin() const noexcept -> const_iterator {
                return &arr[0];
            }
            constexpr auto cbegin() const noexcept -> const_iterator {
                return &arr[0];
            }

            constexpr auto end() noexcept -> iterator {
                return &arr[0] + current_size;
            }
            constexpr auto end() const noexcept -> const_iterator {
                return &arr[0] + current_size;
            }
            constexpr auto cend() const noexcept -> const_iterator {
                return &arr[0] + current_size;
            }

            [[nodiscard]] constexpr auto empty() const noexcept -> bool {
                return (current_size == 0);
            }

            constexpr auto size() const noexcept -> size_type {
                return current_size;
            }

            constexpr auto capacity() const noexcept -> size_type {
                return Capacity;
            }

            constexpr auto clear() noexcept -> void;

            constexpr auto push_back(const T& value) -> void;
            constexpr auto push_back(T&& value) -> void;

            template<typename... Args>
            constexpr auto emplace_back(Args&&... args) -> reference;

            constexpr auto pop_back() -> void;

        private:
            value_type arr[Capacity]{};
            size_type current_size{0};
    };

    template<typename T, std::size_t Capacity>
    constexpr auto StaticVector<T, Capacity>::clear() noexcept -> void {
        while(current_size > 0) {
            pop_back();
        }
    }

    template<typename T, std::size_t Capacity>
    constexpr auto StaticVector<T, Capacity>::push_back(const T& value) -> void {
        ++current_size;
        back() = value;
    }

    template<typename T, std::size_t Capacity>
    constexpr auto StaticVector<T, Capacity>::push_back(T&& value) -> void {
        ++current_size;
        back() = xstd::move(value);
    }

    template<typename T, std::size_t Capacity>
    template<typename... Args>
    constexpr auto StaticVector<T, Capacity>::emplace_back(Args&&... args) -> reference {
        ++current_size;
        back() = T(xstd::forward<Args>(args)...);
        return back();
    }

    template<typename T, std::size_t Capacity>
    constexpr auto StaticVector<T, Capacity>::pop_back() -> void {
        back().~T();
        --current_size;
    }

}
