#if !defined ARV_ARRAY_VIEW_OUTPUT_HPP_INCLUDED
#define      ARV_ARRAY_VIEW_OUTPUT_HPP_INCLUDED

#include <ostream>

namespace arv {
template<class T>
class array_view;
} // namespace arv

template<class T>
std::ostream &operator<<(std::ostream &ost, arv::array_view<T> const& av)
{
    ost << '{';

    if(! av.empty()) {
        auto itr = std::begin(av);
        auto const end = std::end(av);
        while(true) {
            ost << *itr;
            if(++itr != end) {
                ost << ", ";
            } else {
                break;
            }
        }
    }

    ost << '}';
    return ost;
}

#endif    // ARV_ARRAY_VIEW_OUTPUT_HPP_INCLUDED
