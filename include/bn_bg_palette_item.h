#ifndef BN_BG_PALETTE_ITEM_H
#define BN_BG_PALETTE_ITEM_H

#include "bn_bg_palette_ptr.h"

namespace bn
{
    class bg_palette_item
    {
    public:
        constexpr bg_palette_item() {}

        // Stub: Create a palette pointer
        bg_palette_ptr create_palette() const
        {
            return bg_palette_ptr();
        }
    };
}

#endif