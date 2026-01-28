#ifndef BN_SOUND_ACTIONS_H
#define BN_SOUND_ACTIONS_H

#include "bn_fixed.h"
#include "bn_sound_items.h"

namespace bn
{
    // Stubs for common sound action patterns.
    // Since we don't see the usage in main.cpp yet, we define the basics.

    class sound_master_volume_action
    {
    public:
        sound_master_volume_action(fixed duration, fixed final_volume) {}

        void update() {}
        bool done() const { return true; }
    };

    class sound_master_volume_to_action : public sound_master_volume_action
    {
    public:
        sound_master_volume_to_action(int duration_updates, fixed final_volume)
            : sound_master_volume_action(duration_updates, final_volume) {}
    };

    // If your code uses handle-based actions (e.g. changing volume of a specific sound effect),
    // they would go here. For now, this stub allows compilation to proceed to the next error.
}

#endif