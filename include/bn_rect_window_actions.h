#ifndef BN_RECT_WINDOW_ACTIONS_H
#define BN_RECT_WINDOW_ACTIONS_H

#include "bn_fixed.h"

namespace bn
{
    // Stub: Butano Windows are clipping regions.
    // Implementing move actions for them in Raylib is complex without a global state manager for windows.
    // We provide a no-op stub to allow compilation.

    class rect_window_move_top_action
    {
    public:
        rect_window_move_top_action(fixed final_top, int duration) {}
        void update() {}
        bool done() const { return true; }
    };
}

#endif