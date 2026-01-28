#ifndef BN_MUSIC_ACTIONS_H
#define BN_MUSIC_ACTIONS_H

#include "bn_music.h"
#include "bn_fixed.h"

namespace bn
{
    class music_volume_manager
    {
    public:
        // Changed from set_volume to set to match main.cpp usage
        static void set(fixed volume) { music::set_volume(volume); }
    };

    class music_stop_action
    {
    public:
        music_stop_action() {}
        void update() { music::stop(); }
        bool done() const { return !music::playing(); }
    };
}

#endif