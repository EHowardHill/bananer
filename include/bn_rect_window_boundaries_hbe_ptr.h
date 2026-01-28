#ifndef BN_RECT_WINDOW_BOUNDARIES_HBE_PTR_H
#define BN_RECT_WINDOW_BOUNDARIES_HBE_PTR_H

#include "bn_vector.h"
#include "bn_fixed.h"

namespace bn
{
    // HBE (Horizontal Blank Effect) changes parameters per scanline.
    // This is extremely difficult to emulate in high-level Raylib.
    // We provide a stub that accepts the data but does nothing.

    class rect_window_boundaries_hbe_ptr
    {
    public:
        static rect_window_boundaries_hbe_ptr create(
            fixed horizontal_boundaries,      // Placeholder arg
            const vector<fixed, 160> &deltas) // The per-scanline data
        {
            return rect_window_boundaries_hbe_ptr();
        }

        void set_visible(bool visible) {}
    };
}

#endif