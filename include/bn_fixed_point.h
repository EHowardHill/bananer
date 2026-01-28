#ifndef BN_FIXED_POINT_H
#define BN_FIXED_POINT_H

#include "bn_fixed.h"

namespace bn
{
    class fixed_point
    {
    public:
        constexpr fixed_point() : _x(0), _y(0) {}

        constexpr fixed_point(fixed x, fixed y) : _x(x), _y(y) {}

        [[nodiscard]] constexpr fixed x() const { return _x; }
        [[nodiscard]] constexpr fixed y() const { return _y; }

        constexpr void set_x(fixed x) { _x = x; }
        constexpr void set_y(fixed y) { _y = y; }

        constexpr fixed_point &operator+=(const fixed_point &other)
        {
            _x += other._x;
            _y += other._y;
            return *this;
        }

        constexpr fixed_point &operator-=(const fixed_point &other)
        {
            _x -= other._x;
            _y -= other._y;
            return *this;
        }

        friend constexpr fixed_point operator+(const fixed_point &a, const fixed_point &b)
        {
            return fixed_point(a._x + b._x, a._y + b._y);
        }

        friend constexpr fixed_point operator-(const fixed_point &a, const fixed_point &b)
        {
            return fixed_point(a._x - b._x, a._y - b._y);
        }

    private:
        fixed _x;
        fixed _y;
    };
}

#endif