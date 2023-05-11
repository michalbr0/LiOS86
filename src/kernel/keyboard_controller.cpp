#include "keyboard_controller.hpp"

#include "interrupt_manager.hpp"
#include "ports.hpp"
#include "keyboard_helpers.hpp"
#include "keyboard_event.hpp"

namespace LiOS86 {

    namespace {
        auto get_scancode() -> KeyboardHelpers::ScanCode {
            return static_cast<KeyboardHelpers::ScanCode>(inb(Port::PS2_DATA));
        }

        auto get_extended_scancode() -> KeyboardHelpers::ExtendedScanCode {
            return static_cast<KeyboardHelpers::ExtendedScanCode>(inb(Port::PS2_DATA));
        }
    }

    KeyboardController::KeyboardController() {
        InterruptManager::set_interrupt_handler(0x21, keyboard_interrupt_handler);
    }

    auto KeyboardController::set_event_callback_impl(CallbackPointerType callback) -> void {
        event_callback = callback;
    }

    auto KeyboardController::is_shift_mode_active_impl() const -> bool {
        return keys_state[KeyboardHelpers::KeyCode::LEFT_SHIFT] == KeyState::PRESSED ||
                keys_state[KeyboardHelpers::KeyCode::RIGHT_SHIFT] == KeyState::PRESSED;
    }

    auto KeyboardController::is_capslock_active_impl() const -> bool {
        return (capslock_state == LockKeyState::ACTIVE);
    }

    auto KeyboardController::execute_callback(KeyboardEvent event) const -> void {
        if(event_callback != nullptr) {
            event_callback(event);
        }
    }

    auto KeyboardController::keyboard_interrupt_handler() -> void {
        auto& instance = KeyboardController::instance();
        if(instance.extended_scancode_sequence_started) {
            instance.extended_scancode_sequence_started = false;
            const auto extended_scancode = get_extended_scancode();
            const auto keycode = KeyboardHelpers::extended_scancode_keycode_map[extended_scancode];
            const auto scancode_type = KeyboardHelpers::extended_scancode_type_map[extended_scancode];
            if(scancode_type == KeyboardHelpers::ScanCodeType::PRESSED || scancode_type == KeyboardHelpers::ScanCodeType::RELEASED) {
                instance.keys_state[keycode] = (scancode_type == KeyboardHelpers::ScanCodeType::PRESSED ? KeyState::PRESSED : KeyState::RELEASED);
                KeyboardEvent event{keycode, (scancode_type == KeyboardHelpers::ScanCodeType::PRESSED ? KeyboardEvent::EventType::PRESSED : KeyboardEvent::EventType::RELEASED)};
                instance.execute_callback(event);
            }
        } else if(const auto scancode = get_scancode(); scancode != KeyboardHelpers::ScanCode::EXTENDED_SCANCODE_START) {
            if(scancode == KeyboardHelpers::ScanCode::CAPSLOCK_PRESSED && instance.keys_state[KeyboardHelpers::KeyCode::CAPSLOCK] == KeyState::RELEASED) {
                if(instance.capslock_state == LockKeyState::ACTIVE) {
                    instance.capslock_state = LockKeyState::INACTIVE;
                } else if(instance.capslock_state == LockKeyState::INACTIVE) {
                    instance.capslock_state = LockKeyState::ACTIVE;
                }
            }
            const auto keycode = KeyboardHelpers::scancode_keycode_map[scancode];
            const auto scancode_type = KeyboardHelpers::scancode_type_map[scancode];
            if(scancode_type == KeyboardHelpers::ScanCodeType::PRESSED || scancode_type == KeyboardHelpers::ScanCodeType::RELEASED) {
                instance.keys_state[keycode] = (scancode_type == KeyboardHelpers::ScanCodeType::PRESSED ? KeyState::PRESSED : KeyState::RELEASED);
                KeyboardEvent event{keycode, (scancode_type == KeyboardHelpers::ScanCodeType::PRESSED ? KeyboardEvent::EventType::PRESSED : KeyboardEvent::EventType::RELEASED)};
                instance.execute_callback(event);
            }
        } else {
            instance.extended_scancode_sequence_started = true;
        }
    }

}
