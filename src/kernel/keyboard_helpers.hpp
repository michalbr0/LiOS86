#pragma once

#include <stdint.h>
#include <type_traits>

#include "utils/array_map.hpp"

namespace LiOS86::KeyboardHelpers {

    enum class KeyCode : uint8_t {                                                                                                                         
        BACKTICK,
        NUM1,
        NUM2,
        NUM3,
        NUM4,
        NUM5,
        NUM6,
        NUM7,
        NUM8,
        NUM9,
        NUM0,
        MINUS,
        EQUAL,
        Q,
        W,
        E,
        R,
        T,
        Y,
        U,
        I,
        O,
        P,
        LEFT_SQ_BRACKET,
        RIGHT_SQ_BRACKET,
        A,
        S,
        D,
        F,
        G,
        H,
        J,
        K,
        L,
        SEMICOLON,
        SINGLEQUOTE,
        BACKSLASH,
        Z,
        X,
        C,
        V,
        B,
        N,
        M,
        COMMA,
        DOT,
        SLASH,
        SPACE,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        ESC,
        BACKSPACE,
        TAB,
        CAPSLOCK,
        ENTER,
        LEFT_SHIFT,
        RIGHT_SHIFT,
        LEFT_CTRL,
        LEFT_ALT,
        RIGHT_ALT,
        RIGHT_CTRL,

        HOME,
        PAGE_UP,
        END,
        PAGE_DOWN,
        INSERT,
        DELETE,

        CURSOR_UP,
        CURSOR_LEFT,
        CURSOR_RIGHT,
        CURSOR_DOWN,

        NUMLOCK,
        SCROLLLOCK,

        KEYPAD_SLASH,
        KEYPAD_STAR,
        KEYPAD_NUM7,
        KEYPAD_NUM8,
        KEYPAD_NUM9,
        KEYPAD_MINUS,
        KEYPAD_NUM4,
        KEYPAD_NUM5,
        KEYPAD_NUM6,
        KEYPAD_PLUS,
        KEYPAD_NUM1,
        KEYPAD_NUM2,
        KEYPAD_NUM3,
        KEYPAD_NUM0,
        KEYPAD_DOT,
        KEYPAD_ENTER,

        LEFT_GUI,
        RIGHT_GUI,
        APPS,

        ACPI_POWER,
        ACPI_SLEEP,
        ACPI_WAKE,

        MULTIMEDIA_PREVIOUS_TRACK,
        MULTIMEDIA_NEXT_TRACK,
        MULTIMEDIA_MUTE,
        MULTIMEDIA_CALCULATOR,
        MULTIMEDIA_PLAY,
        MULTIMEDIA_STOP,
        MULTIMEDIA_VOLUME_DOWN, 
        MULTIMEDIA_VOLUME_UP,
        MULTIMEDIA_WWW_HOME,
        MULTIMEDIA_WWW_SEARCH,
        MULTIMEDIA_WWW_FAVOURITES,
        MULTIMEDIA_WWW_REFRESH,
        MULTIMEDIA_WWW_STOP,
        MULTIMEDIA_WWW_FORWARD, 
        MULTIMEDIA_WWW_BACK, 
        MULTIMEDIA_MY_COMPUTER,
        MULTIMEDIA_EMAIL,
        MULTIMEDIA_MEDIA_SELECT,

        UNKNOWN
    };

    enum class ScanCode : uint8_t {
        ESC_PRESSED = 0x01,
        NUM1_PRESSED = 0x02,
        NUM2_PRESSED = 0x03,
        NUM3_PRESSED = 0x04,
        NUM4_PRESSED = 0x05,
        NUM5_PRESSED = 0x06,
        NUM6_PRESSED = 0x07,
        NUM7_PRESSED = 0x08,
        NUM8_PRESSED = 0x09,
        NUM9_PRESSED = 0x0a,
        NUM0_PRESSED = 0x0b,
        MINUS_PRESSED = 0x0c,
        EQUAL_PRESSED = 0x0d,
        BACKSPACE_PRESSED = 0x0e,
        TAB_PRESSED = 0x0f,
        Q_PRESSED = 0x10,
        W_PRESSED = 0x11,
        E_PRESSED = 0x12,
        R_PRESSED = 0x13,
        T_PRESSED = 0x14,
        Y_PRESSED = 0x15,
        U_PRESSED = 0x16,
        I_PRESSED = 0x17,
        O_PRESSED = 0x18,
        P_PRESSED = 0x19,
        LEFT_SQ_BRACKET_PRESSED = 0x1a,
        RIGHT_SQ_BRACKET_PRESSED = 0x1b,
        ENTER_PRESSED = 0x1c,
        LEFT_CTRL_PRESSED = 0x1d,
        A_PRESSED = 0x1e,
        S_PRESSED = 0x1f,
        D_PRESSED = 0x20,
        F_PRESSED = 0x21,
        G_PRESSED = 0x22,
        H_PRESSED = 0x23,
        J_PRESSED = 0x24,
        K_PRESSED = 0x25,
        L_PRESSED = 0x26,
        SEMICOLON_PRESSED = 0x27,
        SINGLEQUOTE_PRESSED = 0x28,
        BACKTICK_PRESSED = 0x29,
        LEFT_SHIFT_PRESSED = 0x2a,
        BACKSLASH_PRESSED = 0x2b,
        Z_PRESSED = 0x2c,
        X_PRESSED = 0x2d,
        C_PRESSED = 0x2e,
        V_PRESSED = 0x2f,
        B_PRESSED = 0x30,
        N_PRESSED = 0x31,
        M_PRESSED = 0x32,
        COMMA_PRESSED = 0x33,
        DOT_PRESSED = 0x34,
        SLASH_PRESSED = 0x35,
        RIGHT_SHIFT_PRESSED = 0x36,
        KEYPAD_STAR_PRESSED = 0x37,
        LEFT_ALT_PRESSED = 0x38,
        SPACE_PRESSED = 0x39,
        CAPSLOCK_PRESSED = 0x3a,
        F1_PRESSED = 0x3b,
        F2_PRESSED = 0x3c,
        F3_PRESSED = 0x3d,
        F4_PRESSED = 0x3e,
        F5_PRESSED = 0x3f,
        F6_PRESSED = 0x40,
        F7_PRESSED = 0x41,
        F8_PRESSED = 0x42,
        F9_PRESSED = 0x43,
        F10_PRESSED = 0x44,
        NUMLOCK_PRESSED = 0x45,
        SCROLLLOCK_PRESSED = 0x46,
        KEYPAD_NUM7_PRESSED = 0x47,
        KEYPAD_NUM8_PRESSED = 0x48,
        KEYPAD_NUM9_PRESSED = 0x49,
        KEYPAD_MINUS_PRESSED = 0x4a,
        KEYPAD_NUM4_PRESSED = 0x4b,
        KEYPAD_NUM5_PRESSED = 0x4c,
        KEYPAD_NUM6_PRESSED = 0x4d,
        KEYPAD_PLUS_PRESSED = 0x4e,
        KEYPAD_NUM1_PRESSED = 0x4f,
        KEYPAD_NUM2_PRESSED = 0x50,
        KEYPAD_NUM3_PRESSED = 0x51,
        KEYPAD_NUM0_PRESSED = 0x52,
        KEYPAD_DOT_PRESSED = 0x53,
        F11_PRESSED = 0x57,
        F12_PRESSED = 0x58,

