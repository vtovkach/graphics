#pragma once

#include <cstdint>

using Keycode = std::uint32_t;

#define PG_UNKNOWN                0x00000000u /**< 0 */
#define PG_RETURN                 0x0000000du /**< '\r' */
#define PG_ESCAPE                 0x0000001bu /**< '\x1B' */
#define PG_BACKSPACE              0x00000008u /**< '\b' */
#define PG_TAB                    0x00000009u /**< '\t' */
#define PG_SPACE                  0x00000020u /**< ' ' */
#define PG_0                      0x00000030u /**< '0' */
#define PG_1                      0x00000031u /**< '1' */
#define PG_2                      0x00000032u /**< '2' */
#define PG_3                      0x00000033u /**< '3' */
#define PG_4                      0x00000034u /**< '4' */
#define PG_5                      0x00000035u /**< '5' */
#define PG_6                      0x00000036u /**< '6' */
#define PG_7                      0x00000037u /**< '7' */
#define PG_8                      0x00000038u /**< '8' */
#define PG_9                      0x00000039u /**< '9' */
#define PG_A                      0x00000061u /**< 'a' */
#define PG_B                      0x00000062u /**< 'b' */
#define PG_C                      0x00000063u /**< 'c' */
#define PG_D                      0x00000064u /**< 'd' */
#define PG_E                      0x00000065u /**< 'e' */
#define PG_F                      0x00000066u /**< 'f' */
#define PG_G                      0x00000067u /**< 'g' */
#define PG_H                      0x00000068u /**< 'h' */
#define PG_I                      0x00000069u /**< 'i' */
#define PG_J                      0x0000006au /**< 'j' */
#define PG_K                      0x0000006bu /**< 'k' */
#define PG_L                      0x0000006cu /**< 'l' */
#define PG_M                      0x0000006du /**< 'm' */
#define PG_N                      0x0000006eu /**< 'n' */
#define PG_O                      0x0000006fu /**< 'o' */
#define PG_P                      0x00000070u /**< 'p' */
#define PG_Q                      0x00000071u /**< 'q' */
#define PG_R                      0x00000072u /**< 'r' */
#define PG_S                      0x00000073u /**< 's' */
#define PG_T                      0x00000074u /**< 't' */
#define PG_U                      0x00000075u /**< 'u' */
#define PG_V                      0x00000076u /**< 'v' */
#define PG_W                      0x00000077u /**< 'w' */
#define PG_X                      0x00000078u /**< 'x' */
#define PG_Y                      0x00000079u /**< 'y' */
#define PG_Z                      0x0000007au /**< 'z' */
#define PG_DELETE                 0x0000007fu /**< '\x7F' */
#define PG_F1                     0x4000003au
#define PG_F2                     0x4000003bu
#define PG_F3                     0x4000003cu
#define PG_F4                     0x4000003du
#define PG_F5                     0x4000003eu
#define PG_F6                     0x4000003fu
#define PG_F7                     0x40000040u
#define PG_F8                     0x40000041u
#define PG_F9                     0x40000042u
#define PG_F10                    0x40000043u
#define PG_F11                    0x40000044u
#define PG_F12                    0x40000045u
#define PG_INSERT                 0x40000049u
#define PG_HOME                   0x4000004au
#define PG_PAGEUP                 0x4000004bu
#define PG_END                    0x4000004du
#define PG_PAGEDOWN               0x4000004eu
#define PG_RIGHT                  0x4000004fu
#define PG_LEFT                   0x40000050u
#define PG_DOWN                   0x40000051u
#define PG_UP                     0x40000052u
#define PG_LCTRL                  0x400000e0u
#define PG_LSHIFT                 0x400000e1u
#define PG_LALT                   0x400000e2u
#define PG_RCTRL                  0x400000e4u
#define PG_RSHIFT                 0x400000e5u
#define PG_RALT                   0x400000e6u