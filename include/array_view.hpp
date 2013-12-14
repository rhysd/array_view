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
    typedef T hoge_type;
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
    array_view(T const*, size_t const n);
    array_view& operator=(array_view const&) noexcept = default;

private:
    size_type const length_;
    const_pointer const data_;
};

} // namespace arv

#endif    // ARV_ARRAY_VIEW_HPP_INCLUDED
