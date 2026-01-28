#ifndef BN_CAMERA_ACTIONS_H
#define BN_CAMERA_ACTIONS_H

#include "bn_camera_ptr.h"
#include "bn_fixed.h"

namespace bn
{
    // Action to move a camera to a specific position over a set number of frames
    class camera_move_to_action
    {
    public:
        camera_move_to_action(const camera_ptr &camera, int duration_updates, fixed final_x, fixed final_y)
            : _camera(camera),
              _duration(duration_updates),
              _final_x(final_x),
              _final_y(final_y)
        {
            if (_duration > 0)
            {
                _delta_x = (final_x - camera.x()) / duration_updates;
                _delta_y = (final_y - camera.y()) / duration_updates;
            }
            else
            {
                _delta_x = 0;
                _delta_y = 0;
            }
        }

        void update()
        {
            if (_duration > 0)
            {
                // Simple linear interpolation
                _camera.set_x(_camera.x() + _delta_x);
                _camera.set_y(_camera.y() + _delta_y);
                _duration--;

                // Snap to final position on last frame to avoid precision drift
                if (_duration == 0)
                {
                    _camera.set_position(_final_x, _final_y);
                }
            }
        }

        [[nodiscard]] bool done() const
        {
            return _duration <= 0;
        }

    private:
        camera_ptr _camera;
        int _duration;
        fixed _final_x;
        fixed _final_y;
        fixed _delta_x;
        fixed _delta_y;
    };

    // Action to move a camera continuously by a specific delta every update
    class camera_move_loop_action
    {
    public:
        camera_move_loop_action(const camera_ptr &camera, fixed delta_x, fixed delta_y)
            : _camera(camera), _delta_x(delta_x), _delta_y(delta_y)
        {
        }

        void update()
        {
            _camera.set_x(_camera.x() + _delta_x);
            _camera.set_y(_camera.y() + _delta_y);
        }

        [[nodiscard]] bool done() const
        {
            return false;
        }

    private:
        camera_ptr _camera;
        fixed _delta_x;
        fixed _delta_y;
    };
}

#endif