        ESC_RELEASED = 0x81,
        NUM1_RELEASED = 0x82,
        NUM2_RELEASED = 0x83,
        NUM3_RELEASED = 0x84,
        NUM4_RELEASED = 0x85,
        NUM5_RELEASED = 0x86,
        NUM6_RELEASED = 0x87,
        NUM7_RELEASED = 0x88,
        NUM8_RELEASED = 0x89,
        NUM9_RELEASED = 0x8a,
        NUM0_RELEASED = 0x8b,
        MINUS_RELEASED = 0x8c,
        EQUAL_RELEASED = 0x8d,
        BACKSPACE_RELEASED = 0x8e,
        TAB_RELEASED = 0x8f,
        Q_RELEASED = 0x90,
        W_RELEASED = 0x91,
        E_RELEASED = 0x92,
        R_RELEASED = 0x93,
        T_RELEASED = 0x94,
        Y_RELEASED = 0x95,
        U_RELEASED = 0x96,
        I_RELEASED = 0x97,
        O_RELEASED = 0x98,
        P_RELEASED = 0x99,
        LEFT_SQ_BRACKET_RELEASED = 0x9a,
        RIGHT_SQ_BRACKET_RELEASED = 0x9b,
        ENTER_RELEASED = 0x9c,
        LEFT_CTRL_RELEASED = 0x9d,
        A_RELEASED = 0x9e,
        S_RELEASED = 0x9f,
        D_RELEASED = 0xa0,
        F_RELEASED = 0xa1,
        G_RELEASED = 0xa2,
        H_RELEASED = 0xa3,
        J_RELEASED = 0xa4,
        K_RELEASED = 0xa5,
        L_RELEASED = 0xa6,
        SEMICOLON_RELEASED = 0xa7,
        SINGLEQUOTE_RELEASED = 0xa8,
        BACKTICK_RELEASED = 0xa9,
        LEFT_SHIFT_RELEASED = 0xaa,
        BACKSLASH_RELEASED = 0xab,
        Z_RELEASED = 0xac,
        X_RELEASED = 0xad,
        C_RELEASED = 0xae,
        V_RELEASED = 0xaf,
        B_RELEASED = 0xb0,
        N_RELEASED = 0xb1,
        M_RELEASED = 0xb2,
        COMMA_RELEASED = 0xb3,
        DOT_RELEASED = 0xb4,
        SLASH_RELEASED = 0xb5,
        RIGHT_SHIFT_RELEASED = 0xb6,
        KEYPAD_STAR_RELEASED = 0xb7,
        LEFT_ALT_RELEASED = 0xb8,
        SPACE_RELEASED = 0xb9,
        CAPSLOCK_RELEASED = 0xba,
        F1_RELEASED = 0xbb,
        F2_RELEASED = 0xbc,
        F3_RELEASED = 0xbd,
        F4_RELEASED = 0xbe,
        F5_RELEASED = 0xbf,
        F6_RELEASED = 0xc0,
        F7_RELEASED = 0xc1,
        F8_RELEASED = 0xc2,
        F9_RELEASED = 0xc3,
        F10_RELEASED = 0xc4,
        NUMLOCK_RELEASED = 0xc5,
        SCROLLLOCK_RELEASED = 0xc6,
        KEYPAD_NUM7_RELEASED = 0xc7,
        KEYPAD_NUM8_RELEASED = 0xc8,
        KEYPAD_NUM9_RELEASED = 0xc9,
        KEYPAD_MINUS_RELEASED = 0xca,
        KEYPAD_NUM4_RELEASED = 0xcb,
        KEYPAD_NUM5_RELEASED = 0xcc,
        KEYPAD_NUM6_RELEASED = 0xcd,
        KEYPAD_PLUS_RELEASED = 0xce,
        KEYPAD_NUM1_RELEASED = 0xcf,
        KEYPAD_NUM2_RELEASED = 0xd0,
        KEYPAD_NUM3_RELEASED = 0xd1,
        KEYPAD_NUM0_RELEASED = 0xd2,
        KEYPAD_DOT_RELEASED = 0xd3,
        F11_RELEASED = 0xd7,
        F12_RELEASED = 0xd8,

        EXTENDED_SCANCODE_START = 0xe0
    };

    enum class ExtendedScanCode : uint8_t {
        MULTIMEDIA_PREVIOUS_TRACK_PRESSED = 0x10,
        MULTIMEDIA_NEXT_TRACK_PRESSED = 0x19,
        KEYPAD_ENTER_PRESSED = 0x1c,
        RIGHT_CTRL_PRESSED = 0x1d,
        MULTIMEDIA_MUTE_PRESSED = 0x20,
        MULTIMEDIA_CALCULATOR_PRESSED = 0x21,
        MULTIMEDIA_PLAY_PRESSED = 0x22,
        MULTIMEDIA_STOP_PRESSED = 0x24,
        MULTIMEDIA_VOLUME_DOWN_PRESSED = 0x2e, 
        MULTIMEDIA_VOLUME_UP_PRESSED = 0x30,
        MULTIMEDIA_WWW_HOME_PRESSED = 0x32,
        KEYPAD_SLASH_PRESSED = 0x35,
        RIGHT_ALT_PRESSED = 0x38,
        HOME_PRESSED = 0x47,
        CURSOR_UP_PRESSED = 0x48,
        PAGE_UP_PRESSED = 0x49,
        CURSOR_LEFT_PRESSED = 0x4b,
        CURSOR_RIGHT_PRESSED = 0x4d,
        END_PRESSED = 0x4f,
        CURSOR_DOWN_PRESSED = 0x50,
        PAGE_DOWN_PRESSED = 0x51,
        INSERT_PRESSED = 0x52,
        DELETE_PRESSED = 0x53,
        LEFT_GUI_PRESSED = 0x5b,
        RIGHT_GUI_PRESSED = 0x5c,
        APPS_PRESSED = 0x5d,
        ACPI_POWER_PRESSED = 0x5e,
        ACPI_SLEEP_PRESSED = 0x5f,
        ACPI_WAKE_PRESSED = 0x63,
        MULTIMEDIA_WWW_SEARCH_PRESSED = 0x65,
        MULTIMEDIA_WWW_FAVOURITES_PRESSED = 0x66,
        MULTIMEDIA_WWW_REFRESH_PRESSED = 0x67,
        MULTIMEDIA_WWW_STOP_PRESSED = 0x68,
        MULTIMEDIA_WWW_FORWARD_PRESSED = 0x69, 
        MULTIMEDIA_WWW_BACK_PRESSED = 0x6a, 
        MULTIMEDIA_MY_COMPUTER_PRESSED = 0x6b,
        MULTIMEDIA_EMAIL_PRESSED = 0x6c,
        MULTIMEDIA_MEDIA_SELECT_PRESSED = 0x6d,

        MULTIMEDIA_PREVIOUS_TRACK_RELEASED = 0x90,
        MULTIMEDIA_NEXT_TRACK_RELEASED = 0x99,
        KEYPAD_ENTER_RELEASED = 0x9c,
        RIGHT_CTRL_RELEASED = 0x9d,
        MULTIMEDIA_MUTE_RELEASED = 0xa0,
        MULTIMEDIA_CALCULATOR_RELEASED = 0xa1,
        MULTIMEDIA_PLAY_RELEASED = 0xa2,
        MULTIMEDIA_STOP_RELEASED = 0xa4,
        MULTIMEDIA_VOLUME_DOWN_RELEASED = 0xae, 
        MULTIMEDIA_VOLUME_UP_RELEASED = 0xb0,
        MULTIMEDIA_WWW_HOME_RELEASED = 0xb2,
        KEYPAD_SLASH_RELEASED = 0xb5,
        RIGHT_ALT_RELEASED = 0xb8,
        HOME_RELEASED = 0xc7,
        CURSOR_UP_RELEASED = 0xc8,
        PAGE_UP_RELEASED = 0xc9,
        CURSOR_LEFT_RELEASED = 0xcb,
        CURSOR_RIGHT_RELEASED = 0xcd,
        END_RELEASED = 0xcf,
        CURSOR_DOWN_RELEASED = 0xd0,
        PAGE_DOWN_RELEASED = 0xd1,
        INSERT_RELEASED = 0xd2,
        DELETE_RELEASED = 0xd3,
        LEFT_GUI_RELEASED = 0xdb,
        RIGHT_GUI_RELEASED = 0xdc,
        APPS_RELEASED = 0xdd,
        ACPI_POWER_RELEASED = 0xde,
        ACPI_SLEEP_RELEASED = 0xdf,
        ACPI_WAKE_RELEASED = 0xe3,
        MULTIMEDIA_WWW_SEARCH_RELEASED = 0xe5,
        MULTIMEDIA_WWW_FAVOURITES_RELEASED = 0xe6,
        MULTIMEDIA_WWW_REFRESH_RELEASED = 0xe7,
        MULTIMEDIA_WWW_STOP_RELEASED = 0xe8,
        MULTIMEDIA_WWW_FORWARD_RELEASED = 0xe9, 
        MULTIMEDIA_WWW_BACK_RELEASED = 0xea, 
        MULTIMEDIA_MY_COMPUTER_RELEASED = 0xeb,
        MULTIMEDIA_EMAIL_RELEASED = 0xec,
        MULTIMEDIA_MEDIA_SELECT_RELEASED = 0xed
    };

