#include "shell.hpp"

#include "keyboard_controller.hpp"
#include "keyboard_event.hpp"
#include "ports.hpp"
#include "memory_manager.hpp"
#include "std/cstring.hpp"

namespace LiOS86 {

    namespace {
        constexpr int NUMBER_OF_COLUMNS = 80;
        constexpr int NUMBER_OF_ROWS = 25;
        constexpr int MAX_CURSOR_POSITION = NUMBER_OF_COLUMNS*NUMBER_OF_ROWS - 1;
        volatile uint8_t* const FRAMEBUFFER = reinterpret_cast<volatile uint8_t*>(0xB8000);
    }

    Shell::Shell() {
        clear_impl();
        print_impl(R"(  _      _    ____   _____    ___    __)"); print_impl('\n');  
        print_impl(R"( | |    (_)  / __ \ / ____|  / _ \  / /)"); print_impl('\n');  
        print_impl(R"( | |     _  | |  | | (___   | (_) |/ /_)"); print_impl('\n');  
        print_impl(R"( | |    | | | |  | |\___ \   > _ <| '_ \)"); print_impl('\n'); 
        print_impl(R"( | |____| | | |__| |____) | | (_) | (_) |)"); print_impl('\n');
        print_impl(R"( |______|_|  \____/|_____/   \___/ \___/)"); print_impl('\n'); 
        print_impl('\n');
        print_impl("version 1.0.0\n");
        print_impl("Developed by michalbr0 (github.com/michalbr0)\n\n");
        print_impl("Hello adventurer!\n\n");
        print_impl(">");
        KeyboardController::set_event_callback(keyboard_event_handler);
    }

    auto Shell::scroll_up(int number_of_lines) -> void {
        if(number_of_lines > 0 && number_of_lines <= NUMBER_OF_ROWS) {
            for(int i = 0; i < (NUMBER_OF_ROWS-number_of_lines)*NUMBER_OF_COLUMNS; ++i) {
                FRAMEBUFFER[2*i] = FRAMEBUFFER[2*(i+number_of_lines*NUMBER_OF_COLUMNS)];
                FRAMEBUFFER[2*i+1] = FRAMEBUFFER[2*(i+number_of_lines*NUMBER_OF_COLUMNS)+1];
            }
            for(int i = (NUMBER_OF_ROWS-number_of_lines)*NUMBER_OF_COLUMNS; i <= MAX_CURSOR_POSITION; ++i) {
                FRAMEBUFFER[2*i] = ' ';
                FRAMEBUFFER[2*i+1] = 7;
            }
        }
        cursor_position.set(cursor_position.get() - number_of_lines*NUMBER_OF_COLUMNS);
        cursor_position.flush();
    }

    auto Shell::putchar(char c) -> void {
        if(c >= ' ' && c <= '~') {
            if(cursor_position.is_last_position()) {
                scroll_up(1);
            }
            FRAMEBUFFER[2*cursor_position.get()] = c;
            FRAMEBUFFER[2*cursor_position.get()+1] = 7;
            ++cursor_position;
        } else if(c == '\n') {
            if(cursor_position.is_last_line()) {
                scroll_up(1);
            }
            cursor_position.set((cursor_position.get() / NUMBER_OF_COLUMNS + 1) * NUMBER_OF_COLUMNS);
        }
    }

    auto Shell::remove_preceding_character() -> void {
        --cursor_position;
        putchar(' ');
        --cursor_position;
        cursor_position.flush();
    }

    auto Shell::print_impl(const char* cstr) -> void {
        while(*cstr) {
            putchar(*cstr);
            ++cstr;
        }
        cursor_position.flush();
    }

    auto Shell::print_impl(char c) -> void {
        putchar(c);
        cursor_position.flush();
    }

    auto Shell::clear_impl() -> void {
        for(int i = 0; i <= MAX_CURSOR_POSITION; ++i) {
            putchar(' ');
        }
        cursor_position.set(0);
        cursor_position.flush();
    }

    auto Shell::keyboard_event_handler(KeyboardEvent event) -> void {
        auto& instance = Shell::instance();
        if(event.get_event_type() == KeyboardEvent::EventType::PRESSED && event.get_char_representation()) {
            if(instance.input_buffer.size() < instance.input_buffer.capacity()) {
                print(event.get_char_representation());
                instance.input_buffer.push_back(event.get_char_representation());
            }
        } else if(event.get_event_type() == KeyboardEvent::EventType::PRESSED && event.get_keycode() == KeyboardHelpers::KeyCode::BACKSPACE) {
            if(instance.input_buffer.size() > 0) {
                instance.remove_preceding_character();
                instance.input_buffer.pop_back();
            }
        } else if(event.get_event_type() == KeyboardEvent::EventType::PRESSED && event.get_keycode() == KeyboardHelpers::KeyCode::ENTER) {
            print("\n");
            if(instance.input_buffer == "help") {
                print("Available commands:\n");
                print("memmap - displays the physical memory map\n");
                print("clear - clears the screen\n");
                print("help - lists available commands\n");
            } else if(instance.input_buffer == "memmap") {
                MemoryManager::print_memory_map();
            } else if(instance.input_buffer == "clear") {
                clear();
            } else {
                print("Invalid command. Type help to list available commands.\n");
            }
            print(">");
            instance.input_buffer.clear();
        }
    }

    auto Shell::CursorPosition::get() const -> int {
        return position;
    }
    auto Shell::CursorPosition::is_last_position() const -> bool {
        return (position == MAX_CURSOR_POSITION);
    }
    auto Shell::CursorPosition::is_last_line() const -> bool {
        return (position >= (NUMBER_OF_ROWS-1)*NUMBER_OF_COLUMNS);
    }
    auto Shell::CursorPosition::set(int new_position) -> void {
        if(new_position >= 0 && new_position <= MAX_CURSOR_POSITION) {
            position = new_position;
        }
    }
    auto Shell::CursorPosition::operator++() -> CursorPosition& {
        if(position < MAX_CURSOR_POSITION) position++;
        return *this;
    }
    auto Shell::CursorPosition::operator--() -> CursorPosition& {
        if(position > 0) position--;
        return *this;
    }
    auto Shell::CursorPosition::flush() const -> void {
        outb(Port::VGA_REGISTER_INDEX_3D4, 0x0f);
        outb(Port::VGA_REGISTER_DATA_3D5, static_cast<uint8_t>(position & 0xff));
        outb(Port::VGA_REGISTER_INDEX_3D4, 0x0e);
        outb(Port::VGA_REGISTER_DATA_3D5, static_cast<uint8_t>((position >> 8) & 0xff));
    }
    
}
