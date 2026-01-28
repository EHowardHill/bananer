#ifndef BN_RECT_WINDOW_H
#define BN_RECT_WINDOW_H

#include "bn_regular_bg_ptr.h"
#include "bn_fixed.h"

namespace bn
{
    class rect_window
    {
    public:
        static rect_window external() { return rect_window(); }
        static rect_window internal() { return rect_window(); }

        constexpr rect_window() = default;

        void set_show_bg(const regular_bg_ptr &bg, bool show) {}
        void set_boundaries(fixed top, fixed left, fixed bottom, fixed right) {}
        void set_visible(bool visible) {}
        void set_camera(const regular_bg_ptr &camera) {}

        // Fix: Added missing method
        void set_show_sprites(bool show) {}
    };
}

#endif