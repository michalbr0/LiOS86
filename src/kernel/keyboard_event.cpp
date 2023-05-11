#include "keyboard_event.hpp"

#include "keyboard_controller.hpp"

namespace LiOS86 {

    namespace {
        auto convert_to_char_representation(KeyboardHelpers::KeyCode keycode) -> char {
            if(KeyboardController::is_shift_mode_active() && KeyboardController::is_capslock_active()) {
                return KeyboardHelpers::keycode_inverted_caps_char_map[keycode];
            } else if(KeyboardController::is_shift_mode_active()) {
                return KeyboardHelpers::keycode_shift_char_map[keycode];
            } else if(KeyboardController::is_capslock_active()) {
                return KeyboardHelpers::keycode_caps_char_map[keycode];
            } else {
                return KeyboardHelpers::keycode_char_map[keycode];
            }
        }
    }

    KeyboardEvent::KeyboardEvent(KeyboardHelpers::KeyCode key_code, EventType type)
        : event_type{type}, keycode{key_code}, char_representation{convert_to_char_representation(keycode)} { }

}
