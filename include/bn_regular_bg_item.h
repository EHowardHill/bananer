#ifndef BN_REGULAR_BG_ITEM_H
#define BN_REGULAR_BG_ITEM_H

#include "bn_fixed.h"
#include "bn_bg_palette_item.h"

namespace bn
{
    // Forward declaration to break circular dependency
    class regular_bg_ptr;

    class regular_bg_item
    {
    private:
        const char *_path;
        int _width;
        int _height;

    public:
        constexpr regular_bg_item(const char *path, int width, int height)
            : _path(path), _width(width), _height(height)
        {
        }

        const char *path() const { return _path; }
        int width() const { return _width; }
        int height() const { return _height; }

        bg_palette_item palette_item() const { return bg_palette_item(); }

        // The compiler now knows regular_bg_ptr exists as a class,
        // even if it doesn't know its size/members yet.
        regular_bg_ptr create_bg(fixed x, fixed y) const;
    };
}

#endif