#pragma once

#include "keyboard_helpers.hpp"
#include "utils/array_map.hpp"

namespace LiOS86 {
    
    class KeyboardEvent;

    class KeyboardController {
        public:
            KeyboardController(const KeyboardController&) = delete;
            KeyboardController& operator=(const KeyboardController&) = delete;
            KeyboardController(KeyboardController&&) = delete;
            KeyboardController& operator=(KeyboardController&&) = delete;

            static auto& instance() {
                static KeyboardController keyboard_controller;
                return keyboard_controller;
            }
            static auto is_shift_mode_active() -> bool {
                return instance().is_shift_mode_active_impl();
            }
            static auto is_capslock_active() -> bool {
                return instance().is_capslock_active_impl();
            }

            using CallbackPointerType = void (*)(KeyboardEvent);
            static auto set_event_callback(CallbackPointerType callback) -> void {
                instance().set_event_callback_impl(callback);
            }

        private:
            KeyboardController();

            auto is_shift_mode_active_impl() const -> bool;
            auto is_capslock_active_impl() const -> bool;
            auto set_event_callback_impl(CallbackPointerType callback) -> void;

            static auto keyboard_interrupt_handler() -> void;

            CallbackPointerType event_callback{nullptr};
            auto execute_callback(KeyboardEvent event) const -> void;

            bool extended_scancode_sequence_started{false};
            enum class KeyState : bool { PRESSED, RELEASED };
            ArrayMap<KeyboardHelpers::KeyCode, KeyState> keys_state{KeyState::RELEASED};

            enum class LockKeyState : bool { ACTIVE, INACTIVE };
            LockKeyState capslock_state{LockKeyState::INACTIVE};
    };

}
