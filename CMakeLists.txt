cmake_minimum_required(VERSION 3.2)

project(avakar_bigint)

if (MSVC)
	set(bigint_traits_src
		src/msvc_x86_traits.cpp
		src/msvc_x86_traits.h
		)
else()
	set(bigint_traits_src
		src/gcc_traits.cpp
		src/gcc_traits.h
		)
endif()

add_library(avakar_bigint
	include/avakar/bigint.h
	include/avakar/intn.h

	src/digitizer.h
	src/generic_traits.h
	${bigint_traits_src}
	src/traits.h

	src/bigint/bigint.h

	src/cint/README.md
	src/cint/add.h
	src/cint/bitwise.h
	src/cint/cint.h
	src/cint/compare.h
	src/cint/complement.h
	src/cint/digitize.h
	src/cint/digits.h
	src/cint/fwd.h
	src/cint/make.h
	src/cint/mul.h
	src/cint/prepend.h
	src/cint/shift.h
	src/cint/strtoc.h
	src/cint/trim.h

	src/intn/intn.h
	)
target_include_directories(avakar_bigint PUBLIC include)

add_executable(avakar_bigint_test
	test/test_bigint.cpp
	test/test_cint.cpp
	test/test_intn.cpp
	test/test_main.cpp
	test/test_public.cpp
	)
target_link_libraries(avakar_bigint_test PUBLIC avakar_bigint)

set_target_properties(avakar_bigint avakar_bigint_test PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED 1)

source_group(include\\avakar REGULAR_EXPRESSION include/.*)
source_group(src REGULAR_EXPRESSION src/.*)
source_group(src\\bigint REGULAR_EXPRESSION src/bigint/.*)
source_group(src\\cint REGULAR_EXPRESSION src/cint/.*)
source_group(src\\intn REGULAR_EXPRESSION src/intn/.*)
source_group(test REGULAR_EXPRESSION test/.*)
