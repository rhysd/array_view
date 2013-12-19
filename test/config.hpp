#if !defined CONFIG_HPP_INCLUDED
#define      CONFIG_HPP_INCLUDED

#include "../include/array_view.hpp"

using arv::array_view;
using arv::make_view;

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#endif    // CONFIG_HPP_INCLUDED
