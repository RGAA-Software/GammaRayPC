//
// Created by RGAA on 2023/8/13.
//

#include "qt_key_converter.h"

#include "tc_common/log.h"

namespace tc
{

    QtKeyConverter::QtKeyConverter() {

        key_mapping_.insert(Qt::Key_Left,0x25);
        key_mapping_.insert(Qt::Key_Up,0x26);
        key_mapping_.insert(Qt::Key_Right,0x27);
        key_mapping_.insert(Qt::Key_Down,0x28);
        key_mapping_.insert(Qt::Key_Backspace,0x08);
        key_mapping_.insert(Qt::Key_Tab,0x09);
        key_mapping_.insert(Qt::Key_Clear,0x0C);
        key_mapping_.insert(Qt::Key_Return,0x0D);
        key_mapping_.insert(Qt::Key_Enter,0x0D);
        key_mapping_.insert(Qt::Key_Shift,0x10);
        key_mapping_.insert(Qt::Key_Control,0x11);
        key_mapping_.insert(Qt::Key_Alt,0x12);
        key_mapping_.insert(Qt::Key_Pause,0x13);
        key_mapping_.insert(Qt::Key_CapsLock,0x14);
        key_mapping_.insert(Qt::Key_Escape,0x1B);
        key_mapping_.insert(Qt::Key_Space,0x20);
        key_mapping_.insert(Qt::Key_PageUp,0x21);
        key_mapping_.insert(Qt::Key_PageDown,0x22);
        key_mapping_.insert(Qt::Key_End,0x23);
        key_mapping_.insert(Qt::Key_Home,0x24);
        key_mapping_.insert(Qt::Key_Select,0x29);
        key_mapping_.insert(Qt::Key_Print,0x2A);
        key_mapping_.insert(Qt::Key_Execute,0x2B);
        key_mapping_.insert(Qt::Key_Printer,0x2C);
        key_mapping_.insert(Qt::Key_Insert,0x2D);
        key_mapping_.insert(Qt::Key_Delete,0x2E);
        key_mapping_.insert(Qt::Key_Help,0x2F);
        key_mapping_.insert(Qt::Key_0,0x30);
        key_mapping_.insert(Qt::Key_ParenRight,0x30); // )
        key_mapping_.insert(Qt::Key_1,0x31);
        key_mapping_.insert(Qt::Key_Exclam,0x31); // !
        key_mapping_.insert(Qt::Key_2,0x32);
        key_mapping_.insert(Qt::Key_At,0x32); // @
        key_mapping_.insert(Qt::Key_3,0x33);
        key_mapping_.insert(Qt::Key_NumberSign,0x33); // #
        key_mapping_.insert(Qt::Key_4,0x34);
        key_mapping_.insert(Qt::Key_Dollar,0x34); // $
        key_mapping_.insert(Qt::Key_5,0x35);
        key_mapping_.insert(Qt::Key_Percent,0x35); // %
        key_mapping_.insert(Qt::Key_6,0x36);
        key_mapping_.insert(Qt::Key_AsciiCircum,0x36); // ^
        key_mapping_.insert(Qt::Key_7,0x37);
        key_mapping_.insert(Qt::Key_Ampersand,0x37); // &
        key_mapping_.insert(Qt::Key_8,0x38);
        key_mapping_.insert(Qt::Key_Asterisk,0x38); // *
        key_mapping_.insert(Qt::Key_9,0x39);
        key_mapping_.insert(Qt::Key_ParenLeft,0x39); // (
        key_mapping_.insert(Qt::Key_A,0x41);
        key_mapping_.insert(Qt::Key_B,0x42);
        key_mapping_.insert(Qt::Key_C,0x43);
        key_mapping_.insert(Qt::Key_D,0x44);
        key_mapping_.insert(Qt::Key_E,0x45);
        key_mapping_.insert(Qt::Key_F,0x46);
        key_mapping_.insert(Qt::Key_G,0x47);
        key_mapping_.insert(Qt::Key_H,0x48);
        key_mapping_.insert(Qt::Key_I,0x49);
        key_mapping_.insert(Qt::Key_J,0x4A);
        key_mapping_.insert(Qt::Key_K,0x4B);
        key_mapping_.insert(Qt::Key_L,0x4C);
        key_mapping_.insert(Qt::Key_M,0x4D);
        key_mapping_.insert(Qt::Key_N,0x4E);
        key_mapping_.insert(Qt::Key_O,0x4F);
        key_mapping_.insert(Qt::Key_P,0x50);
        key_mapping_.insert(Qt::Key_Q,0x51);
        key_mapping_.insert(Qt::Key_R,0x52);
        key_mapping_.insert(Qt::Key_S,0x53);
        key_mapping_.insert(Qt::Key_T,0x54);
        key_mapping_.insert(Qt::Key_U,0x55);
        key_mapping_.insert(Qt::Key_V,0x56);
        key_mapping_.insert(Qt::Key_W,0x57);
        key_mapping_.insert(Qt::Key_X,0x58);
        key_mapping_.insert(Qt::Key_Y,0x59);
        key_mapping_.insert(Qt::Key_Z,0x5A);
        key_mapping_.insert(Qt::Key_multiply,0x6A);
        key_mapping_.insert(Qt::Key_F1,0x70);
        key_mapping_.insert(Qt::Key_F2,0x71);
        key_mapping_.insert(Qt::Key_F3,0x72);
        key_mapping_.insert(Qt::Key_F4,0x73);
        key_mapping_.insert(Qt::Key_F5,0x74);
        key_mapping_.insert(Qt::Key_F6,0x75);
        key_mapping_.insert(Qt::Key_F7,0x76);
        key_mapping_.insert(Qt::Key_F8,0x77);
        key_mapping_.insert(Qt::Key_F9,0x78);
        key_mapping_.insert(Qt::Key_F10,0x79);
        key_mapping_.insert(Qt::Key_F11,0x7A);
        key_mapping_.insert(Qt::Key_F12,0x7B);
        key_mapping_.insert(Qt::Key_F13,0x7C);
        key_mapping_.insert(Qt::Key_F14,0x7D);
        key_mapping_.insert(Qt::Key_F15,0x7E);
        key_mapping_.insert(Qt::Key_F16,0x7F);
        key_mapping_.insert(Qt::Key_F17,0x80);
        key_mapping_.insert(Qt::Key_F18,0x81);
        key_mapping_.insert(Qt::Key_F19,0x82);
        key_mapping_.insert(Qt::Key_F20,0x83);
        key_mapping_.insert(Qt::Key_F21,0x84);
        key_mapping_.insert(Qt::Key_F22,0x85);
        key_mapping_.insert(Qt::Key_F23,0x86);
        key_mapping_.insert(Qt::Key_F24,0x87);
        key_mapping_.insert(Qt::Key_NumLock,0x90);
        key_mapping_.insert(Qt::Key_ScrollLock,0x91);
        key_mapping_.insert(Qt::Key_VolumeDown,0xAE);
        key_mapping_.insert(Qt::Key_VolumeUp,0xAF);
        key_mapping_.insert(Qt::Key_VolumeMute,0xAD);
        key_mapping_.insert(Qt::Key_MediaStop,0xB2);
        key_mapping_.insert(Qt::Key_MediaPlay,0xB3);
        key_mapping_.insert(Qt::Key_Plus,0xBB); // +
        key_mapping_.insert(Qt::Key_Minus,0xBD); // -
        key_mapping_.insert(Qt::Key_Underscore,0xBD); // _
        key_mapping_.insert(Qt::Key_Equal,0xBB); // =
        key_mapping_.insert(Qt::Key_Semicolon,0xBA); // ;
        key_mapping_.insert(Qt::Key_Colon,0xBA); // :
        key_mapping_.insert(Qt::Key_Comma,0xBC); // ,
        key_mapping_.insert(Qt::Key_Less,0xBC); // <
        key_mapping_.insert(Qt::Key_Period,0xBE); // .
        key_mapping_.insert(Qt::Key_Greater,0xBE); // >
        key_mapping_.insert(Qt::Key_Slash,0xBF);  // /
        key_mapping_.insert(Qt::Key_Question,0xBF); // ?
        key_mapping_.insert(Qt::Key_BracketLeft,0xDB); // [
        key_mapping_.insert(Qt::Key_BraceLeft,0xDB); // {
        key_mapping_.insert(Qt::Key_BracketRight,0xDD); // ]
        key_mapping_.insert(Qt::Key_BraceRight,0xDD); // }
        key_mapping_.insert(Qt::Key_Bar,0xDC); // |
        key_mapping_.insert(Qt::Key_Backslash,0xDC); // '\\'
        key_mapping_.insert(Qt::Key_Apostrophe,0xDE); // '
        key_mapping_.insert(Qt::Key_QuoteDbl,0xDE); // "
        key_mapping_.insert(Qt::Key_QuoteLeft,0xC0); // `
        key_mapping_.insert(Qt::Key_AsciiTilde,0xC0); // ~

    }

