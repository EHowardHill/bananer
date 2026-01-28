#ifndef BN_SPRITE_TEXT_GENERATOR_H
#define BN_SPRITE_TEXT_GENERATOR_H

#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_string_view.h"
#include "bn_sprite_font.h"

namespace bn
{
    class sprite_text_generator
    {
    private:
        const sprite_font *_font;

    public:
        explicit sprite_text_generator(const sprite_font &font) : _font(&font) {}

        template <typename Container>
        void generate(fixed x, fixed y, const string_view &text, Container &sprites) const
        {
            generate_impl(x.integer(), y.integer(), text, sprites);
        }

        template <typename Container>
        void generate(int x, int y, const string_view &text, Container &sprites) const
        {
            generate_impl(x, y, text, sprites);
        }

    private:
        template <typename Container>
        void generate_impl(int start_x, int start_y, const string_view &text, Container &sprites) const
        {
            if (!_font)
                return;

            int cursor_x = start_x;
            int char_width = 8;

            for (char c : text)
            {
                int tile_index = c - _font->minimum_ascii_character();

                // FIX: If index is negative (e.g. Space), simply skip rendering a sprite.
                // This preserves the gap (cursor_x still advances) but draws nothing.
                if (tile_index >= 0)
                {
                    auto ptr = sprite_ptr::create(cursor_x, start_y, _font->item(), tile_index);
                    sprites.push_back(std::move(ptr));
                }

                cursor_x += char_width;
            }
        }
    };
}

#endif