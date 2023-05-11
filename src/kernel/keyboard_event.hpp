#pragma once

#include "keyboard_helpers.hpp"

namespace LiOS86 {

    class KeyboardEvent {
        public:
            using KeyCode = KeyboardHelpers::KeyCode;
            enum class EventType : bool { PRESSED, RELEASED };

            KeyboardEvent(KeyboardHelpers::KeyCode keycode, EventType event_type);

            auto get_event_type() const -> EventType {
                return event_type;
            }
            auto get_keycode() const -> KeyCode {
                return keycode;
            }
            auto get_char_representation() const -> char {
                return char_representation;
            }

        private:
            EventType event_type;
            KeyCode keycode;
            char char_representation;
    };
    
}