    enum class ScanCodeType : uint8_t {
        PRESSED, RELEASED, EXTENDED, INVALID
    };

    inline constexpr ArrayMap<ScanCode, KeyCode> scancode_keycode_map = []() {
        ArrayMap<ScanCode, KeyCode> map{KeyCode::UNKNOWN};

        map[ScanCode::ESC_PRESSED] = KeyCode::ESC;
        map[ScanCode::NUM1_PRESSED] = KeyCode::NUM1;
        map[ScanCode::NUM2_PRESSED] = KeyCode::NUM2;
        map[ScanCode::NUM3_PRESSED] = KeyCode::NUM3;
        map[ScanCode::NUM4_PRESSED] = KeyCode::NUM4;
        map[ScanCode::NUM5_PRESSED] = KeyCode::NUM5;
        map[ScanCode::NUM6_PRESSED] = KeyCode::NUM6;
        map[ScanCode::NUM7_PRESSED] = KeyCode::NUM7;
        map[ScanCode::NUM8_PRESSED] = KeyCode::NUM8;
        map[ScanCode::NUM9_PRESSED] = KeyCode::NUM9;
        map[ScanCode::NUM0_PRESSED] = KeyCode::NUM0;
        map[ScanCode::MINUS_PRESSED] = KeyCode::MINUS;
        map[ScanCode::EQUAL_PRESSED] = KeyCode::EQUAL;
        map[ScanCode::BACKSPACE_PRESSED] = KeyCode::BACKSPACE;
        map[ScanCode::TAB_PRESSED] = KeyCode::TAB;
        map[ScanCode::Q_PRESSED] = KeyCode::Q;
        map[ScanCode::W_PRESSED] = KeyCode::W;
        map[ScanCode::E_PRESSED] = KeyCode::E;
        map[ScanCode::R_PRESSED] = KeyCode::R;
        map[ScanCode::T_PRESSED] = KeyCode::T;
        map[ScanCode::Y_PRESSED] = KeyCode::Y;
        map[ScanCode::U_PRESSED] = KeyCode::U;
        map[ScanCode::I_PRESSED] = KeyCode::I;
        map[ScanCode::O_PRESSED] = KeyCode::O;
        map[ScanCode::P_PRESSED] = KeyCode::P;
        map[ScanCode::LEFT_SQ_BRACKET_PRESSED] = KeyCode::LEFT_SQ_BRACKET;
        map[ScanCode::RIGHT_SQ_BRACKET_PRESSED] = KeyCode::RIGHT_SQ_BRACKET;
        map[ScanCode::ENTER_PRESSED] = KeyCode::ENTER;
        map[ScanCode::LEFT_CTRL_PRESSED] = KeyCode::LEFT_CTRL;
        map[ScanCode::A_PRESSED] = KeyCode::A;
        map[ScanCode::S_PRESSED] = KeyCode::S;
        map[ScanCode::D_PRESSED] = KeyCode::D;
        map[ScanCode::F_PRESSED] = KeyCode::F;
        map[ScanCode::G_PRESSED] = KeyCode::G;
        map[ScanCode::H_PRESSED] = KeyCode::H;
        map[ScanCode::J_PRESSED] = KeyCode::J;
        map[ScanCode::K_PRESSED] = KeyCode::K;
        map[ScanCode::L_PRESSED] = KeyCode::L;
        map[ScanCode::SEMICOLON_PRESSED] = KeyCode::SEMICOLON;
        map[ScanCode::SINGLEQUOTE_PRESSED] = KeyCode::SINGLEQUOTE;
        map[ScanCode::BACKTICK_PRESSED] = KeyCode::BACKTICK;
        map[ScanCode::LEFT_SHIFT_PRESSED] = KeyCode::LEFT_SHIFT;
        map[ScanCode::BACKSLASH_PRESSED] = KeyCode::BACKSLASH;
        map[ScanCode::Z_PRESSED] = KeyCode::Z;
        map[ScanCode::X_PRESSED] = KeyCode::X;
        map[ScanCode::C_PRESSED] = KeyCode::C;
        map[ScanCode::V_PRESSED] = KeyCode::V;
        map[ScanCode::B_PRESSED] = KeyCode::B;
        map[ScanCode::N_PRESSED] = KeyCode::N;
        map[ScanCode::M_PRESSED] = KeyCode::M;
        map[ScanCode::COMMA_PRESSED] = KeyCode::COMMA;
        map[ScanCode::DOT_PRESSED] = KeyCode::DOT;
        map[ScanCode::SLASH_PRESSED] = KeyCode::SLASH;
        map[ScanCode::RIGHT_SHIFT_PRESSED] = KeyCode::RIGHT_SHIFT;
        map[ScanCode::KEYPAD_STAR_PRESSED] = KeyCode::KEYPAD_STAR;
        map[ScanCode::LEFT_ALT_PRESSED] = KeyCode::LEFT_ALT;
        map[ScanCode::SPACE_PRESSED] = KeyCode::SPACE;
        map[ScanCode::CAPSLOCK_PRESSED] = KeyCode::CAPSLOCK;
        map[ScanCode::F1_PRESSED] = KeyCode::F1;
        map[ScanCode::F2_PRESSED] = KeyCode::F2;
        map[ScanCode::F3_PRESSED] = KeyCode::F3;
        map[ScanCode::F4_PRESSED] = KeyCode::F4;
        map[ScanCode::F5_PRESSED] = KeyCode::F5;
        map[ScanCode::F6_PRESSED] = KeyCode::F6;
        map[ScanCode::F7_PRESSED] = KeyCode::F7;
        map[ScanCode::F8_PRESSED] = KeyCode::F8;
        map[ScanCode::F9_PRESSED] = KeyCode::F9;
        map[ScanCode::F10_PRESSED] = KeyCode::F10;
        map[ScanCode::NUMLOCK_PRESSED] = KeyCode::NUMLOCK;
        map[ScanCode::SCROLLLOCK_PRESSED] = KeyCode::SCROLLLOCK;
        map[ScanCode::KEYPAD_NUM7_PRESSED] = KeyCode::KEYPAD_NUM7;
        map[ScanCode::KEYPAD_NUM8_PRESSED] = KeyCode::KEYPAD_NUM8;
        map[ScanCode::KEYPAD_NUM9_PRESSED] = KeyCode::KEYPAD_NUM9;
        map[ScanCode::KEYPAD_MINUS_PRESSED] = KeyCode::KEYPAD_MINUS;
        map[ScanCode::KEYPAD_NUM4_PRESSED] = KeyCode::KEYPAD_NUM4;
        map[ScanCode::KEYPAD_NUM5_PRESSED] = KeyCode::KEYPAD_NUM5;
        map[ScanCode::KEYPAD_NUM6_PRESSED] = KeyCode::KEYPAD_NUM6;
        map[ScanCode::KEYPAD_PLUS_PRESSED] = KeyCode::KEYPAD_PLUS;
        map[ScanCode::KEYPAD_NUM1_PRESSED] = KeyCode::KEYPAD_NUM1;
        map[ScanCode::KEYPAD_NUM2_PRESSED] = KeyCode::KEYPAD_NUM2;
        map[ScanCode::KEYPAD_NUM3_PRESSED] = KeyCode::KEYPAD_NUM3;
        map[ScanCode::KEYPAD_NUM0_PRESSED] = KeyCode::KEYPAD_NUM0;
        map[ScanCode::KEYPAD_DOT_PRESSED] = KeyCode::KEYPAD_DOT;
        map[ScanCode::F11_PRESSED] = KeyCode::F11;
        map[ScanCode::F12_PRESSED] = KeyCode::F12;

        map[ScanCode::ESC_RELEASED] = KeyCode::ESC;
        map[ScanCode::NUM1_RELEASED] = KeyCode::NUM1;
        map[ScanCode::NUM2_RELEASED] = KeyCode::NUM2;
        map[ScanCode::NUM3_RELEASED] = KeyCode::NUM3;
        map[ScanCode::NUM4_RELEASED] = KeyCode::NUM4;
        map[ScanCode::NUM5_RELEASED] = KeyCode::NUM5;
        map[ScanCode::NUM6_RELEASED] = KeyCode::NUM6;
        map[ScanCode::NUM7_RELEASED] = KeyCode::NUM7;
        map[ScanCode::NUM8_RELEASED] = KeyCode::NUM8;
        map[ScanCode::NUM9_RELEASED] = KeyCode::NUM9;
        map[ScanCode::NUM0_RELEASED] = KeyCode::NUM0;
        map[ScanCode::MINUS_RELEASED] = KeyCode::MINUS;
        map[ScanCode::EQUAL_RELEASED] = KeyCode::EQUAL;
        map[ScanCode::BACKSPACE_RELEASED] = KeyCode::BACKSPACE;
        map[ScanCode::TAB_RELEASED] = KeyCode::TAB;
        map[ScanCode::Q_RELEASED] = KeyCode::Q;
        map[ScanCode::W_RELEASED] = KeyCode::W;
        map[ScanCode::E_RELEASED] = KeyCode::E;
        map[ScanCode::R_RELEASED] = KeyCode::R;
        map[ScanCode::T_RELEASED] = KeyCode::T;
        map[ScanCode::Y_RELEASED] = KeyCode::Y;
        map[ScanCode::U_RELEASED] = KeyCode::U;
        map[ScanCode::I_RELEASED] = KeyCode::I;
        map[ScanCode::O_RELEASED] = KeyCode::O;
        map[ScanCode::P_RELEASED] = KeyCode::P;
        map[ScanCode::LEFT_SQ_BRACKET_RELEASED] = KeyCode::LEFT_SQ_BRACKET;
        map[ScanCode::RIGHT_SQ_BRACKET_RELEASED] = KeyCode::RIGHT_SQ_BRACKET;
        map[ScanCode::ENTER_RELEASED] = KeyCode::ENTER;
        map[ScanCode::LEFT_CTRL_RELEASED] = KeyCode::LEFT_CTRL;
        map[ScanCode::A_RELEASED] = KeyCode::A;
        map[ScanCode::S_RELEASED] = KeyCode::S;
        map[ScanCode::D_RELEASED] = KeyCode::D;
        map[ScanCode::F_RELEASED] = KeyCode::F;
        map[ScanCode::G_RELEASED] = KeyCode::G;
        map[ScanCode::H_RELEASED] = KeyCode::H;
        map[ScanCode::J_RELEASED] = KeyCode::J;
        map[ScanCode::K_RELEASED] = KeyCode::K;
        map[ScanCode::L_RELEASED] = KeyCode::L;
        map[ScanCode::SEMICOLON_RELEASED] = KeyCode::SEMICOLON;
        map[ScanCode::SINGLEQUOTE_RELEASED] = KeyCode::SINGLEQUOTE;
        map[ScanCode::BACKTICK_RELEASED] = KeyCode::BACKTICK;
        map[ScanCode::LEFT_SHIFT_RELEASED] = KeyCode::LEFT_SHIFT;
        map[ScanCode::BACKSLASH_RELEASED] = KeyCode::BACKSLASH;
        map[ScanCode::Z_RELEASED] = KeyCode::Z;
        map[ScanCode::X_RELEASED] = KeyCode::X;
        map[ScanCode::C_RELEASED] = KeyCode::C;
        map[ScanCode::V_RELEASED] = KeyCode::V;
        map[ScanCode::B_RELEASED] = KeyCode::B;
        map[ScanCode::N_RELEASED] = KeyCode::N;
        map[ScanCode::M_RELEASED] = KeyCode::M;
        map[ScanCode::COMMA_RELEASED] = KeyCode::COMMA;
        map[ScanCode::DOT_RELEASED] = KeyCode::DOT;
        map[ScanCode::SLASH_RELEASED] = KeyCode::SLASH;
        map[ScanCode::RIGHT_SHIFT_RELEASED] = KeyCode::RIGHT_SHIFT;
        map[ScanCode::KEYPAD_STAR_RELEASED] = KeyCode::KEYPAD_STAR;
        map[ScanCode::LEFT_ALT_RELEASED] = KeyCode::LEFT_ALT;
        map[ScanCode::SPACE_RELEASED] = KeyCode::SPACE;
        map[ScanCode::CAPSLOCK_RELEASED] = KeyCode::CAPSLOCK;
        map[ScanCode::F1_RELEASED] = KeyCode::F1;
        map[ScanCode::F2_RELEASED] = KeyCode::F2;
        map[ScanCode::F3_RELEASED] = KeyCode::F3;
        map[ScanCode::F4_RELEASED] = KeyCode::F4;
        map[ScanCode::F5_RELEASED] = KeyCode::F5;
        map[ScanCode::F6_RELEASED] = KeyCode::F6;
        map[ScanCode::F7_RELEASED] = KeyCode::F7;
        map[ScanCode::F8_RELEASED] = KeyCode::F8;
        map[ScanCode::F9_RELEASED] = KeyCode::F9;
        map[ScanCode::F10_RELEASED] = KeyCode::F10;
        map[ScanCode::NUMLOCK_RELEASED] = KeyCode::NUMLOCK;
        map[ScanCode::SCROLLLOCK_RELEASED] = KeyCode::SCROLLLOCK;
        map[ScanCode::KEYPAD_NUM7_RELEASED] = KeyCode::KEYPAD_NUM7;
        map[ScanCode::KEYPAD_NUM8_RELEASED] = KeyCode::KEYPAD_NUM8;
        map[ScanCode::KEYPAD_NUM9_RELEASED] = KeyCode::KEYPAD_NUM9;
        map[ScanCode::KEYPAD_MINUS_RELEASED] = KeyCode::KEYPAD_MINUS;
        map[ScanCode::KEYPAD_NUM4_RELEASED] = KeyCode::KEYPAD_NUM4;
        map[ScanCode::KEYPAD_NUM5_RELEASED] = KeyCode::KEYPAD_NUM5;
        map[ScanCode::KEYPAD_NUM6_RELEASED] = KeyCode::KEYPAD_NUM6;
        map[ScanCode::KEYPAD_PLUS_RELEASED] = KeyCode::KEYPAD_PLUS;
        map[ScanCode::KEYPAD_NUM1_RELEASED] = KeyCode::KEYPAD_NUM1;
        map[ScanCode::KEYPAD_NUM2_RELEASED] = KeyCode::KEYPAD_NUM2;
        map[ScanCode::KEYPAD_NUM3_RELEASED] = KeyCode::KEYPAD_NUM3;
        map[ScanCode::KEYPAD_NUM0_RELEASED] = KeyCode::KEYPAD_NUM0;
        map[ScanCode::KEYPAD_DOT_RELEASED] = KeyCode::KEYPAD_DOT;
        map[ScanCode::F11_RELEASED] = KeyCode::F11;
        map[ScanCode::F12_RELEASED] = KeyCode::F12;  

        return map;
    } ();
    
