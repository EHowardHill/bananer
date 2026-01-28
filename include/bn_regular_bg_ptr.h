#ifndef BN_REGULAR_BG_PTR_H
#define BN_REGULAR_BG_PTR_H

#include "bn_regular_bg_item.h"
#include "bn_fixed.h"
#include "bn_optional.h"
#include "bn_bg_palette_ptr.h"
#include "bn_camera_ptr.h" // Added
#include <memory>

namespace bn
{
    class regular_bg_impl;

    class regular_bg_ptr
    {
    public:
        static regular_bg_ptr create(fixed x, fixed y, const regular_bg_item &item);

        regular_bg_ptr(const regular_bg_ptr &other) = default;
        regular_bg_ptr(regular_bg_ptr &&other) noexcept = default;
        ~regular_bg_ptr() = default;

        regular_bg_ptr &operator=(const regular_bg_ptr &other) = default;
        regular_bg_ptr &operator=(regular_bg_ptr &&other) noexcept = default;

        void set_x(fixed x);
        void set_y(fixed y);
        void set_position(fixed x, fixed y);

        fixed x() const;
        fixed y() const;

        void set_visible(bool visible) {}

        bg_palette_ptr palette() const { return bg_palette_ptr(); }

        void set_blending_enabled(bool enabled);
        bool blending_enabled() const;

        // Added to fix error
        void set_camera(const camera_ptr &camera);

    private:
        std::shared_ptr<regular_bg_impl> _impl;
        regular_bg_ptr(std::shared_ptr<regular_bg_impl> impl);
    };
}

#endif