#ifndef BN_CORE_H
#define BN_CORE_H

#include "bn_fixed.h"
#include "bn_string_view.h"
#include "bn_vector.h"
#include "bn_span.h"
#include "bn_optional.h"
#include "bn_rect_window.h"
#include "bn_algorithm.h" // Added to ensure min/max are available

#ifndef GAME_WIDTH
#define GAME_WIDTH 240
#endif

#ifndef GAME_HEIGHT
#define GAME_HEIGHT 160
#endif

namespace bn::core
{
    void init();
    void update();
    void exit();

    // --- ADDED: reset stub ---
    inline void reset() {}
}

#endif