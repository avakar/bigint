cmake_minimum_required(VERSION 3.2)

project(avakar_bigint)

add_library(avakar_bigint
	include/avakar/bigint.h

	src/generic_traits.h
	src/msvc_x86_traits.h
	src/msvc_x86_traits.cpp
	src/traits.h

	src/bigint/bigint.h

	src/cint/README.md
	src/cint/add.h
	src/cint/bitwise.h
	src/cint/cint.h
	src/cint/compare.h
	src/cint/complement.h
	src/cint/digits.h
	src/cint/fwd.h
	src/cint/make.h
	src/cint/mul.h
	src/cint/prepend.h
	src/cint/shift.h
	src/cint/strtoc.h
	src/cint/trim.h
	)
target_include_directories(avakar_bigint PUBLIC include)

add_executable(avakar_bigint_test
	test/test_bigint.cpp
	test/test_cint.cpp
	test/test_main.cpp
	test/test_public.cpp
	)
target_link_libraries(avakar_bigint_test PUBLIC avakar_bigint)

source_group(include\\avakar REGULAR_EXPRESSION include/.*)
source_group(src REGULAR_EXPRESSION src/.*)
source_group(src\\bigint REGULAR_EXPRESSION src/bigint/.*)
source_group(src\\cint REGULAR_EXPRESSION src/cint/.*)
source_group(test REGULAR_EXPRESSION test/.*)
