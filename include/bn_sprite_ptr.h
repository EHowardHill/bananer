#ifndef BN_SPRITE_PTR_H
#define BN_SPRITE_PTR_H

#include "bn_sprite_item.h"
#include "bn_fixed.h"
#include "bn_sprite_palette_item.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_camera_ptr.h" // Added
#include <memory>

namespace bn
{
    class sprite_impl;

    class sprite_ptr
    {
    public:
        static sprite_ptr create(float x, float y, const sprite_item &item, int graphics_index = 0);

        sprite_ptr(const sprite_ptr &other) = default;
        sprite_ptr(sprite_ptr &&other) noexcept = default;
        ~sprite_ptr() = default;

        sprite_ptr &operator=(const sprite_ptr &other) = default;
        sprite_ptr &operator=(sprite_ptr &&other) noexcept = default;

        void set_x(fixed x);
        void set_y(fixed y);
        void set_position(fixed x, fixed y);

        fixed x() const;
        fixed y() const;

        void set_visible(bool visible);
        bool visible() const;

        void set_scale(double scale);
        void set_scale(fixed scale);
        void set_scale(fixed x, fixed y);

        void set_horizontal_scale(fixed scale);
        void set_vertical_scale(fixed scale);

        fixed horizontal_scale() const;
        fixed vertical_scale() const;

        void set_rotation_angle(int angle);
        void set_rotation_angle(fixed angle);

        fixed rotation_angle() const;

        void set_horizontal_flip(bool flip);
        bool horizontal_flip() const;

        void set_vertical_flip(bool flip);
        bool vertical_flip() const;

        void set_z_order(int z);
        int z_order() const;

        void set_blending_enabled(bool enabled);

        void put_above();
        void put_below();

        void set_palette(const sprite_palette_item &palette_item);
        sprite_palette_ptr palette() const { return sprite_palette_ptr(); }

        void set_tiles(int graphics_index);
        void set_tiles(const sprite_item &item, int graphics_index = 0);

        // Added overload for sprite_tiles_item
        void set_tiles(const sprite_tiles_item &item, int graphics_index = 0);

        // Added set_camera
        void set_camera(const camera_ptr &camera);

    private:
        std::shared_ptr<sprite_impl> _impl;
        sprite_ptr(std::shared_ptr<sprite_impl> impl);
    };
}

#endif