#ifndef BN_BG_PALETTE_PTR_H
#define BN_BG_PALETTE_PTR_H

#include "bn_optional.h"
#include "bn_fixed.h"

namespace bn
{
    class bg_palette_ptr
    {
    public:
        // Stub: Set color of a specific index
        void set_color(int index, int color) {}

        // Stub: Set generic fade color
        void set_fade(int color, fixed intensity) {}

        // Fix: Add set_inverted stub
        void set_inverted(bool inverted) {}
    };
}

#endif