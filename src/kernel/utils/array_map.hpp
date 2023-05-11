#pragma once

#include <type_traits>
#include <limits>

#include "../std/array.hpp"

namespace LiOS86 {
    
    template<typename Key, typename T>
    requires std::is_unsigned_v<Key> || (std::is_enum_v<Key> && std::is_unsigned_v<std::underlying_type_t<Key>>)
    class ArrayMap {
        public:
            using key_type = Key;
            using underlying_key_type = std::conditional_t<std::is_enum_v<Key>, std::underlying_type_t<Key>, Key>;
            using mapped_type = T;

            constexpr ArrayMap() = default;
            constexpr explicit ArrayMap(const T& default_value);

            constexpr auto operator[](Key key) -> T& {
                return arr[ static_cast<underlying_key_type>(key) ];
            }
            constexpr auto operator[](Key key) const -> const T& {
                return arr[ static_cast<underlying_key_type>(key) ];
            }

        private:
            std::array<T, std::numeric_limits<underlying_key_type>::max()+1> arr{};
    };

    template<typename Key, typename T>
    constexpr ArrayMap<Key, T>::ArrayMap(const T& default_value) {
        for(auto& value : arr) {
            value = default_value;
        }
    }

}
