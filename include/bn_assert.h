#ifndef BN_ASSERT_H
#define BN_ASSERT_H

#include <cassert>
#include <iostream>
#include <cstdlib>

// Define BN_ASSERT to wrap standard C++ assert with a message
#define BN_ASSERT(condition, message)                              \
    do                                                             \
    {                                                              \
        if (!(condition))                                          \
        {                                                          \
            std::cerr << "ASSERTION FAILED: " << (message) << "\n" \
                      << "File: " << __FILE__ << "\n"              \
                      << "Line: " << __LINE__ << std::endl;        \
            std::abort();                                          \
        }                                                          \
    } while (0)

// Define BN_ERROR for unconditional failure
#define BN_ERROR(message)                                    \
    do                                                       \
    {                                                        \
        std::cerr << "CRITICAL ERROR: " << (message) << "\n" \
                  << "File: " << __FILE__ << "\n"            \
                  << "Line: " << __LINE__ << std::endl;      \
        std::abort();                                        \
    } while (0)

#endif