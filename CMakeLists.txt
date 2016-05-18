# Copyright (c) 2016 Jakob Meng, <jakobmeng@web.de>
#
# Redistribution and use is allowed according to the terms of the NYSL license.

cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

#################### project settings ####################

project(array_view)

#################### options ####################

option(ARV_ENABLE_MEMCHECK "Run tests and examples with valgrind." OFF)

#################### find all used packages ####################

find_program(VALGRIND NAMES valgrind)
if(NOT VALGRIND)
	message(WARNING "Could not find 'valgrind' tool, it is required to do benchmarks and tests.")
endif()

find_package(Boost 1.46 COMPONENTS unit_test_framework)
if(NOT Boost_FOUND)
	message(WARNING "Could not find boost libraries, they are required for tests.")
endif()

#################### source settings ####################

# Always include srcdir and builddir in include path
# This saves typing ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} in about every subdir
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Src: kdelibs/cmake/modules/KDE4Defaults.cmake

# put the include dirs which are in the source or build tree before all other include dirs, so the headers in the sources are preferred over the already installed ones
set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)
# Src: kdelibs/cmake/modules/KDE4Defaults.cmake

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${Boost_INCLUDE_DIRS})

enable_testing()

#################### macros ####################

# Inspired by: https://github.com/boostorg/hana/blob/master/CMakeLists.txt
include(CheckCXXCompilerFlag)
macro(arv_maybe_add_flag testname flag)
    set(extra_macro_args ${ARGN})
	check_cxx_compiler_flag(${flag} ${testname})
	if (${testname})
		#add_compile_options(${flag}) # only available in CMake 3.0 and newer.
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" )
	endif()
endmacro()

#################### build settings ####################

arv_maybe_add_flag(ARV_HAS_WALL            "-Wall")
arv_maybe_add_flag(ARV_HAS_WEXTRA          "-Wextra")
arv_maybe_add_flag(ARV_HAS_CXX11           "-std=c++11")

if(NOT ARV_HAS_CXX11)
	message(STATUS "Your C++ compiler ${CMAKE_CXX_COMPILER} does not support '-std=c++11', use it at your own risk.")
endif()

#################### install settings ####################

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.hpp"
)

#################### list the subdirectories ####################

add_subdirectory(test)

