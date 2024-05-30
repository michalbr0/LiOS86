#include "cstring.hpp"

namespace LiOS86::xstd {

    auto strcmp(const char* lhs, const char* rhs) -> int {
        while(*lhs && (*lhs == *rhs)) {
            ++lhs;
            ++rhs;
        }
        return *reinterpret_cast<const unsigned char*>(lhs) - *reinterpret_cast<const unsigned char*>(rhs);
    }

    auto memcpy(void* dest, const void* src, std::size_t count) -> void* {
        auto destBytePtr = reinterpret_cast<unsigned char*>(dest);
        auto srcBytePtr = reinterpret_cast<const unsigned char*>(src);
        while(count--) {
            *(destBytePtr++) = *(srcBytePtr++);
        }
        return dest;
    }

}
