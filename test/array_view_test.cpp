#define BOOST_TEST_MODULE ArrayViewTest

#include <sstream>
#include <list>

#include "../include/array_view.hpp"
#include "../include/array_view_output.hpp"

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
    array_view<int> av5;
    array_view<int> av6(std::begin(a), std::end(a));
    array_view<int> av11({1, 2, 3});
    BOOST_CHECK(is_1_2_3(av1));
    BOOST_CHECK(is_1_2_3(av2));
    BOOST_CHECK(is_1_2_3(av3));
    BOOST_CHECK(is_1_2_3(av4));
    BOOST_CHECK(is_1_2_3(av6));
    BOOST_CHECK(is_1_2_3(av11));

    // zero size
    constexpr std::array<int, 0> ar2 = {};
    std::vector<int> v2;
    // array_view<int> av7 = a2;
    array_view<int> av7{a, 0};
    array_view<int> av8 = ar2;
    array_view<int> av9 = v2;
    array_view<int> av10(std::begin(ar2), std::end(ar2));
    array_view<int> av12 = {};
    BOOST_CHECK(av7.empty());
    BOOST_CHECK(av8.empty());
    BOOST_CHECK(av9.empty());
    BOOST_CHECK(av10.empty());
    BOOST_CHECK(av12.empty());
}

