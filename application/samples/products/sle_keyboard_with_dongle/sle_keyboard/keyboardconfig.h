#ifndef _KEYSCAN_TASK_H_
#define _KEYSCAN_TASK_H_

#define HID_KEY_NONE 0x00

#define HID_KEY_A 0x04
#define HID_KEY_B 0x05
#define HID_KEY_C 0x06
#define HID_KEY_D 0x07
#define HID_KEY_E 0x08
#define HID_KEY_F 0x09
#define HID_KEY_G 0x0A
#define HID_KEY_H 0x0B
#define HID_KEY_I 0x0C
#define HID_KEY_J 0x0D
#define HID_KEY_K 0x0E
#define HID_KEY_L 0x0F
#define HID_KEY_M 0x10
#define HID_KEY_N 0x11
#define HID_KEY_O 0x12
#define HID_KEY_P 0x13
#define HID_KEY_Q 0x14
#define HID_KEY_R 0x15
#define HID_KEY_S 0x16
#define HID_KEY_T 0x17
#define HID_KEY_U 0x18
#define HID_KEY_V 0x19
#define HID_KEY_W 0x1A
#define HID_KEY_X 0x1B
#define HID_KEY_Y 0x1C
#define HID_KEY_Z 0x1D

#define HID_KEY_1 0x1E
#define HID_KEY_2 0x1F
#define HID_KEY_3 0x20
#define HID_KEY_4 0x21
#define HID_KEY_5 0x22
#define HID_KEY_6 0x23
#define HID_KEY_7 0x24
#define HID_KEY_8 0x25
#define HID_KEY_9 0x26
#define HID_KEY_0 0x27

#define HID_KEY_ENTER 0x28
#define HID_KEY_ESC 0x29
#define HID_KEY_BACKSPACE 0x2A
#define HID_KEY_TAB 0x2B
#define HID_KEY_SPACEBAR 0x2C
#define HID_KEY_MINUS 0x2D         // - _
#define HID_KEY_EQUALS 0x2E        // = +
#define HID_KEY_LEFT_BRACKET 0x2F  // [ {
#define HID_KEY_RIGHT_BRACKET 0x30 // ] }
#define HID_KEY_BACKSLASH 0x31     // \ |
#define HID_KEY_NON_US_HASH 0x32   // Non-US # ~
#define HID_KEY_SEMICOLON 0x33     // ; :
#define HID_KEY_APOSTROPHE 0x34    // ' "
#define HID_KEY_GRAVE_ACCENT 0x35  // ` ~
#define HID_KEY_COMMA 0x36         // , <
#define HID_KEY_PERIOD 0x37        // . >
#define HID_KEY_SLASH 0x38         // / ?
#define HID_KEY_CAPS_LOCK 0x39     // Caps Lock

#define HID_KEY_F1 0x3A
#define HID_KEY_F2 0x3B
#define HID_KEY_F3 0x3C
#define HID_KEY_F4 0x3D
#define HID_KEY_F5 0x3E
#define HID_KEY_F6 0x3F
#define HID_KEY_F7 0x40
#define HID_KEY_F8 0x41
#define HID_KEY_F9 0x42
#define HID_KEY_F10 0x43
#define HID_KEY_F11 0x44
#define HID_KEY_F12 0x45

#define HID_KEY_PRINT_SCREEN 0x46
#define HID_KEY_SCROLL_LOCK 0x47
#define HID_KEY_PAUSE 0x48
#define HID_KEY_INSERT 0x49
#define HID_KEY_HOME 0x4A
#define HID_KEY_PAGE_UP 0x4B
#define HID_KEY_DELETE 0x4C
#define HID_KEY_END 0x4D
#define HID_KEY_PAGE_DOWN 0x4E

#define HID_KEY_RIGHT_ARROW 0x4F
#define HID_KEY_LEFT_ARROW 0x50
#define HID_KEY_DOWN_ARROW 0x51
#define HID_KEY_UP_ARROW 0x52

#define HID_KEY_NUM_LOCK 0x53
#define HID_KEYPAD_SLASH 0x54
#define HID_KEYPAD_ASTERISK 0x55
#define HID_KEYPAD_MINUS 0x56
#define HID_KEYPAD_PLUS 0x57

