#ifndef BN_CAMERA_PTR_H
#define BN_CAMERA_PTR_H

#include "bn_fixed.h"
#include <memory>

namespace bn
{
    class camera_ptr
    {
    public:
        // Factory method
        static camera_ptr create(fixed x, fixed y);

        camera_ptr(const camera_ptr &other) = default;
        camera_ptr &operator=(const camera_ptr &other) = default;
        ~camera_ptr() = default;

        fixed x() const;
        fixed y() const;

        void set_x(fixed x);
        void set_y(fixed y);
        void set_position(fixed x, fixed y);

        // Internal implementation struct
        struct impl;

    private:
        std::shared_ptr<impl> _impl;
        explicit camera_ptr(std::shared_ptr<impl> impl);
    };
}

#endif