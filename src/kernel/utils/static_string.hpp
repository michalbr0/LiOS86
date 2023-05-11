#pragma once

#include <cstddef>

#include "../std/cstring.hpp"

namespace LiOS86 {

    template<typename CharT, std::size_t Capacity>
    class StaticBasicString {
        public:
            using value_type = CharT;
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

            constexpr auto data() noexcept -> CharT* {
                return arr;
            }
            constexpr auto data() const noexcept -> const CharT* {
                return arr;
            }

            constexpr auto c_str() const noexcept -> const CharT* {
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

            friend constexpr auto operator==(const StaticBasicString<CharT, Capacity>& lhs, const StaticBasicString<CharT, Capacity>& rhs) -> bool {
                if(lhs.size() != rhs.size()) return false;
                return (std::strcmp(lhs.c_str(), rhs.c_str()) == 0);
            }
            friend constexpr auto operator==(const StaticBasicString<CharT, Capacity>& lhs, const CharT* rhs) -> bool {
                return (std::strcmp(lhs.c_str(), rhs) == 0);
            }
            friend constexpr auto operator<=>(const StaticBasicString<CharT, Capacity>& lhs, const StaticBasicString<CharT, Capacity>& rhs) -> int {
                return std::strcmp(lhs.c_str(), rhs.c_str());
            }
            friend constexpr auto operator<=>(const StaticBasicString<CharT, Capacity>& lhs, const CharT* rhs) -> int {
                return std::strcmp(lhs.c_str(), rhs);
            }

            constexpr auto clear() noexcept -> void {
                arr[0] = 0;
                current_size = 0;
            }

            constexpr auto push_back(CharT value) -> void {
                ++current_size;
                arr[current_size-1] = value;
                arr[current_size] = 0;
            }

            constexpr auto pop_back() -> void {
                --current_size;
                arr[current_size] = 0;
            }

        private:
            value_type arr[Capacity+1]{};
            size_type current_size{0};
    };

    template<std::size_t Capacity>
    using StaticString = StaticBasicString<char, Capacity>;

}
