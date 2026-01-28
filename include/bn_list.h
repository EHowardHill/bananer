#ifndef BN_LIST_H
#define BN_LIST_H

#include <list>

namespace bn
{
    // Alias std::list, ignoring the MaxSize integer template parameter
    template <typename T, int MaxSize>
    using list = std::list<T>;
}

#endif