#ifndef BN_SPRITE_FONT_H
#define BN_SPRITE_FONT_H

#include "bn_sprite_item.h"
#include "bn_span.h"
#include "bn_string_view.h"

namespace bn
{
    class sprite_font
    {
    private:
        sprite_item _item;

    public:
        constexpr sprite_font(const sprite_item &item) : _item(item) {}

        template <int Size>
        constexpr sprite_font(const sprite_item &item, const span<const string_view> &characters, const int8_t (&widths)[Size])
            : _item(item)
        {
        }

        const sprite_item &item() const { return _item; }

        // FIX: Changed from 32 to 33.
        // Most Butano font bitmaps start at '!' (33).
        // Space (32) is usually empty/handled by cursor movement.
        int minimum_ascii_character() const { return 33; }
    };
}

#endif