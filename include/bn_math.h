#ifndef BN_MATH_H
#define BN_MATH_H

#include <cmath>
#include <algorithm>
#include <cstdlib>
#include "bn_fixed.h"

namespace bn
{
    constexpr double DEG_TO_RAD = 3.14159265358979323846 / 180.0;

    // Import clamp, min, max from std to avoid conflicts
    // (bn_algorithm.h also imports these, but we need them here too for files that only include bn_math.h)
    using std::clamp;
    using std::max;
    using std::min;

    template <typename T>
    [[nodiscard]] constexpr T abs(T value)
    {
        return std::abs(value);
    }

    template <int P>
    [[nodiscard]] inline fixed_t<P> sin(const fixed_t<P> &value) { return fixed_t<P>(std::sin(value.to_float())); }

    template <int P>
    [[nodiscard]] inline fixed_t<P> cos(const fixed_t<P> &value) { return fixed_t<P>(std::cos(value.to_float())); }

    template <int P>
    [[nodiscard]] inline fixed_t<P> sqrt(const fixed_t<P> &value) { return fixed_t<P>(std::sqrt(value.to_float())); }

    [[nodiscard]] inline fixed sin(int value) { return fixed(std::sin(value)); }
    [[nodiscard]] inline fixed cos(int value) { return fixed(std::cos(value)); }
    [[nodiscard]] inline fixed sin(double value) { return fixed(std::sin(value)); }
    [[nodiscard]] inline fixed cos(double value) { return fixed(std::cos(value)); }

    [[nodiscard]] inline float degrees_sin(int degrees)
    {
        return std::sin(degrees * DEG_TO_RAD);
    }

    [[nodiscard]] inline float degrees_cos(int degrees)
    {
        return std::cos(degrees * DEG_TO_RAD);
    }

    template <int P>
    [[nodiscard]] inline fixed_t<P> degrees_sin(const fixed_t<P> &degrees)
    {
        return fixed_t<P>(std::sin(degrees.to_float() * DEG_TO_RAD));
    }

    template <int P>
    [[nodiscard]] inline fixed_t<P> degrees_cos(const fixed_t<P> &degrees)
    {
        return fixed_t<P>(std::cos(degrees.to_float() * DEG_TO_RAD));
    }
}

#endif