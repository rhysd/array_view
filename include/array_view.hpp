#if !defined ARV_ARRAY_VIEW_HPP_INCLUDED
#define      ARV_ARRAY_VIEW_HPP_INCLUDED

#include <cstddef>
#include <iterator>
#include <array>

namespace arv {

using std::size_t;

template<class T>
class array_view {
public:
    // types
    typedef T value_type;
    typedef value_type const* pointer;
    typedef value_type const* const_pointer;
    typedef value_type const& reference;
    typedef value_type const& const_reference;
    typedef value_type const* iterator;
    typedef value_type const* const_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // ctors and copy operators
    constexpr array_view() noexept;
    constexpr array_view(array_view const&) noexcept = default;
    template<size_t N>
    constexpr array_view(std::array<T, N> const&) noexcept;
    template<size_t N>
    constexpr array_view(T (&)[N]) noexcept;
    explicit array_view(T const*, size_type const n);
    array_view& operator=(array_view const&) noexcept = default;

    // iterator interfaces
    constexpr const_iterator begin() noexcept const;
    constexpr const_iterator end() noexcept const;
    constexpr const_iterator cbegin() noexcept const;
    constexpr const_iterator cend() noexcept const;
    const_reverse_iterator begin() noexcept const;
    const_reverse_iterator end() noexcept const;
    const_reverse_iterator cbegin() noexcept const;
    const_reverse_iterator cend() noexcept const;

    // access
    constexpr size_type size() noexcept const;
    constexpr size_type length() noexcept const;
    constexpr size_type max_size() noexcept const;
    constexpr bool empty() noexcept const;
    constexpr const_reference operator[](size_type const n) const;
    constexpr const_pointer data() noexcept const;
    constexpr const_reference front() noexcept const;
    constexpr const_reference back() noexcept const;

private:
    size_type const length_;
    const_pointer const data_;
};

} // namespace arv

#endif    // ARV_ARRAY_VIEW_HPP_INCLUDED
