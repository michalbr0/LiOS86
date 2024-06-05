#include "error_handling.hpp"

#include <stdint.h>

#include "../xstd/utility.hpp"

namespace LiOS86 {

    namespace {
        constexpr int NUMBER_OF_COLUMNS = 80;
        constexpr int NUMBER_OF_ROWS = 25;
        constexpr int MAX_CURSOR_POSITION = NUMBER_OF_COLUMNS * NUMBER_OF_ROWS - 1;
        const auto FRAMEBUFFER = reinterpret_cast<volatile uint8_t*>(0xB8000);

        void putchar(char c, int position) {
            if(c < ' ' || c > '~') return;
            FRAMEBUFFER[2 * position] = c;
            FRAMEBUFFER[2 * position + 1] = 7;
        }

        auto print(const char* text, int currentPosition) -> int {
            while(*text) {
                putchar(*text, currentPosition);
                ++text;
                ++currentPosition;
            }
            return currentPosition;
        }

        void clear() {
            for(int i = 0; i <= MAX_CURSOR_POSITION; ++i) {
                putchar(' ', i);
            }
        }
    };

    [[noreturn]] void kassert_impl(const char* expressionText, const char* filename, int lineNumber) {
        // Text to be displayed: "Assertion {expressionText} failed (filename:lineNumber). Halting."
        clear();
        int currentPosition = 0;
        currentPosition = print("Assertion ", currentPosition);
        currentPosition = print(expressionText, currentPosition);
        currentPosition = print(" failed (", currentPosition);
        currentPosition = print(filename, currentPosition);
        currentPosition = print(":", currentPosition);

        char lineNumberChars[11]{};
        int digitCount = 0;
        int temp = lineNumber;

        do {
            ++digitCount;
            temp /= 10;
        } while(temp != 0);

        while(lineNumber > 0) {
            --digitCount;
            lineNumberChars[digitCount] = static_cast<char>(lineNumber % 10) + '0';
            lineNumber /= 10;
        }
        currentPosition = print(lineNumberChars, currentPosition);

        currentPosition = print("). Halting.", currentPosition);
        kpanic();
    }

    [[noreturn]] void kpanic(const char* message) {
        clear();
        print(message, 0);
        kpanic();
    }

    [[noreturn]] void kpanic() {
        __asm__ volatile ("cli");
		__asm__ volatile ("hlt");
        xstd::unreachable();
    }

}