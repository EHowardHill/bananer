#ifndef BN_MUSIC_ITEM_H
#define BN_MUSIC_ITEM_H

#include "bn_fixed.h"
#include <cstring>

namespace bn
{
    struct music_item
    {
        const char *_path;

        constexpr music_item(const char *path) : _path(path) {}

        void play(fixed volume = 1, bool loop = true) const;

        // --- ADDED: Comparison Operators ---
        bool operator==(const music_item &other) const
        {
            // Simple pointer check first, then string compare
            if (_path == other._path)
                return true;
            return std::strcmp(_path, other._path) == 0;
        }

        bool operator!=(const music_item &other) const
        {
            return !(*this == other);
        }
    };
}

#endif