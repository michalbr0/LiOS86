#pragma once

#define kassert(EXPRESSION) (void)((EXPRESSION) || (LiOS86::kassert_impl(#EXPRESSION, __FILE__, __LINE__), 0))

namespace LiOS86 {

    [[noreturn]] void kassert_impl(const char* message, const char* filename, int lineNumber);
    [[noreturn]] void kpanic(const char* message);
    [[noreturn]] void kpanic();

}