    inline constexpr ArrayMap<ExtendedScanCode, KeyCode> extended_scancode_keycode_map = []() {
        ArrayMap<ExtendedScanCode, KeyCode> map{KeyCode::UNKNOWN};

        map[ExtendedScanCode::MULTIMEDIA_PREVIOUS_TRACK_PRESSED] = KeyCode::MULTIMEDIA_PREVIOUS_TRACK;
        map[ExtendedScanCode::MULTIMEDIA_NEXT_TRACK_PRESSED] = KeyCode::MULTIMEDIA_NEXT_TRACK;
        map[ExtendedScanCode::KEYPAD_ENTER_PRESSED] = KeyCode::KEYPAD_ENTER;
        map[ExtendedScanCode::RIGHT_CTRL_PRESSED] = KeyCode::RIGHT_CTRL;
        map[ExtendedScanCode::MULTIMEDIA_MUTE_PRESSED] = KeyCode::MULTIMEDIA_MUTE;
        map[ExtendedScanCode::MULTIMEDIA_CALCULATOR_PRESSED] = KeyCode::MULTIMEDIA_CALCULATOR;
        map[ExtendedScanCode::MULTIMEDIA_PLAY_PRESSED] = KeyCode::MULTIMEDIA_PLAY;
        map[ExtendedScanCode::MULTIMEDIA_STOP_PRESSED] = KeyCode::MULTIMEDIA_STOP;
        map[ExtendedScanCode::MULTIMEDIA_VOLUME_DOWN_PRESSED] = KeyCode::MULTIMEDIA_VOLUME_DOWN; 
        map[ExtendedScanCode::MULTIMEDIA_VOLUME_UP_PRESSED] = KeyCode::MULTIMEDIA_VOLUME_UP;
        map[ExtendedScanCode::MULTIMEDIA_WWW_HOME_PRESSED] = KeyCode::MULTIMEDIA_WWW_HOME;
        map[ExtendedScanCode::KEYPAD_SLASH_PRESSED] = KeyCode::KEYPAD_SLASH;
        map[ExtendedScanCode::RIGHT_ALT_PRESSED] = KeyCode::RIGHT_ALT;
        map[ExtendedScanCode::HOME_PRESSED] = KeyCode::HOME;
        map[ExtendedScanCode::CURSOR_UP_PRESSED] = KeyCode::CURSOR_UP;
        map[ExtendedScanCode::PAGE_UP_PRESSED] = KeyCode::PAGE_UP;
        map[ExtendedScanCode::CURSOR_LEFT_PRESSED] = KeyCode::CURSOR_LEFT;
        map[ExtendedScanCode::CURSOR_RIGHT_PRESSED] = KeyCode::CURSOR_RIGHT;
        map[ExtendedScanCode::END_PRESSED] = KeyCode::END;
        map[ExtendedScanCode::CURSOR_DOWN_PRESSED] = KeyCode::CURSOR_DOWN;
        map[ExtendedScanCode::PAGE_DOWN_PRESSED] = KeyCode::PAGE_DOWN;
        map[ExtendedScanCode::INSERT_PRESSED] = KeyCode::INSERT;
        map[ExtendedScanCode::DELETE_PRESSED] = KeyCode::DELETE;
        map[ExtendedScanCode::LEFT_GUI_PRESSED] = KeyCode::LEFT_GUI;
        map[ExtendedScanCode::RIGHT_GUI_PRESSED] = KeyCode::RIGHT_GUI;
        map[ExtendedScanCode::APPS_PRESSED] = KeyCode::APPS;
        map[ExtendedScanCode::ACPI_POWER_PRESSED] = KeyCode::ACPI_POWER;
        map[ExtendedScanCode::ACPI_SLEEP_PRESSED] = KeyCode::ACPI_SLEEP;
        map[ExtendedScanCode::ACPI_WAKE_PRESSED] = KeyCode::ACPI_WAKE;
        map[ExtendedScanCode::MULTIMEDIA_WWW_SEARCH_PRESSED] = KeyCode::MULTIMEDIA_WWW_SEARCH;
        map[ExtendedScanCode::MULTIMEDIA_WWW_FAVOURITES_PRESSED] = KeyCode::MULTIMEDIA_WWW_FAVOURITES;
        map[ExtendedScanCode::MULTIMEDIA_WWW_REFRESH_PRESSED] = KeyCode::MULTIMEDIA_WWW_REFRESH;
        map[ExtendedScanCode::MULTIMEDIA_WWW_STOP_PRESSED] = KeyCode::MULTIMEDIA_WWW_STOP;
        map[ExtendedScanCode::MULTIMEDIA_WWW_FORWARD_PRESSED] = KeyCode::MULTIMEDIA_WWW_FORWARD; 
        map[ExtendedScanCode::MULTIMEDIA_WWW_BACK_PRESSED] = KeyCode::MULTIMEDIA_WWW_BACK; 
        map[ExtendedScanCode::MULTIMEDIA_MY_COMPUTER_PRESSED] = KeyCode::MULTIMEDIA_MY_COMPUTER;
        map[ExtendedScanCode::MULTIMEDIA_EMAIL_PRESSED] = KeyCode::MULTIMEDIA_EMAIL;
        map[ExtendedScanCode::MULTIMEDIA_MEDIA_SELECT_PRESSED] = KeyCode::MULTIMEDIA_MEDIA_SELECT;

        map[ExtendedScanCode::MULTIMEDIA_PREVIOUS_TRACK_RELEASED] = KeyCode::MULTIMEDIA_PREVIOUS_TRACK;
        map[ExtendedScanCode::MULTIMEDIA_NEXT_TRACK_RELEASED] = KeyCode::MULTIMEDIA_NEXT_TRACK;
        map[ExtendedScanCode::KEYPAD_ENTER_RELEASED] = KeyCode::KEYPAD_ENTER;
        map[ExtendedScanCode::RIGHT_CTRL_RELEASED] = KeyCode::RIGHT_CTRL;
        map[ExtendedScanCode::MULTIMEDIA_MUTE_RELEASED] = KeyCode::MULTIMEDIA_MUTE;
        map[ExtendedScanCode::MULTIMEDIA_CALCULATOR_RELEASED] = KeyCode::MULTIMEDIA_CALCULATOR;
        map[ExtendedScanCode::MULTIMEDIA_PLAY_RELEASED] = KeyCode::MULTIMEDIA_PLAY;
        map[ExtendedScanCode::MULTIMEDIA_STOP_RELEASED] = KeyCode::MULTIMEDIA_STOP;
        map[ExtendedScanCode::MULTIMEDIA_VOLUME_DOWN_RELEASED] = KeyCode::MULTIMEDIA_VOLUME_DOWN; 
        map[ExtendedScanCode::MULTIMEDIA_VOLUME_UP_RELEASED] = KeyCode::MULTIMEDIA_VOLUME_UP;
        map[ExtendedScanCode::MULTIMEDIA_WWW_HOME_RELEASED] = KeyCode::MULTIMEDIA_WWW_HOME;
        map[ExtendedScanCode::KEYPAD_SLASH_RELEASED] = KeyCode::KEYPAD_SLASH;
        map[ExtendedScanCode::RIGHT_ALT_RELEASED] = KeyCode::RIGHT_ALT;
        map[ExtendedScanCode::HOME_RELEASED] = KeyCode::HOME;
        map[ExtendedScanCode::CURSOR_UP_RELEASED] = KeyCode::CURSOR_UP;
        map[ExtendedScanCode::PAGE_UP_RELEASED] = KeyCode::PAGE_UP;
        map[ExtendedScanCode::CURSOR_LEFT_RELEASED] = KeyCode::CURSOR_LEFT;
        map[ExtendedScanCode::CURSOR_RIGHT_RELEASED] = KeyCode::CURSOR_RIGHT;
        map[ExtendedScanCode::END_RELEASED] = KeyCode::END;
        map[ExtendedScanCode::CURSOR_DOWN_RELEASED] = KeyCode::CURSOR_DOWN;
        map[ExtendedScanCode::PAGE_DOWN_RELEASED] = KeyCode::PAGE_DOWN;
        map[ExtendedScanCode::INSERT_RELEASED] = KeyCode::INSERT;
        map[ExtendedScanCode::DELETE_RELEASED] = KeyCode::DELETE;
        map[ExtendedScanCode::LEFT_GUI_RELEASED] = KeyCode::LEFT_GUI;
        map[ExtendedScanCode::RIGHT_GUI_RELEASED] = KeyCode::RIGHT_GUI;
        map[ExtendedScanCode::APPS_RELEASED] = KeyCode::APPS;
        map[ExtendedScanCode::ACPI_POWER_RELEASED] = KeyCode::ACPI_POWER;
        map[ExtendedScanCode::ACPI_SLEEP_RELEASED] = KeyCode::ACPI_SLEEP;
        map[ExtendedScanCode::ACPI_WAKE_RELEASED] = KeyCode::ACPI_WAKE;
        map[ExtendedScanCode::MULTIMEDIA_WWW_SEARCH_RELEASED] = KeyCode::MULTIMEDIA_WWW_SEARCH;
        map[ExtendedScanCode::MULTIMEDIA_WWW_FAVOURITES_RELEASED] = KeyCode::MULTIMEDIA_WWW_FAVOURITES;
        map[ExtendedScanCode::MULTIMEDIA_WWW_REFRESH_RELEASED] = KeyCode::MULTIMEDIA_WWW_REFRESH;
        map[ExtendedScanCode::MULTIMEDIA_WWW_STOP_RELEASED] = KeyCode::MULTIMEDIA_WWW_STOP;
        map[ExtendedScanCode::MULTIMEDIA_WWW_FORWARD_RELEASED] = KeyCode::MULTIMEDIA_WWW_FORWARD; 
        map[ExtendedScanCode::MULTIMEDIA_WWW_BACK_RELEASED] = KeyCode::MULTIMEDIA_WWW_BACK; 
        map[ExtendedScanCode::MULTIMEDIA_MY_COMPUTER_RELEASED] = KeyCode::MULTIMEDIA_MY_COMPUTER;
        map[ExtendedScanCode::MULTIMEDIA_EMAIL_RELEASED] = KeyCode::MULTIMEDIA_EMAIL;
        map[ExtendedScanCode::MULTIMEDIA_MEDIA_SELECT_RELEASED] = KeyCode::MULTIMEDIA_MEDIA_SELECT;

        return map;
    } ();
    
