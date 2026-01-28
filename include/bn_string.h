#ifndef BN_STRING_H
#define BN_STRING_H

#include "bn_string_view.h"
#include "bn_assert.h"
#include <string>
#include <algorithm>
#include <cstdio>
#include <type_traits>

namespace bn
{
    template <int MaxSize>
    class string : public std::string
    {
    public:
        using std::string::string;

        string() : std::string() {}
        string(const char *char_array) : std::string(char_array) {}
        string(const std::string &other) : std::string(other) {}
        string(const string_view &view) : std::string(view.data(), view.size()) {}

        [[nodiscard]] int size() const
        {
            return static_cast<int>(std::string::size());
        }

        template <int OtherSize>
        string(const string<OtherSize> &other) : std::string(other) {}

        template <int OtherSize>
        string &operator=(const string<OtherSize> &other)
        {
            this->assign(other);
            return *this;
        }

        string &operator=(const char *char_array)
        {
            this->assign(char_array);
            return *this;
        }

        string &operator=(const string_view &view)
        {
            this->assign(view.data(), view.size());
            return *this;
        }

        // --- NEW: Assignment from std::string (fixes concatenation ambiguity) ---
        string &operator=(const std::string &other)
        {
            this->assign(other);
            return *this;
        }
    };

    template <int MaxSize>
    [[nodiscard]] string<MaxSize> to_string(int value)
    {
        return string<MaxSize>(std::to_string(value).c_str());
    }

    template <int MaxSize>
    [[nodiscard]] string<MaxSize> to_string(long value)
    {
        return string<MaxSize>(std::to_string(value).c_str());
    }

    template <int MaxSize>
    [[nodiscard]] string<MaxSize> to_string(unsigned value)
    {
        return string<MaxSize>(std::to_string(value).c_str());
    }

    template <int MaxSize>
    [[nodiscard]] string<MaxSize> to_string(unsigned long value)
    {
        return string<MaxSize>(std::to_string(value).c_str());
    }

    template <int MaxSize>
    [[nodiscard]] string<MaxSize> to_string(double value)
    {
        return string<MaxSize>(std::to_string(value).c_str());
    }
}

namespace std
{
    template <int MaxSize>
    struct hash<bn::string<MaxSize>>
    {
        std::size_t operator()(const bn::string<MaxSize> &s) const noexcept
        {
            return std::hash<std::string>{}(s);
        }
    };
}

#endif