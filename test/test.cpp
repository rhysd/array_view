#define BOOST_TEST_MODULE ArrayViewTest

#include "../include/array_view.hpp"

using arv::array_view;
using arv::make_view;

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(array_view_test)

struct fixture_1_2_3 {
    template<class T>
    bool is_1_2_3(array_view<T> av)
    {
        return av.length() == 3 && av[0] == 1 && av[1] == 2 && av[2] == 3;
    }
};

BOOST_FIXTURE_TEST_CASE(constructors, fixture_1_2_3) {
    constexpr int a[] = {1, 2, 3};
    constexpr std::array<int, 3> ar = {{1, 2, 3}};
    std::vector<int> v = {1, 2, 3};
    array_view<int> av1 = a;
    array_view<int> av2 = ar;
    array_view<int> av3 = v;
    array_view<int> av4{&a[0], sizeof(a)/sizeof(a[0])};
    BOOST_CHECK(is_1_2_3(av1));
    BOOST_CHECK(is_1_2_3(av2));
    BOOST_CHECK(is_1_2_3(av3));
    BOOST_CHECK(is_1_2_3(av4));
}

BOOST_FIXTURE_TEST_CASE(functions_arguments, fixture_1_2_3) {
    constexpr int a[] = {1, 2, 3};
    constexpr std::array<int, 3> ar = {{1, 2, 3}};
    std::vector<int> v = {1, 2, 3};
    BOOST_CHECK(is_1_2_3(make_view(a)));
    BOOST_CHECK(is_1_2_3(make_view(ar)));
    BOOST_CHECK(is_1_2_3(make_view(v)));
    BOOST_CHECK(is_1_2_3(make_view(&a[0], sizeof(a)/sizeof(a[0]))));
}

BOOST_AUTO_TEST_SUITE_END()