    inline constexpr ArrayMap<ScanCode, ScanCodeType> scancode_type_map = []() {
        ArrayMap<ScanCode, ScanCodeType> map{ScanCodeType::INVALID};

        map[ScanCode::ESC_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::NUM1_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::NUM2_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::NUM3_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::NUM4_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::NUM5_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::NUM6_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::NUM7_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::NUM8_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::NUM9_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::NUM0_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::MINUS_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::EQUAL_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::BACKSPACE_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::TAB_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::Q_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::W_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::E_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::R_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::T_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::Y_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::U_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::I_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::O_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::P_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::LEFT_SQ_BRACKET_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::RIGHT_SQ_BRACKET_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::ENTER_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::LEFT_CTRL_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::A_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::S_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::D_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::G_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::H_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::J_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::K_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::L_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::SEMICOLON_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::SINGLEQUOTE_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::BACKTICK_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::LEFT_SHIFT_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::BACKSLASH_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::Z_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::X_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::C_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::V_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::B_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::N_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::M_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::COMMA_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::DOT_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::SLASH_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::RIGHT_SHIFT_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_STAR_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::LEFT_ALT_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::SPACE_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::CAPSLOCK_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F1_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F2_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F3_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F4_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F5_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F6_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F7_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F8_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F9_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F10_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::NUMLOCK_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::SCROLLLOCK_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_NUM7_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_NUM8_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_NUM9_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_MINUS_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_NUM4_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_NUM5_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_NUM6_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_PLUS_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_NUM1_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_NUM2_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_NUM3_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_NUM0_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::KEYPAD_DOT_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F11_PRESSED] = ScanCodeType::PRESSED;
        map[ScanCode::F12_PRESSED] = ScanCodeType::PRESSED;

        map[ScanCode::ESC_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::NUM1_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::NUM2_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::NUM3_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::NUM4_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::NUM5_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::NUM6_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::NUM7_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::NUM8_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::NUM9_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::NUM0_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::MINUS_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::EQUAL_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::BACKSPACE_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::TAB_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::Q_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::W_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::E_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::R_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::T_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::Y_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::U_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::I_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::O_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::P_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::LEFT_SQ_BRACKET_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::RIGHT_SQ_BRACKET_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::ENTER_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::LEFT_CTRL_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::A_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::S_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::D_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::G_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::H_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::J_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::K_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::L_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::SEMICOLON_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::SINGLEQUOTE_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::BACKTICK_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::LEFT_SHIFT_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::BACKSLASH_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::Z_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::X_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::C_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::V_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::B_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::N_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::M_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::COMMA_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::DOT_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::SLASH_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::RIGHT_SHIFT_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_STAR_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::LEFT_ALT_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::SPACE_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::CAPSLOCK_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F1_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F2_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F3_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F4_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F5_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F6_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F7_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F8_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F9_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F10_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::NUMLOCK_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::SCROLLLOCK_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_NUM7_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_NUM8_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_NUM9_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_MINUS_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_NUM4_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_NUM5_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_NUM6_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_PLUS_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_NUM1_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_NUM2_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_NUM3_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_NUM0_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::KEYPAD_DOT_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F11_RELEASED] = ScanCodeType::RELEASED;
        map[ScanCode::F12_RELEASED] = ScanCodeType::RELEASED;

        map[ScanCode::EXTENDED_SCANCODE_START] = ScanCodeType::EXTENDED;

        return map;
    } ();
    
