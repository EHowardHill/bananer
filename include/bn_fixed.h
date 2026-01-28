#ifndef BN_FIXED_H
#define BN_FIXED_H

#include <cmath>
#include <compare>
#include <cstdint>
#include <ostream>

namespace bn
{
    template <int Precision>
    class fixed_t
    {
    private:
        float _value;

    public:
        constexpr fixed_t() : _value(0) {}
        constexpr fixed_t(int v) : _value(static_cast<float>(v)) {}
        constexpr fixed_t(float v) : _value(v) {}
        constexpr fixed_t(double v) : _value(static_cast<float>(v)) {}

        // --- ADDED: Ambiguity resolvers for size_t (long/long long) ---
        constexpr fixed_t(long v) : _value(static_cast<float>(v)) {}
        constexpr fixed_t(unsigned long v) : _value(static_cast<float>(v)) {}
        constexpr fixed_t(long long v) : _value(static_cast<float>(v)) {}
        constexpr fixed_t(unsigned long long v) : _value(static_cast<float>(v)) {}

        template <int OtherPrecision>
        constexpr fixed_t(const fixed_t<OtherPrecision> &other) : _value(other.to_float()) {}

        [[nodiscard]] constexpr int integer() const { return static_cast<int>(_value); }
        [[nodiscard]] constexpr float to_float() const { return _value; }
        [[nodiscard]] constexpr double to_double() const { return static_cast<double>(_value); }

        explicit constexpr operator float() const { return _value; }

        constexpr fixed_t &operator+=(float b)
        {
            _value += b;
            return *this;
        }
        constexpr fixed_t &operator-=(float b)
        {
            _value -= b;
            return *this;
        }
        constexpr fixed_t &operator*=(float b)
        {
            _value *= b;
            return *this;
        }
        constexpr fixed_t &operator/=(float b)
        {
            _value /= b;
            return *this;
        }

        template <int Q>
        constexpr fixed_t &operator+=(const fixed_t<Q> &b)
        {
            _value += b.to_float();
            return *this;
        }
        template <int Q>
        constexpr fixed_t &operator-=(const fixed_t<Q> &b)
        {
            _value -= b.to_float();
            return *this;
        }

        constexpr fixed_t operator-() const { return fixed_t(-_value); }

        friend constexpr fixed_t abs(const fixed_t &val)
        {
            return fixed_t(std::abs(val._value));
        }

        // --- ARITHMETIC OPERATORS ---
        friend constexpr fixed_t operator+(const fixed_t &a, int b) { return fixed_t(a._value + b); }
        friend constexpr fixed_t operator+(int a, const fixed_t &b) { return fixed_t(a + b._value); }
        friend constexpr fixed_t operator+(const fixed_t &a, float b) { return fixed_t(a._value + b); }
        friend constexpr fixed_t operator+(float a, const fixed_t &b) { return fixed_t(a + b._value); }
        friend constexpr fixed_t operator+(const fixed_t &a, double b) { return fixed_t(a._value + static_cast<float>(b)); }
        friend constexpr fixed_t operator+(double a, const fixed_t &b) { return fixed_t(static_cast<float>(a) + b._value); }

        // Added long/long long support
        friend constexpr fixed_t operator+(const fixed_t &a, long b) { return fixed_t(a._value + b); }
        friend constexpr fixed_t operator+(long a, const fixed_t &b) { return fixed_t(a + b._value); }
        friend constexpr fixed_t operator+(const fixed_t &a, unsigned long b) { return fixed_t(a._value + b); }
        friend constexpr fixed_t operator+(unsigned long a, const fixed_t &b) { return fixed_t(a + b._value); }
        friend constexpr fixed_t operator+(const fixed_t &a, long long b) { return fixed_t(a._value + b); }
        friend constexpr fixed_t operator+(long long a, const fixed_t &b) { return fixed_t(a + b._value); }

        friend constexpr fixed_t operator-(const fixed_t &a, int b) { return fixed_t(a._value - b); }
        friend constexpr fixed_t operator-(int a, const fixed_t &b) { return fixed_t(a - b._value); }
        friend constexpr fixed_t operator-(const fixed_t &a, float b) { return fixed_t(a._value - b); }
        friend constexpr fixed_t operator-(float a, const fixed_t &b) { return fixed_t(a - b._value); }
        friend constexpr fixed_t operator-(const fixed_t &a, double b) { return fixed_t(a._value - static_cast<float>(b)); }
        friend constexpr fixed_t operator-(double a, const fixed_t &b) { return fixed_t(static_cast<float>(a) - b._value); }

