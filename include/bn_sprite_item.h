#ifndef BN_SPRITE_ITEM_H
#define BN_SPRITE_ITEM_H

#include "raylib.h"
#include "bn_fixed.h"
#include "bn_sprite_palette_item.h"
#include "bn_sprite_tiles_item.h"

namespace bn
{
    class sprite_ptr;

    // --- ADDED: sprite_shape_size ---
    class sprite_shape_size
    {
    private:
        int _width;
        int _height;

    public:
        constexpr sprite_shape_size(int w, int h) : _width(w), _height(h) {}
        constexpr int width() const { return _width; }
        constexpr int height() const { return _height; }
    };

    class sprite_item
    {
    private:
        const char *_path;
        int _width;
        int _height;
        int _tiles_count;

    public:
        constexpr sprite_item(const char *path, int width, int height, int tiles_count)
            : _path(path), _width(width), _height(height), _tiles_count(tiles_count)
        {
        }

        const char *path() const { return _path; }
        int width() const { return _width; }
        int height() const { return _height; }
        int tiles_count() const { return _tiles_count; }

        sprite_palette_item palette_item() const { return sprite_palette_item(); }
        sprite_tiles_item tiles_item() const { return sprite_tiles_item(*this); }

        // --- ADDED: shape_size accessor ---
        constexpr sprite_shape_size shape_size() const
        {
            return sprite_shape_size(_width, _height);
        }

        sprite_ptr create_sprite(float x, float y) const;
        sprite_ptr create_sprite(float x, float y, int graphics_index) const;
        sprite_ptr create_sprite(fixed x, fixed y) const;
        sprite_ptr create_sprite(fixed x, fixed y, int graphics_index) const;
    };
}

#endif