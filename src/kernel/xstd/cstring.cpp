#include "cstring.hpp"

namespace LiOS86::xstd {

    auto strcmp(const char* lhs, const char* rhs) -> int {
        while(*lhs && (*lhs == *rhs)) {
            ++lhs;
            ++rhs;
        }
        return *reinterpret_cast<const unsigned char*>(lhs) - *reinterpret_cast<const unsigned char*>(rhs);
    }

}