#define HID_KEY_CTRL_LEFT 0xE0   // Left Control
#define HID_KEY_SHIFT_LEFT 0xE1  // Left Shift
#define HID_KEY_ALT_LEFT 0xE2    // Left Alt
#define HID_KEY_GUI_LEFT 0xE3    // Left GUI (Windows/Command key)
#define HID_KEY_CTRL_RIGHT 0xE4  // Right Control
#define HID_KEY_SHIFT_RIGHT 0xE5 // Right Shift
#define HID_KEY_ALT_RIGHT 0xE6   // Right Alt
#define HID_KEY_GUI_RIGHT 0xE7   // Right GUI (Windows/Command key)

#define HID_KEY_FN 0x65

#define KEYSCAN_MAP                                                                                                    \
    {                                                                                                                  \
        {HID_KEY_F11,        HID_KEY_F12,         HID_KEY_6,        HID_KEY_PAGE_DOWN,                                 \
         HID_KEY_APOSTROPHE, HID_KEY_RIGHT_ARROW, HID_KEY_SPACEBAR, HID_KEY_NONE},                                     \
            {HID_KEY_F10,       HID_KEY_PRINT_SCREEN, HID_KEY_5,        HID_KEY_ENTER,                                 \
             HID_KEY_SEMICOLON, HID_KEY_DOWN_ARROW,   HID_KEY_ALT_LEFT, HID_KEY_NONE},                                 \
            {HID_KEY_F9, HID_KEY_PAUSE,      HID_KEY_4,        HID_KEY_PAGE_UP,                                        \
             HID_KEY_L,  HID_KEY_LEFT_ARROW, HID_KEY_GUI_LEFT, HID_KEY_NONE},                                          \
            {HID_KEY_F8, HID_KEY_DELETE,     HID_KEY_3,         HID_KEY_BACKSLASH,                                     \
             HID_KEY_K,  HID_KEY_CTRL_RIGHT, HID_KEY_CTRL_LEFT, HID_KEY_NONE},                                         \
            {HID_KEY_F7, HID_KEY_HOME, HID_KEY_2, HID_KEY_RIGHT_BRACKET,                                               \
             HID_KEY_J,  HID_KEY_FN,   HID_KEY_M, HID_KEY_NONE},                                                       \
            {HID_KEY_F6, HID_KEY_BACKSPACE, HID_KEY_1, HID_KEY_LEFT_BRACKET,                                           \
             HID_KEY_H,  HID_KEY_ALT_RIGHT, HID_KEY_N, HID_KEY_NONE},                                                  \
            {HID_KEY_F5,  HID_KEY_EQUALS, HID_KEY_GRAVE_ACCENT, HID_KEY_P, HID_KEY_G,                                  \
             HID_KEY_END, HID_KEY_B,      HID_KEY_NONE},                                                               \
            {HID_KEY_F4, HID_KEY_MINUS, HID_KEY_TAB, HID_KEY_O, HID_KEY_F, HID_KEY_UP_ARROW, HID_KEY_V, HID_KEY_NONE}, \
            {HID_KEY_F3, HID_KEY_0, HID_KEY_W, HID_KEY_I, HID_KEY_D, HID_KEY_SHIFT_RIGHT, HID_KEY_C, HID_KEY_NONE},    \
            {HID_KEY_F2, HID_KEY_9, HID_KEY_Q, HID_KEY_U, HID_KEY_S, HID_KEY_SLASH, HID_KEY_X, HID_KEY_NONE},          \
            {HID_KEY_F1, HID_KEY_8, HID_KEY_E, HID_KEY_Y, HID_KEY_A, HID_KEY_PERIOD, HID_KEY_Z, HID_KEY_NONE},         \
            {HID_KEY_ESC,       HID_KEY_7,     HID_KEY_R,          HID_KEY_T,                                          \
             HID_KEY_CAPS_LOCK, HID_KEY_COMMA, HID_KEY_SHIFT_LEFT, HID_KEY_NONE},                                      \
            {HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,                                                   \
             HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE},                                                  \
            {HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,                                                   \
             HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE},                                                  \
            {HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,                                                   \
             HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE},                                                  \
        {                                                                                                              \
            HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,          \
                HID_KEY_NONE                                                                                           \
        }                                                                                                              \
    }

// void *keyscan_task(const char *arg);

#endif /* _KEYSCAN_TASK_H_ */