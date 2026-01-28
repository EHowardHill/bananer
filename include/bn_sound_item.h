#ifndef BN_SOUND_ITEM_H
#define BN_SOUND_ITEM_H

#include "bn_fixed.h"

namespace bn
{
    struct sound_item
    {
        const char *_path;

        constexpr sound_item(const char *path) : _path(path) {}

        // Implementation is in src/bn_sprites.cpp
        void play(fixed volume = 1) const;
    };
}

#endif