#ifndef BN_BG_PALETTES_H
#define BN_BG_PALETTES_H

#include "bn_fixed.h"
#include "raylib.h"

namespace bn::bg_palettes
{
    // Sets the transparent color for backgrounds (usually index 0).
    // In our implementation, this is handled during loading, but we provide the stub.
    inline void set_transparent_color(int color_index) {}

    inline void set_brightness(fixed brightness)
    {
        // Stub: Would require shader or texture recoloring
    }
}

#endif