    int QtKeyConverter::ToVK(int qt_key) {
        if (key_mapping_.find(qt_key) != key_mapping_.end()) {
            return key_mapping_[qt_key];
        }
        return -1;
    }

    std::map<int, bool> QtKeyConverter::GetSysKeyStatus() {
        std::map<int, bool> status;
#if WIN32
        auto func_is_pressed = [](int vk) -> bool {
            return GetKeyState(vk) < 0;
        };

        status.insert(std::make_pair(VK_SHIFT, func_is_pressed(VK_SHIFT)));
        status.insert(std::make_pair(VK_LSHIFT, func_is_pressed(VK_LSHIFT)));
        status.insert(std::make_pair(VK_RSHIFT, func_is_pressed(VK_RSHIFT)));
        status.insert(std::make_pair(VK_SHIFT, func_is_pressed(VK_MBUTTON)));
        status.insert(std::make_pair(VK_CAPITAL, func_is_pressed(VK_CAPITAL)));
        status.insert(std::make_pair(VK_CONTROL, func_is_pressed(VK_CONTROL)));
        status.insert(std::make_pair(VK_MENU, func_is_pressed(VK_MENU)));
        status.insert(std::make_pair(VK_LMENU, func_is_pressed(VK_LMENU)));
        status.insert(std::make_pair(VK_RMENU, func_is_pressed(VK_RMENU)));
        status.insert(std::make_pair(VK_LBUTTON, func_is_pressed(VK_LBUTTON)));
        status.insert(std::make_pair(VK_RBUTTON, func_is_pressed(VK_RBUTTON)));
        status.insert(std::make_pair(VK_MBUTTON, func_is_pressed(VK_MBUTTON)));
#endif
        return status;
    }

}
