#pragma once

#include <concepts>
#include <limits>
#include "xstd/array.hpp"
#include "utils/static_string.hpp"

namespace LiOS86 {

    class KeyboardEvent;

    class Shell {
        public:
            Shell(const Shell&) = delete;
            Shell& operator=(const Shell&) = delete;
            Shell(Shell&&) = delete;
            Shell& operator=(Shell&&) = delete;

            static auto& instance() {
                static Shell shell;
                return shell;
            }
            
            static auto print(const char* cstr) -> void {
                instance().print_impl(cstr);
            }
            static auto print(char c) -> void {
                instance().print_impl(c);
            }

            template<std::unsigned_integral T>
            static auto printhex(T value) -> void {
                instance().printhex_impl(value);
            }

            static auto clear() -> void {
                instance().clear_impl();
            }

        private:
            Shell();

            static auto keyboard_event_handler(KeyboardEvent event) -> void;

            auto scroll_up(int number_of_lines) -> void;
            auto putchar(char c) -> void;
            auto remove_preceding_character() -> void;

            auto print_impl(const char* cstr) -> void;
            auto print_impl(char c) -> void;

            template<std::unsigned_integral T>
            auto printhex_impl(T value) -> void;

            auto clear_impl() -> void;

            StaticString<256> input_buffer{};

            class CursorPosition {
                public:
                    auto get() const -> int;
                    auto is_last_position() const -> bool;
                    auto is_last_line() const -> bool;
                    auto set(int new_position) -> void ;
                    auto operator++() -> CursorPosition&;
                    auto operator--() -> CursorPosition&;
                    auto flush() const -> void;
                private:
                    int position = 0;
            };
            CursorPosition cursor_position{};
    };

    template<std::unsigned_integral T>
    auto Shell::printhex_impl(T value) -> void {
        print_impl("0x");
        constexpr auto width = std::numeric_limits<T>::digits / 4;
        xstd::array<char, width> str;
        str.fill('0');
        size_t current_char_index = width - 1;
        while(value > 0) {
            str[current_char_index] = value % 16;
            if(str[current_char_index] >= 10) str[current_char_index] += 'a' - 10;
            else str[current_char_index] += '0';
            value >>= 4;
            --current_char_index;
        }
        for(const auto ch : str) {
            print_impl(ch);
        }
    }
    
}
