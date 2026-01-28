#ifndef BN_UTF8_CHARACTERS_MAP_H
#define BN_UTF8_CHARACTERS_MAP_H

#include "bn_span.h"
#include "bn_string_view.h"
#include "bn_utf8_character.h"

namespace bn
{
    // Base implementation (Non-template logic)
    class utf8_characters_map_base
    {
    public:
        constexpr explicit utf8_characters_map_base(const span<const string_view> &references) : _references(references)
        {
        }

        // FIX: Renamed from references() to reference() to match user code
        [[nodiscard]] constexpr const span<const string_view> &reference() const
        {
            return _references;
        }

        [[nodiscard]] int index(const string_view &utf8_character) const
        {
            int count = _references.size();
            for (int i = 0; i < count; ++i)
            {
                if (_references[i] == utf8_character)
                {
                    return i;
                }
            }
            return -1;
        }

    private:
        span<const string_view> _references;
    };

    // Template wrapper
    template <const auto &Reference>
    class utf8_characters_map : public utf8_characters_map_base
    {
    public:
        constexpr utf8_characters_map() : utf8_characters_map_base(Reference)
        {
        }
    };
}

#endif