#ifndef BN_LOG_H
#define BN_LOG_H

#include <iostream>

namespace bn::detail
{
    inline void log_printer()
    {
        std::cout << std::endl;
    }

    template <typename First, typename... Rest>
    void log_printer(const First &first, const Rest &...rest)
    {
        std::cout << first;
        log_printer(rest...);
    }
}

// Wrapper macro
#define BN_LOG(...) bn::detail::log_printer(__VA_ARGS__)

#endif