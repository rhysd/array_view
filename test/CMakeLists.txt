# Copyright (c) 2016 Jakob Meng, <jakobmeng@web.de>
#
# Redistribution and use is allowed according to the terms of the NYSL license.

if(ARV_ENABLE_MEMCHECK AND NOT VALGRIND)
	message(WARNING "Valgrind not found, tests are done without check for memory leaks.")
endif()

if(ARV_ENABLE_MEMCHECK AND VALGRIND)
	function(arv_add_test name)
		add_test(${name} ${VALGRIND} --leak-check=full --error-exitcode=1 ${ARGN})
	endfunction()
else()
	function(arv_add_test name)
		add_test(${name} ${ARGN})
	endfunction()
endif()

############## tests ##############

if (NOT Boost_FOUND)
	message(WARNING "Boost libraries not found, tests disabled.")
	return()
endif()

add_custom_target(tests COMMENT "Build all the tests.")

foreach(target array_view_test)
	add_executable(${target} EXCLUDE_FROM_ALL "${target}.cpp")
	target_link_libraries(${target} ${Boost_LIBRARIES})
	arv_add_test(${target} ${CMAKE_CURRENT_BINARY_DIR}/${target})
	add_dependencies(tests ${target})
endforeach()

