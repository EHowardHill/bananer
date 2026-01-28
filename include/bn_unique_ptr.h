#ifndef BN_UNIQUE_PTR_H
#define BN_UNIQUE_PTR_H

#include <memory>

namespace bn
{
    template <typename Type>
    using unique_ptr = std::unique_ptr<Type>;

    using std::make_unique;
}

#endif