#ifndef BN_SPAN_H
#define BN_SPAN_H

#include <cstddef>
#include <iterator>
#include <cassert>

namespace bn
{
    template <typename T>
    class span
    {
    public:
        using element_type = T;
        using value_type = std::remove_cv_t<T>;
        using size_type = int;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iterator = const T *;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        // Constructors
        constexpr span() = default;

        constexpr span(pointer data, size_type size) : _data(data), _size(size)
        {
            assert(size >= 0);
        }

        // Allow constructing from C-arrays
        template <size_t N>
        constexpr span(T (&array)[N]) : _data(array), _size(static_cast<size_type>(N))
        {
        }

        // Observers
        [[nodiscard]] constexpr pointer data() const
        {
            return _data;
        }

        [[nodiscard]] constexpr size_type size() const
        {
            return _size;
        }

        [[nodiscard]] constexpr size_type size_bytes() const
        {
            return _size * sizeof(T);
        }

        [[nodiscard]] constexpr bool empty() const
        {
            return _size == 0;
        }

        // Element access
        [[nodiscard]] constexpr reference operator[](size_type index) const
        {
            assert(index >= 0 && index < _size);
            return _data[index];
        }

        [[nodiscard]] constexpr reference front() const
        {
            assert(_size > 0);
            return _data[0];
        }

        [[nodiscard]] constexpr reference back() const
        {
            assert(_size > 0);
            return _data[_size - 1];
        }

        // Iterators
        [[nodiscard]] constexpr iterator begin() const
        {
            return _data;
        }

        [[nodiscard]] constexpr iterator end() const
        {
            return _data + _size;
        }

        [[nodiscard]] constexpr const_iterator cbegin() const
        {
            return _data;
        }

        [[nodiscard]] constexpr const_iterator cend() const
        {
            return _data + _size;
        }

        [[nodiscard]] constexpr reverse_iterator rbegin() const
        {
            return reverse_iterator(end());
        }

        [[nodiscard]] constexpr reverse_iterator rend() const
        {
            return reverse_iterator(begin());
        }

        [[nodiscard]] constexpr const_reverse_iterator crbegin() const
        {
            return const_reverse_iterator(cend());
        }

        [[nodiscard]] constexpr const_reverse_iterator crend() const
        {
            return const_reverse_iterator(cbegin());
        }

    private:
        pointer _data = nullptr;
        size_type _size = 0;
    };
}

#endif