        // Added long/long long support
        friend constexpr fixed_t operator-(const fixed_t &a, long b) { return fixed_t(a._value - b); }
        friend constexpr fixed_t operator-(long a, const fixed_t &b) { return fixed_t(a - b._value); }
        friend constexpr fixed_t operator-(const fixed_t &a, unsigned long b) { return fixed_t(a._value - b); }
        friend constexpr fixed_t operator-(unsigned long a, const fixed_t &b) { return fixed_t(a - b._value); }
        friend constexpr fixed_t operator-(const fixed_t &a, long long b) { return fixed_t(a._value - b); }
        friend constexpr fixed_t operator-(long long a, const fixed_t &b) { return fixed_t(a - b._value); }

        friend constexpr fixed_t operator*(const fixed_t &a, int b) { return fixed_t(a._value * b); }
        friend constexpr fixed_t operator*(int a, const fixed_t &b) { return fixed_t(a * b._value); }
        friend constexpr fixed_t operator*(const fixed_t &a, float b) { return fixed_t(a._value * b); }
        friend constexpr fixed_t operator*(float a, const fixed_t &b) { return fixed_t(a * b._value); }
        friend constexpr fixed_t operator*(const fixed_t &a, double b) { return fixed_t(a._value * static_cast<float>(b)); }
        friend constexpr fixed_t operator*(double a, const fixed_t &b) { return fixed_t(static_cast<float>(a) * b._value); }

        // Added long/long long support
        friend constexpr fixed_t operator*(const fixed_t &a, long b) { return fixed_t(a._value * b); }
        friend constexpr fixed_t operator*(long a, const fixed_t &b) { return fixed_t(a * b._value); }
        friend constexpr fixed_t operator*(const fixed_t &a, unsigned long b) { return fixed_t(a._value * b); }
        friend constexpr fixed_t operator*(unsigned long a, const fixed_t &b) { return fixed_t(a * b._value); }

        friend constexpr fixed_t operator/(const fixed_t &a, int b) { return fixed_t(a._value / b); }
        friend constexpr fixed_t operator/(int a, const fixed_t &b) { return fixed_t(a / b._value); }
        friend constexpr fixed_t operator/(const fixed_t &a, float b) { return fixed_t(a._value / b); }
        friend constexpr fixed_t operator/(float a, const fixed_t &b) { return fixed_t(a / b._value); }
        friend constexpr fixed_t operator/(const fixed_t &a, double b) { return fixed_t(a._value / static_cast<float>(b)); }
        friend constexpr fixed_t operator/(double a, const fixed_t &b) { return fixed_t(static_cast<float>(a) / b._value); }

        // Added long/long long support
        friend constexpr fixed_t operator/(const fixed_t &a, long b) { return fixed_t(a._value / b); }
        friend constexpr fixed_t operator/(long a, const fixed_t &b) { return fixed_t(a / b._value); }
        friend constexpr fixed_t operator/(const fixed_t &a, unsigned long b) { return fixed_t(a._value / b); }
        friend constexpr fixed_t operator/(unsigned long a, const fixed_t &b) { return fixed_t(a / b._value); }

        // --- COMPARISONS ---
        friend constexpr bool operator==(const fixed_t &a, int b) { return a._value == b; }
        friend constexpr bool operator==(int a, const fixed_t &b) { return a == b._value; }
        friend constexpr bool operator!=(const fixed_t &a, int b) { return a._value != b; }
        friend constexpr bool operator!=(int a, const fixed_t &b) { return a != b._value; }
        friend constexpr bool operator<(const fixed_t &a, int b) { return a._value < b; }
        friend constexpr bool operator<(int a, const fixed_t &b) { return a < b._value; }
        friend constexpr bool operator>(const fixed_t &a, int b) { return a._value > b; }
        friend constexpr bool operator>(int a, const fixed_t &b) { return a > b._value; }
        friend constexpr bool operator<=(const fixed_t &a, int b) { return a._value <= b; }
        friend constexpr bool operator<=(int a, const fixed_t &b) { return a <= b._value; }
        friend constexpr bool operator>=(const fixed_t &a, int b) { return a._value >= b; }
        friend constexpr bool operator>=(int a, const fixed_t &b) { return a >= b._value; }