    inline constexpr ArrayMap<ExtendedScanCode, ScanCodeType> extended_scancode_type_map = []() {
        ArrayMap<ExtendedScanCode, ScanCodeType> map{ScanCodeType::INVALID};

        map[ExtendedScanCode::MULTIMEDIA_PREVIOUS_TRACK_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_NEXT_TRACK_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::KEYPAD_ENTER_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::RIGHT_CTRL_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_MUTE_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_CALCULATOR_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_PLAY_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_STOP_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_VOLUME_DOWN_PRESSED] = ScanCodeType::PRESSED; 
        map[ExtendedScanCode::MULTIMEDIA_VOLUME_UP_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_HOME_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::KEYPAD_SLASH_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::RIGHT_ALT_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::HOME_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::CURSOR_UP_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::PAGE_UP_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::CURSOR_LEFT_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::CURSOR_RIGHT_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::END_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::CURSOR_DOWN_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::PAGE_DOWN_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::INSERT_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::DELETE_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::LEFT_GUI_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::RIGHT_GUI_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::APPS_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::ACPI_POWER_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::ACPI_SLEEP_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::ACPI_WAKE_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_SEARCH_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_FAVOURITES_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_REFRESH_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_STOP_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_FORWARD_PRESSED] = ScanCodeType::PRESSED; 
        map[ExtendedScanCode::MULTIMEDIA_WWW_BACK_PRESSED] = ScanCodeType::PRESSED; 
        map[ExtendedScanCode::MULTIMEDIA_MY_COMPUTER_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_EMAIL_PRESSED] = ScanCodeType::PRESSED;
        map[ExtendedScanCode::MULTIMEDIA_MEDIA_SELECT_PRESSED] = ScanCodeType::PRESSED;

        map[ExtendedScanCode::MULTIMEDIA_PREVIOUS_TRACK_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_NEXT_TRACK_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::KEYPAD_ENTER_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::RIGHT_CTRL_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_MUTE_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_CALCULATOR_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_PLAY_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_STOP_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_VOLUME_DOWN_RELEASED] = ScanCodeType::RELEASED; 
        map[ExtendedScanCode::MULTIMEDIA_VOLUME_UP_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_HOME_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::KEYPAD_SLASH_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::RIGHT_ALT_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::HOME_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::CURSOR_UP_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::PAGE_UP_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::CURSOR_LEFT_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::CURSOR_RIGHT_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::END_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::CURSOR_DOWN_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::PAGE_DOWN_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::INSERT_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::DELETE_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::LEFT_GUI_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::RIGHT_GUI_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::APPS_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::ACPI_POWER_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::ACPI_SLEEP_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::ACPI_WAKE_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_SEARCH_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_FAVOURITES_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_REFRESH_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_STOP_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_WWW_FORWARD_RELEASED] = ScanCodeType::RELEASED; 
        map[ExtendedScanCode::MULTIMEDIA_WWW_BACK_RELEASED] = ScanCodeType::RELEASED; 
        map[ExtendedScanCode::MULTIMEDIA_MY_COMPUTER_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_EMAIL_RELEASED] = ScanCodeType::RELEASED;
        map[ExtendedScanCode::MULTIMEDIA_MEDIA_SELECT_RELEASED] = ScanCodeType::RELEASED;

        return map;
    } ();

