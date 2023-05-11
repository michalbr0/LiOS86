#include "cstring.hpp"

namespace std {

    auto strcmp(const char* lhs, const char* rhs) -> int {
        while(*lhs && (*lhs == *rhs)) {
            ++lhs;
            ++rhs;
        }
        return *reinterpret_cast<const unsigned char*>(lhs) - *reinterpret_cast<const unsigned char*>(rhs);
    }

}
