#pragma once

#include <cstddef>

namespace LiOS86::xstd {
    
    template<typename T, std::size_t N>
    class array {
        public:
            using value_type = T;
            using size_type = std::size_t;
            using difference_type = std::ptrdiff_t;
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = value_type*;
            using const_pointer = const value_type;

            using iterator = value_type*;
            using const_iterator = const value_type*;

            constexpr auto operator[](size_type pos) -> reference {
                return _arr[pos];
            }
            constexpr auto operator[](size_type pos) const -> const_reference {
                return _arr[pos];
            }

            constexpr auto front() -> reference {
                return _arr[0];
            }
            constexpr auto front() const -> const_reference {
                return _arr[0];
            }

            constexpr auto back() -> reference {
                return _arr[N-1];
            }
            constexpr auto back() const -> const_reference {
                return _arr[N-1];
            }

            constexpr auto data() noexcept -> T* {
                return _arr;
            }
            constexpr auto data() const noexcept -> const T* {
                return _arr;
            }

            constexpr auto begin() noexcept -> iterator {
                return &_arr[0];
            }
            constexpr auto begin() const noexcept -> const_iterator {
                return &_arr[0];
            }
            constexpr auto cbegin() const noexcept -> const_iterator {
                return &_arr[0];
            }

            constexpr auto end() noexcept -> iterator {
                return &_arr[0] + N;
            }
            constexpr auto end() const noexcept -> const_iterator {
                return &_arr[0] + N;
            }
            constexpr auto cend() const noexcept -> const_iterator {
                return &_arr[0] + N;
            }

            [[nodiscard]] constexpr auto empty() const noexcept -> bool {
                return (begin() == end());
            }

            constexpr auto size() const noexcept -> size_type {
                return N;
            }

            constexpr auto fill(const T& value) -> void {
                for(std::size_t i = 0; i < N; ++i) {
                    _arr[i] = value;
                }
            }

            value_type _arr[N];
    };

}
