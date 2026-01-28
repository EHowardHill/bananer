#ifndef BN_KEYPAD_H
#define BN_KEYPAD_H

#include "raylib.h"

namespace bn::keypad
{
    inline bool up_held() { return IsKeyDown(KEY_UP); }
    inline bool down_held() { return IsKeyDown(KEY_DOWN); }
    inline bool left_held() { return IsKeyDown(KEY_LEFT); }
    inline bool right_held() { return IsKeyDown(KEY_RIGHT); }

    inline bool up_pressed() { return IsKeyPressed(KEY_UP); }
    inline bool down_pressed() { return IsKeyPressed(KEY_DOWN); }
    inline bool left_pressed() { return IsKeyPressed(KEY_LEFT); }
    inline bool right_pressed() { return IsKeyPressed(KEY_RIGHT); }

    inline bool start_held() { return IsKeyDown(KEY_ENTER); }
    inline bool start_pressed() { return IsKeyPressed(KEY_ENTER); }

    inline bool l_held() { return IsKeyDown(KEY_A); }
    inline bool l_pressed() { return IsKeyPressed(KEY_A); }
    inline bool r_held() { return IsKeyDown(KEY_S); }
    inline bool r_pressed() { return IsKeyDown(KEY_S); }

    // Map A to 'Z' and B to 'X' (standard emulator mapping)
    inline bool a_pressed() { return IsKeyPressed(KEY_Z); }
    inline bool a_held() { return IsKeyDown(KEY_Z); }
    inline bool a_released() { return IsKeyReleased(KEY_Z); }
    inline bool b_pressed() { return IsKeyPressed(KEY_X); }
    inline bool b_held() { return IsKeyDown(KEY_X); }
    inline bool b_released() { return IsKeyReleased(KEY_X); }
}

#endif