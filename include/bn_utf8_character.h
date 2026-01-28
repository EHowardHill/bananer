#ifndef BN_UTF8_CHARACTER_H
#define BN_UTF8_CHARACTER_H

#include "bn_string_view.h"

namespace bn
{
    // A utf8_character is essentially a string_view (can hold multibyte chars)
    using utf8_character = string_view;
}

#endif