    inline constexpr ArrayMap<KeyCode, char> keycode_char_map = []() {
        ArrayMap<KeyCode, char> map{0};

        map[KeyCode::BACKTICK] = '`';
        map[KeyCode::NUM1] = '1';
        map[KeyCode::NUM2] = '2';
        map[KeyCode::NUM3] = '3';
        map[KeyCode::NUM4] = '4';
        map[KeyCode::NUM5] = '5';
        map[KeyCode::NUM6] = '6';
        map[KeyCode::NUM7] = '7';
        map[KeyCode::NUM8] = '8';
        map[KeyCode::NUM9] = '9';
        map[KeyCode::NUM0] = '0';
        map[KeyCode::MINUS] = '-';
        map[KeyCode::EQUAL] = '=';
        map[KeyCode::Q] = 'q';
        map[KeyCode::W] = 'w';
        map[KeyCode::E] = 'e';
        map[KeyCode::R] = 'r';
        map[KeyCode::T] = 't';
        map[KeyCode::Y] = 'y';
        map[KeyCode::U] = 'u';
        map[KeyCode::I] = 'i';
        map[KeyCode::O] = 'o';
        map[KeyCode::P] = 'p';
        map[KeyCode::LEFT_SQ_BRACKET] = '[';
        map[KeyCode::RIGHT_SQ_BRACKET] = ']';
        map[KeyCode::A] = 'a';
        map[KeyCode::S] = 's';
        map[KeyCode::D] = 'd';
        map[KeyCode::F] = 'f';
        map[KeyCode::G] = 'g';
        map[KeyCode::H] = 'h';
        map[KeyCode::J] = 'j';
        map[KeyCode::K] = 'k';
        map[KeyCode::L] = 'l';
        map[KeyCode::SEMICOLON] = ';';
        map[KeyCode::SINGLEQUOTE] = '\'';
        map[KeyCode::BACKSLASH] = '\\';
        map[KeyCode::Z] = 'z';
        map[KeyCode::X] = 'x';
        map[KeyCode::C] = 'c';
        map[KeyCode::V] = 'v';
        map[KeyCode::B] = 'b';
        map[KeyCode::N] = 'n';
        map[KeyCode::M] = 'm';
        map[KeyCode::COMMA] = ',';
        map[KeyCode::DOT] = '.';
        map[KeyCode::SLASH] = '/';
        map[KeyCode::SPACE] = ' ';
    
        map[KeyCode::KEYPAD_SLASH] = '/';
        map[KeyCode::KEYPAD_STAR] = '*';
        map[KeyCode::KEYPAD_NUM7] = '7';
        map[KeyCode::KEYPAD_NUM8] = '8';
        map[KeyCode::KEYPAD_NUM9] = '9';
        map[KeyCode::KEYPAD_MINUS] = '-';
        map[KeyCode::KEYPAD_NUM4] = '4';
        map[KeyCode::KEYPAD_NUM5] = '5';
        map[KeyCode::KEYPAD_NUM6] = '6';
        map[KeyCode::KEYPAD_PLUS] = '+';
        map[KeyCode::KEYPAD_NUM1] = '1';
        map[KeyCode::KEYPAD_NUM2] = '2';
        map[KeyCode::KEYPAD_NUM3] = '3';
        map[KeyCode::KEYPAD_NUM0] = '0';
        map[KeyCode::KEYPAD_DOT] = '.';

        return map;
    } ();

    inline constexpr ArrayMap<KeyCode, char> keycode_shift_char_map = []() {
        ArrayMap<KeyCode, char> map{0};

        map[KeyCode::BACKTICK] = '~';
        map[KeyCode::NUM1] = '!';
        map[KeyCode::NUM2] = '@';
        map[KeyCode::NUM3] = '#';
        map[KeyCode::NUM4] = '$';
        map[KeyCode::NUM5] = '%';
        map[KeyCode::NUM6] = '^';
        map[KeyCode::NUM7] = '&';
        map[KeyCode::NUM8] = '*';
        map[KeyCode::NUM9] = '(';
        map[KeyCode::NUM0] = ')';
        map[KeyCode::MINUS] = '_';
        map[KeyCode::EQUAL] = '+';
        map[KeyCode::Q] = 'Q';
        map[KeyCode::W] = 'W';
        map[KeyCode::E] = 'E';
        map[KeyCode::R] = 'R';
        map[KeyCode::T] = 'T';
        map[KeyCode::Y] = 'Y';
        map[KeyCode::U] = 'U';
        map[KeyCode::I] = 'I';
        map[KeyCode::O] = 'O';
        map[KeyCode::P] = 'P';
        map[KeyCode::LEFT_SQ_BRACKET] = '{';
        map[KeyCode::RIGHT_SQ_BRACKET] = '}';
        map[KeyCode::A] = 'A';
        map[KeyCode::S] = 'S';
        map[KeyCode::D] = 'D';
        map[KeyCode::F] = 'F';
        map[KeyCode::G] = 'G';
        map[KeyCode::H] = 'H';
        map[KeyCode::J] = 'J';
        map[KeyCode::K] = 'K';
        map[KeyCode::L] = 'L';
        map[KeyCode::SEMICOLON] = ':';
        map[KeyCode::SINGLEQUOTE] = '"';
        map[KeyCode::BACKSLASH] = '|';
        map[KeyCode::Z] = 'Z';
        map[KeyCode::X] = 'X';
        map[KeyCode::C] = 'C';
        map[KeyCode::V] = 'V';
        map[KeyCode::B] = 'B';
        map[KeyCode::N] = 'N';
        map[KeyCode::M] = 'M';
        map[KeyCode::COMMA] = '<';
        map[KeyCode::DOT] = '>';
        map[KeyCode::SLASH] = '?';
        map[KeyCode::SPACE] = ' ';
    
        map[KeyCode::KEYPAD_SLASH] = '/';
        map[KeyCode::KEYPAD_STAR] = '*';
        map[KeyCode::KEYPAD_NUM7] = '7';
        map[KeyCode::KEYPAD_NUM8] = '8';
        map[KeyCode::KEYPAD_NUM9] = '9';
        map[KeyCode::KEYPAD_MINUS] = '-';
        map[KeyCode::KEYPAD_NUM4] = '4';
        map[KeyCode::KEYPAD_NUM5] = '5';
        map[KeyCode::KEYPAD_NUM6] = '6';
        map[KeyCode::KEYPAD_PLUS] = '+';
        map[KeyCode::KEYPAD_NUM1] = '1';
        map[KeyCode::KEYPAD_NUM2] = '2';
        map[KeyCode::KEYPAD_NUM3] = '3';
        map[KeyCode::KEYPAD_NUM0] = '0';
        map[KeyCode::KEYPAD_DOT] = '.';

        return map;
    } ();

