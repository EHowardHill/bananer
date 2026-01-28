#ifndef BN_SPRITE_ANIMATE_ACTION_H
#define BN_SPRITE_ANIMATE_ACTION_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_sprite_tiles_item.h"
#include "bn_assert.h"
#include <array>

namespace bn
{
    template <int Size>
    class sprite_animate_action
    {
    private:
        sprite_ptr _sprite;
        int _wait_updates;
        int _current_wait;
        int _current_step;
        std::array<int, Size> _indices;
        bool _forever;

    public:
        // Template the tiles_item argument to accept sprite_item OR sprite_tiles_item
        template <typename TilesItem, typename... Args>
        sprite_animate_action(const sprite_ptr &sprite, int wait_updates, const TilesItem &tiles, Args... args)
            : _sprite(sprite),
              _wait_updates(wait_updates),
              _current_wait(wait_updates),
              _current_step(0),
              _indices{static_cast<int>(args)...},
              _forever(true)
        {
            // Set initial frame
            if (Size > 0)
            {
                _sprite.set_tiles(_indices[0]);
            }
        }

        void update()
        {
            if (_current_wait > 0)
            {
                _current_wait--;
            }
            else
            {
                _current_wait = _wait_updates;
                _current_step++;

                if (_current_step >= Size)
                {
                    if (_forever)
                    {
                        _current_step = 0;
                    }
                    else
                    {
                        _current_step = Size - 1;
                    }
                }

                _sprite.set_tiles(_indices[_current_step]);
            }
        }

        bool done() const
        {
            return !_forever && _current_step >= Size - 1;
        }
    };

    // Helper: Updated to use template for TilesItem
    template <typename TilesItem, typename... Args>
    sprite_animate_action<sizeof...(Args)> create_sprite_animate_action_forever(
        const sprite_ptr &sprite, int wait_updates, const TilesItem &tiles_item, Args... args)
    {
        return sprite_animate_action<sizeof...(Args)>(sprite, wait_updates, tiles_item, args...);
    }
}

#endif