#ifndef BN_ARRAY_H
#define BN_ARRAY_H

#include <array>

namespace bn
{
    template <typename Type, int Size>
    using array = std::array<Type, Size>;
}

#endif