    inline constexpr ArrayMap<KeyCode, char> keycode_caps_char_map = []() {
        ArrayMap<KeyCode, char> map{0};

        map[KeyCode::BACKTICK] = '`';
        map[KeyCode::NUM1] = '1';
        map[KeyCode::NUM2] = '2';
        map[KeyCode::NUM3] = '3';
        map[KeyCode::NUM4] = '4';
        map[KeyCode::NUM5] = '5';
        map[KeyCode::NUM6] = '6';
        map[KeyCode::NUM7] = '7';
        map[KeyCode::NUM8] = '8';
        map[KeyCode::NUM9] = '9';
        map[KeyCode::NUM0] = '0';
        map[KeyCode::MINUS] = '-';
        map[KeyCode::EQUAL] = '=';
        map[KeyCode::Q] = 'Q';
        map[KeyCode::W] = 'W';
        map[KeyCode::E] = 'E';
        map[KeyCode::R] = 'R';
        map[KeyCode::T] = 'T';
        map[KeyCode::Y] = 'Y';
        map[KeyCode::U] = 'U';
        map[KeyCode::I] = 'I';
        map[KeyCode::O] = 'O';
        map[KeyCode::P] = 'P';
        map[KeyCode::LEFT_SQ_BRACKET] = '[';
        map[KeyCode::RIGHT_SQ_BRACKET] = ']';
        map[KeyCode::A] = 'A';
        map[KeyCode::S] = 'S';
        map[KeyCode::D] = 'D';
        map[KeyCode::F] = 'F';
        map[KeyCode::G] = 'G';
        map[KeyCode::H] = 'H';
        map[KeyCode::J] = 'J';
        map[KeyCode::K] = 'K';
        map[KeyCode::L] = 'L';
        map[KeyCode::SEMICOLON] = ';';
        map[KeyCode::SINGLEQUOTE] = '\'';
        map[KeyCode::BACKSLASH] = '\\';
        map[KeyCode::Z] = 'Z';
        map[KeyCode::X] = 'X';
        map[KeyCode::C] = 'C';
        map[KeyCode::V] = 'V';
        map[KeyCode::B] = 'B';
        map[KeyCode::N] = 'N';
        map[KeyCode::M] = 'M';
        map[KeyCode::COMMA] = ',';
        map[KeyCode::DOT] = '.';
        map[KeyCode::SLASH] = '/';
        map[KeyCode::SPACE] = ' ';
    
        map[KeyCode::KEYPAD_SLASH] = '/';
        map[KeyCode::KEYPAD_STAR] = '*';
        map[KeyCode::KEYPAD_NUM7] = '7';
        map[KeyCode::KEYPAD_NUM8] = '8';
        map[KeyCode::KEYPAD_NUM9] = '9';
        map[KeyCode::KEYPAD_MINUS] = '-';
        map[KeyCode::KEYPAD_NUM4] = '4';
        map[KeyCode::KEYPAD_NUM5] = '5';
        map[KeyCode::KEYPAD_NUM6] = '6';
        map[KeyCode::KEYPAD_PLUS] = '+';
        map[KeyCode::KEYPAD_NUM1] = '1';
        map[KeyCode::KEYPAD_NUM2] = '2';
        map[KeyCode::KEYPAD_NUM3] = '3';
        map[KeyCode::KEYPAD_NUM0] = '0';
        map[KeyCode::KEYPAD_DOT] = '.';

        return map;
    } ();

    inline constexpr ArrayMap<KeyCode, char> keycode_inverted_caps_char_map = []() {
        ArrayMap<KeyCode, char> map{0};

        map[KeyCode::BACKTICK] = '~';
        map[KeyCode::NUM1] = '!';
        map[KeyCode::NUM2] = '@';
        map[KeyCode::NUM3] = '#';
        map[KeyCode::NUM4] = '$';
        map[KeyCode::NUM5] = '%';
        map[KeyCode::NUM6] = '^';
        map[KeyCode::NUM7] = '&';
        map[KeyCode::NUM8] = '*';
        map[KeyCode::NUM9] = '(';
        map[KeyCode::NUM0] = ')';
        map[KeyCode::MINUS] = '_';
        map[KeyCode::EQUAL] = '+';
        map[KeyCode::Q] = 'q';
        map[KeyCode::W] = 'w';
        map[KeyCode::E] = 'e';
        map[KeyCode::R] = 'r';
        map[KeyCode::T] = 't';
        map[KeyCode::Y] = 'y';
        map[KeyCode::U] = 'u';
        map[KeyCode::I] = 'i';
        map[KeyCode::O] = 'o';
        map[KeyCode::P] = 'p';
        map[KeyCode::LEFT_SQ_BRACKET] = '{';
        map[KeyCode::RIGHT_SQ_BRACKET] = '}';
        map[KeyCode::A] = 'a';
        map[KeyCode::S] = 's';
        map[KeyCode::D] = 'd';
        map[KeyCode::F] = 'f';
        map[KeyCode::G] = 'g';
        map[KeyCode::H] = 'h';
        map[KeyCode::J] = 'j';
        map[KeyCode::K] = 'k';
        map[KeyCode::L] = 'l';
        map[KeyCode::SEMICOLON] = ':';
        map[KeyCode::SINGLEQUOTE] = '"';
        map[KeyCode::BACKSLASH] = '|';
        map[KeyCode::Z] = 'z';
        map[KeyCode::X] = 'x';
        map[KeyCode::C] = 'c';
        map[KeyCode::V] = 'v';
        map[KeyCode::B] = 'b';
        map[KeyCode::N] = 'n';
        map[KeyCode::M] = 'm';
        map[KeyCode::COMMA] = '<';
        map[KeyCode::DOT] = '>';
        map[KeyCode::SLASH] = '?';
        map[KeyCode::SPACE] = ' ';
    
        map[KeyCode::KEYPAD_SLASH] = '/';
        map[KeyCode::KEYPAD_STAR] = '*';
        map[KeyCode::KEYPAD_NUM7] = '7';
        map[KeyCode::KEYPAD_NUM8] = '8';
        map[KeyCode::KEYPAD_NUM9] = '9';
        map[KeyCode::KEYPAD_MINUS] = '-';
        map[KeyCode::KEYPAD_NUM4] = '4';
        map[KeyCode::KEYPAD_NUM5] = '5';
        map[KeyCode::KEYPAD_NUM6] = '6';
        map[KeyCode::KEYPAD_PLUS] = '+';
        map[KeyCode::KEYPAD_NUM1] = '1';
        map[KeyCode::KEYPAD_NUM2] = '2';
        map[KeyCode::KEYPAD_NUM3] = '3';
        map[KeyCode::KEYPAD_NUM0] = '0';
        map[KeyCode::KEYPAD_DOT] = '.';

        return map;
    } ();

}
