#ifndef BN_MUSIC_H
#define BN_MUSIC_H

#include "bn_fixed.h"
#include "bn_music_items.h"
#include "bn_optional.h"

namespace bn::music
{
    void play(const music_item &item, fixed volume = 1);
    void play(const music_item &item, fixed volume, bool loop);

    void stop();
    void pause();
    void resume();

    bool playing();

    // --- ADDED: playing_item ---
    optional<music_item> playing_item();

    void set_volume(fixed volume);
    fixed volume();

    void _update_stream();
}

#endif