        friend constexpr bool operator==(const fixed_t &a, float b) { return a._value == b; }
        friend constexpr bool operator==(float a, const fixed_t &b) { return a == b._value; }
        friend constexpr bool operator!=(const fixed_t &a, float b) { return a._value != b; }
        friend constexpr bool operator!=(float a, const fixed_t &b) { return a != b._value; }
        friend constexpr bool operator<(const fixed_t &a, float b) { return a._value < b; }
        friend constexpr bool operator<(float a, const fixed_t &b) { return a < b._value; }
        friend constexpr bool operator>(const fixed_t &a, float b) { return a._value > b; }
        friend constexpr bool operator>(float a, const fixed_t &b) { return a > b._value; }
        friend constexpr bool operator<=(const fixed_t &a, float b) { return a._value <= b; }
        friend constexpr bool operator<=(float a, const fixed_t &b) { return a <= b._value; }
        friend constexpr bool operator>=(const fixed_t &a, float b) { return a._value >= b; }
        friend constexpr bool operator>=(float a, const fixed_t &b) { return a >= b._value; }

        friend constexpr bool operator==(const fixed_t &a, double b) { return a._value == static_cast<float>(b); }
        friend constexpr bool operator==(double a, const fixed_t &b) { return static_cast<float>(a) == b._value; }
        friend constexpr bool operator!=(const fixed_t &a, double b) { return a._value != static_cast<float>(b); }
        friend constexpr bool operator!=(double a, const fixed_t &b) { return static_cast<float>(a) != b._value; }
        friend constexpr bool operator<(const fixed_t &a, double b) { return a._value < static_cast<float>(b); }
        friend constexpr bool operator<(double a, const fixed_t &b) { return static_cast<float>(a) < b._value; }
        friend constexpr bool operator>(const fixed_t &a, double b) { return a._value > static_cast<float>(b); }
        friend constexpr bool operator>(double a, const fixed_t &b) { return static_cast<float>(a) > b._value; }
        friend constexpr bool operator<=(const fixed_t &a, double b) { return a._value <= static_cast<float>(b); }
        friend constexpr bool operator<=(double a, const fixed_t &b) { return static_cast<float>(a) <= b._value; }
        friend constexpr bool operator>=(const fixed_t &a, double b) { return a._value >= static_cast<float>(b); }
        friend constexpr bool operator>=(double a, const fixed_t &b) { return static_cast<float>(a) >= b._value; }

        friend constexpr fixed_t operator%(const fixed_t &a, int b) { return fixed_t(a.integer() % b); }

        friend std::ostream &operator<<(std::ostream &os, const fixed_t &f)
        {
            os << f.to_float();
            return os;
        }
    };

    template <int P, int Q>
    constexpr fixed_t<P> operator+(const fixed_t<P> &a, const fixed_t<Q> &b) { return fixed_t<P>(a.to_float() + b.to_float()); }

    template <int P, int Q>
    constexpr fixed_t<P> operator-(const fixed_t<P> &a, const fixed_t<Q> &b) { return fixed_t<P>(a.to_float() - b.to_float()); }

    template <int P, int Q>
    constexpr fixed_t<P> operator*(const fixed_t<P> &a, const fixed_t<Q> &b) { return fixed_t<P>(a.to_float() * b.to_float()); }

    template <int P, int Q>
    constexpr fixed_t<P> operator/(const fixed_t<P> &a, const fixed_t<Q> &b) { return fixed_t<P>(a.to_float() / b.to_float()); }

    template <int P, int Q>
    constexpr bool operator==(const fixed_t<P> &a, const fixed_t<Q> &b) { return a.to_float() == b.to_float(); }

    template <int P, int Q>
    constexpr bool operator!=(const fixed_t<P> &a, const fixed_t<Q> &b) { return a.to_float() != b.to_float(); }

    template <int P, int Q>
    constexpr bool operator<(const fixed_t<P> &a, const fixed_t<Q> &b) { return a.to_float() < b.to_float(); }

    template <int P, int Q>
    constexpr bool operator>(const fixed_t<P> &a, const fixed_t<Q> &b) { return a.to_float() > b.to_float(); }

    template <int P, int Q>
    constexpr bool operator<=(const fixed_t<P> &a, const fixed_t<Q> &b) { return a.to_float() <= b.to_float(); }

    template <int P, int Q>
    constexpr bool operator>=(const fixed_t<P> &a, const fixed_t<Q> &b) { return a.to_float() >= b.to_float(); }

    using fixed = fixed_t<12>;
}

#endif