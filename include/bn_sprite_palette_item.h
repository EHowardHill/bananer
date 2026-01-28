#ifndef BN_SPRITE_PALETTE_ITEM_H
#define BN_SPRITE_PALETTE_ITEM_H

#include "bn_sprite_palette_ptr.h"

namespace bn
{
    class sprite_palette_item
    {
    public:
        // Stub constructor
        constexpr sprite_palette_item() {}

        // Stub: Create a palette pointer (if code calls create_palette)
        sprite_palette_ptr create_palette() const
        {
            return sprite_palette_ptr();
        }
    };
}

#endif