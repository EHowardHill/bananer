#ifndef BN_VECTOR_H
#define BN_VECTOR_H

#include <vector>

namespace bn
{
    // Alias std::vector, ignoring the MaxSize template parameter
    template <typename T, int MaxSize>
    using vector = std::vector<T>;
}

#endif