#ifndef BN_RANDOM_H
#define BN_RANDOM_H

#include <cstdlib>
#include "bn_fixed.h"

namespace bn
{
    class random
    {
    public:
        constexpr random() = default;

        void update() {}

        [[nodiscard]] int get_int() const
        {
            return std::rand();
        }

        [[nodiscard]] int get_int(int limit) const
        {
            if (limit <= 0)
                return 0;
            return std::rand() % limit;
        }

        [[nodiscard]] int get_int(int min, int max) const
        {
            if (min >= max)
                return min;
            return min + (std::rand() % (max - min));
        }

        // --- Added Fixed Point Generators ---

        // Returns a random fixed point between 0 and range (exclusive)
        [[nodiscard]] fixed get_fixed(fixed range) const
        {
            if (range <= 0)
                return 0;
            float r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
            return fixed(r * range.to_float());
        }

        // Returns a random fixed point between min and max (exclusive)
        [[nodiscard]] fixed get_fixed(fixed min, fixed max) const
        {
            if (min >= max)
                return min;
            float r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
            return min + fixed(r * (max - min).to_float());
        }
    };
}

#endif