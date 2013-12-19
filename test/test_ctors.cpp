#define BOOST_TEST_MODULE ArrayViewTest
#include "./config.hpp"

BOOST_AUTO_TEST_SUITE(array_view_test)

struct ctor_fixture {
    template<class T>
    bool is_1_2_3(array_view<T> av)
    {
        return av.length() == 3 && av[0] == 1 && av[1] == 2 && av[2] == 3;
    }
};

BOOST_FIXTURE_TEST_CASE(constructors, ctor_fixture) {
    constexpr int a[] = {1, 2, 3};
    constexpr std::array<int, 3> ar = {{1, 2, 3}};
    std::vector<int> v = {1, 2, 3};
    array_view<int> av1 = a;
    array_view<int> av2 = ar;
    array_view<int> av3 = v;
    BOOST_CHECK(is_1_2_3(av1));
    BOOST_CHECK(is_1_2_3(av2));
    BOOST_CHECK(is_1_2_3(av3));
}

BOOST_AUTO_TEST_SUITE_END()
