#ifndef BN_DISPLAY_H
#define BN_DISPLAY_H

#include "bn_fixed.h"
#include "bn_core.h" // <--- Added to get GAME_WIDTH/HEIGHT

namespace bn::display
{
    constexpr int width() { return GAME_WIDTH; }
    constexpr int height() { return GAME_HEIGHT; }
}

#endif