BOOST_AUTO_TEST_CASE(check_make_view) {
    constexpr int a[] = {1, 2, 3};
    constexpr std::array<int, 3> ar = {{1, 2, 3}};
    std::vector<int> v = {1, 2, 3};
    auto il = {1, 2, 3};
    array_view<int> av = il;
    BOOST_CHECK(av == make_view(a));
    BOOST_CHECK(av == make_view(ar));
    BOOST_CHECK(av == make_view(v));
    BOOST_CHECK(av == make_view(il));
    BOOST_CHECK(av == make_view(&a[0], 3));
    BOOST_CHECK(av == make_view(ar.begin(), ar.end()));
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

BOOST_AUTO_TEST_CASE(explicit_conversion) {
    constexpr int a[] = {1, 2, 3};
    auto av = make_view(a);
    std::array<int, 3> ar = {{1, 2, 3}};
    BOOST_CHECK(std::vector<int>({1, 2, 3}) == av.to_vector());
    BOOST_CHECK(ar == av.to_array<3>());
}

BOOST_AUTO_TEST_CASE(compare_operators) {
    constexpr int a[] = {1, 2, 3};
    constexpr int a2[] = {1, 1, 2, 3, 5};
    constexpr std::array<int, 3> ar = {{1, 2, 3}};
    std::vector<int> v = {1, 2, 3};
    auto av = make_view(a);
    auto av2 = make_view(a2);
    auto il = {1, 2, 3};
    BOOST_CHECK(av == av);
    BOOST_CHECK(av != a2);
    BOOST_CHECK(av == a);
    BOOST_CHECK(av2 != a);
    BOOST_CHECK(av == ar);
    BOOST_CHECK(av2 != ar);
    BOOST_CHECK(av == v);
    BOOST_CHECK(av2 != v);
    BOOST_CHECK(av == il);
    BOOST_CHECK(av2 != il);
    BOOST_CHECK(a == av);
    BOOST_CHECK(a != av2);
    BOOST_CHECK(ar == av);
    BOOST_CHECK(ar != av2);
    BOOST_CHECK(v == av);
    BOOST_CHECK(v != av2);
    BOOST_CHECK(il == av);
    BOOST_CHECK(il != av2);
}

BOOST_AUTO_TEST_CASE(array_view_output) {
    std::stringstream ss;
    ss << make_view({1, 2, 3});
    BOOST_CHECK(ss.str() == "{1, 2, 3}");
    ss << array_view<int>{};
    BOOST_CHECK(ss.str() == "{1, 2, 3}{}");
    ss << make_view({"aaa", "bbb", "ccc"});
    BOOST_CHECK(ss.str() == "{1, 2, 3}{}{aaa, bbb, ccc}");
}

BOOST_AUTO_TEST_CASE(is_array_meta_function) {
    typedef std::array<int, 3> array_int_3;
    BOOST_CHECK(arv::is_array<array_int_3>::value);
    BOOST_CHECK(arv::is_array<std::vector<int>>::value);
    BOOST_CHECK(arv::is_array<std::initializer_list<int>>::value);
    BOOST_CHECK(arv::is_array<int [3]>::value);
    BOOST_CHECK(!arv::is_array<int>::value);
    BOOST_CHECK(!arv::is_array<int *>::value);
    BOOST_CHECK(!arv::is_array<std::list<int>>::value);
}

BOOST_AUTO_TEST_CASE(non_safe_slice) {
    auto il = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    array_view<int> av = il;

    // Note: Work around for BOOST_CHECK.
    // It seems that {a, b} is not available in BOOST_CHECK().
    BOOST_CHECK(av.slice(2, 5) == make_view({3, 4, 5, 6, 7}));
    BOOST_CHECK(av.slice_before(5) == make_view({1, 2, 3, 4, 5}));
    BOOST_CHECK(av.slice_after(5) == make_view({6, 7, 8, 9}));
    BOOST_CHECK(av.slice(av.begin()+2, av.begin()+7) == make_view({3, 4, 5, 6, 7}));
    BOOST_CHECK(av.slice_before(av.begin()+5) == make_view({1, 2, 3, 4, 5}));
    BOOST_CHECK(av.slice_after(av.begin()+5) == make_view({6, 7, 8, 9}));
}

BOOST_AUTO_TEST_CASE(safe_slice) {
    auto il = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    array_view<int> av = il;

    using arv::check_bound;

    // Note: Work around for BOOST_CHECK.
    // It seems that {a, b} is not available in BOOST_CHECK().
    BOOST_CHECK(av.slice(check_bound, 2, 5) == make_view({3, 4, 5, 6, 7}));
    BOOST_CHECK(av.slice(check_bound, 2, 0).empty() );
    BOOST_CHECK(av.slice_before(check_bound, 5) == make_view({1, 2, 3, 4, 5}));
    BOOST_CHECK(av.slice_after(check_bound, 5) == make_view({6, 7, 8, 9}));
    BOOST_CHECK(av.slice(check_bound, av.begin()+2, av.begin()+7) == make_view({3, 4, 5, 6, 7}));
    BOOST_CHECK(av.slice(check_bound, av.begin()+2, av.begin()+2).empty() );
    BOOST_CHECK(av.slice_before(check_bound, av.begin()+5) == make_view({1, 2, 3, 4, 5}));
    BOOST_CHECK(av.slice_after(check_bound, av.begin()+5) == make_view({6, 7, 8, 9}));

    // Throw an exception when boundary check fails
    BOOST_CHECK_THROW(av.slice(check_bound, 10, 1), std::out_of_range);
    BOOST_CHECK_THROW(av.slice(check_bound, 1, 10), std::out_of_range);
    BOOST_CHECK_THROW(av.slice(check_bound, 10, 10), std::out_of_range);
    BOOST_CHECK_THROW(av.slice_before(check_bound, 10), std::out_of_range);
    BOOST_CHECK_THROW(av.slice_after(check_bound, 10), std::out_of_range);
    BOOST_CHECK_THROW(av.slice(check_bound, av.begin() + 3, av.begin() + 1), std::out_of_range);
    BOOST_CHECK_THROW(av.slice(check_bound, av.begin() + 10, av.begin() + 11), std::out_of_range);
    BOOST_CHECK_THROW(av.slice(check_bound, av.begin(), av.begin() + 11), std::out_of_range);
    BOOST_CHECK_THROW(av.slice(check_bound, av.begin() + 11, av.begin() + 11), std::out_of_range);
    BOOST_CHECK_THROW(av.slice_before(check_bound, av.begin() + 11), std::out_of_range);
    BOOST_CHECK_THROW(av.slice_after(check_bound, av.begin() + 11), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
