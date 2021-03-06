#include <avakar/bigint.h>

#include "catch.hpp"

using B = avakar::bigint;

TEST_CASE("bigint: public mul")
{
	using avakar::operator""_z;

	REQUIRE(B(0_z) * B(-1_z) == B(0_z));
	REQUIRE(B(0_z) * B(0_z) == B(0_z));
	REQUIRE(B(0_z) * B(1_z) == B(0_z));
	REQUIRE(B(1_z) * B(-1_z) == B(-1_z));
	REQUIRE(B(1_z) * B(0_z) == B(0_z));
	REQUIRE(B(1_z) * B(1_z) == B(1_z));
	REQUIRE(B(-1_z) * B(-1_z) == B(1_z));
	REQUIRE(B(-1_z) * B(0_z) == B(0_z));
	REQUIRE(B(-1_z) * B(1_z) == B(-1_z));

	REQUIRE(B(-0x100000001_z) * B(-0x100000001_z) == B(0x10000000200000001_z));
	REQUIRE(B(-0x100000001_z) * B(-0x100000000_z) == B(0x10000000100000000_z));
	REQUIRE(B(-0x100000001_z) * B(-0xffffffff_z) == B(0xffffffffffffffff_z));
	REQUIRE(B(-0x100000001_z) * B(-0x80000001_z) == B(0x8000000180000001_z));
	REQUIRE(B(-0x100000001_z) * B(-0x80000000_z) == B(0x8000000080000000_z));
	REQUIRE(B(-0x100000001_z) * B(-0x7fffffff_z) == B(0x7fffffff7fffffff_z));
	REQUIRE(B(-0x100000001_z) * B(-0x10001_z) == B(0x1000100010001_z));
	REQUIRE(B(-0x100000001_z) * B(-0x10000_z) == B(0x1000000010000_z));
	REQUIRE(B(-0x100000001_z) * B(-0xffff_z) == B(0xffff0000ffff_z));
	REQUIRE(B(-0x100000001_z) * B(-0x8001_z) == B(0x800100008001_z));
	REQUIRE(B(-0x100000001_z) * B(-0x8000_z) == B(0x800000008000_z));
	REQUIRE(B(-0x100000001_z) * B(-0x7fff_z) == B(0x7fff00007fff_z));
	REQUIRE(B(-0x100000001_z) * B(0x7fff_z) == B(-0x7fff00007fff_z));
	REQUIRE(B(-0x100000001_z) * B(0x8000_z) == B(-0x800000008000_z));
	REQUIRE(B(-0x100000001_z) * B(0x8001_z) == B(-0x800100008001_z));
	REQUIRE(B(-0x100000001_z) * B(0xffff_z) == B(-0xffff0000ffff_z));
	REQUIRE(B(-0x100000001_z) * B(0x10000_z) == B(-0x1000000010000_z));
	REQUIRE(B(-0x100000001_z) * B(0x10001_z) == B(-0x1000100010001_z));
	REQUIRE(B(-0x100000001_z) * B(0x7fffffff_z) == B(-0x7fffffff7fffffff_z));
	REQUIRE(B(-0x100000001_z) * B(0x80000000_z) == B(-0x8000000080000000_z));
	REQUIRE(B(-0x100000001_z) * B(0x80000001_z) == B(-0x8000000180000001_z));
	REQUIRE(B(-0x100000001_z) * B(0xffffffff_z) == B(-0xffffffffffffffff_z));
	REQUIRE(B(-0x100000001_z) * B(0x100000000_z) == B(-0x10000000100000000_z));
	REQUIRE(B(-0x100000001_z) * B(0x100000001_z) == B(-0x10000000200000001_z));
	REQUIRE(B(-0x100000000_z) * B(-0x100000001_z) == B(0x10000000100000000_z));
	REQUIRE(B(-0x100000000_z) * B(-0x100000000_z) == B(0x10000000000000000_z));
	REQUIRE(B(-0x100000000_z) * B(-0xffffffff_z) == B(0xffffffff00000000_z));
	REQUIRE(B(-0x100000000_z) * B(-0x80000001_z) == B(0x8000000100000000_z));
	REQUIRE(B(-0x100000000_z) * B(-0x80000000_z) == B(0x8000000000000000_z));
	REQUIRE(B(-0x100000000_z) * B(-0x7fffffff_z) == B(0x7fffffff00000000_z));
	REQUIRE(B(-0x100000000_z) * B(-0x10001_z) == B(0x1000100000000_z));
	REQUIRE(B(-0x100000000_z) * B(-0x10000_z) == B(0x1000000000000_z));
	REQUIRE(B(-0x100000000_z) * B(-0xffff_z) == B(0xffff00000000_z));
	REQUIRE(B(-0x100000000_z) * B(-0x8001_z) == B(0x800100000000_z));
	REQUIRE(B(-0x100000000_z) * B(-0x8000_z) == B(0x800000000000_z));
	REQUIRE(B(-0x100000000_z) * B(-0x7fff_z) == B(0x7fff00000000_z));
	REQUIRE(B(-0x100000000_z) * B(0x7fff_z) == B(-0x7fff00000000_z));
	REQUIRE(B(-0x100000000_z) * B(0x8000_z) == B(-0x800000000000_z));
	REQUIRE(B(-0x100000000_z) * B(0x8001_z) == B(-0x800100000000_z));
	REQUIRE(B(-0x100000000_z) * B(0xffff_z) == B(-0xffff00000000_z));
	REQUIRE(B(-0x100000000_z) * B(0x10000_z) == B(-0x1000000000000_z));
	REQUIRE(B(-0x100000000_z) * B(0x10001_z) == B(-0x1000100000000_z));
	REQUIRE(B(-0x100000000_z) * B(0x7fffffff_z) == B(-0x7fffffff00000000_z));
	REQUIRE(B(-0x100000000_z) * B(0x80000000_z) == B(-0x8000000000000000_z));
	REQUIRE(B(-0x100000000_z) * B(0x80000001_z) == B(-0x8000000100000000_z));
	REQUIRE(B(-0x100000000_z) * B(0xffffffff_z) == B(-0xffffffff00000000_z));
	REQUIRE(B(-0x100000000_z) * B(0x100000000_z) == B(-0x10000000000000000_z));
	REQUIRE(B(-0x100000000_z) * B(0x100000001_z) == B(-0x10000000100000000_z));
	REQUIRE(B(-0xffffffff_z) * B(-0x100000001_z) == B(0xffffffffffffffff_z));
	REQUIRE(B(-0xffffffff_z) * B(-0x100000000_z) == B(0xffffffff00000000_z));
	REQUIRE(B(-0xffffffff_z) * B(-0xffffffff_z) == B(0xfffffffe00000001_z));
	REQUIRE(B(-0xffffffff_z) * B(-0x80000001_z) == B(0x800000007fffffff_z));
	REQUIRE(B(-0xffffffff_z) * B(-0x80000000_z) == B(0x7fffffff80000000_z));
	REQUIRE(B(-0xffffffff_z) * B(-0x7fffffff_z) == B(0x7ffffffe80000001_z));
	REQUIRE(B(-0xffffffff_z) * B(-0x10001_z) == B(0x10000fffeffff_z));
	REQUIRE(B(-0xffffffff_z) * B(-0x10000_z) == B(0xffffffff0000_z));
	REQUIRE(B(-0xffffffff_z) * B(-0xffff_z) == B(0xfffeffff0001_z));
	REQUIRE(B(-0xffffffff_z) * B(-0x8001_z) == B(0x8000ffff7fff_z));
	REQUIRE(B(-0xffffffff_z) * B(-0x8000_z) == B(0x7fffffff8000_z));
	REQUIRE(B(-0xffffffff_z) * B(-0x7fff_z) == B(0x7ffeffff8001_z));
	REQUIRE(B(-0xffffffff_z) * B(0x7fff_z) == B(-0x7ffeffff8001_z));
	REQUIRE(B(-0xffffffff_z) * B(0x8000_z) == B(-0x7fffffff8000_z));
	REQUIRE(B(-0xffffffff_z) * B(0x8001_z) == B(-0x8000ffff7fff_z));
	REQUIRE(B(-0xffffffff_z) * B(0xffff_z) == B(-0xfffeffff0001_z));
	REQUIRE(B(-0xffffffff_z) * B(0x10000_z) == B(-0xffffffff0000_z));
	REQUIRE(B(-0xffffffff_z) * B(0x10001_z) == B(-0x10000fffeffff_z));
	REQUIRE(B(-0xffffffff_z) * B(0x7fffffff_z) == B(-0x7ffffffe80000001_z));
	REQUIRE(B(-0xffffffff_z) * B(0x80000000_z) == B(-0x7fffffff80000000_z));
	REQUIRE(B(-0xffffffff_z) * B(0x80000001_z) == B(-0x800000007fffffff_z));
	REQUIRE(B(-0xffffffff_z) * B(0xffffffff_z) == B(-0xfffffffe00000001_z));
	REQUIRE(B(-0xffffffff_z) * B(0x100000000_z) == B(-0xffffffff00000000_z));
	REQUIRE(B(-0xffffffff_z) * B(0x100000001_z) == B(-0xffffffffffffffff_z));
	REQUIRE(B(-0x80000001_z) * B(-0x100000001_z) == B(0x8000000180000001_z));
	REQUIRE(B(-0x80000001_z) * B(-0x100000000_z) == B(0x8000000100000000_z));
	REQUIRE(B(-0x80000001_z) * B(-0xffffffff_z) == B(0x800000007fffffff_z));
	REQUIRE(B(-0x80000001_z) * B(-0x80000001_z) == B(0x4000000100000001_z));
	REQUIRE(B(-0x80000001_z) * B(-0x80000000_z) == B(0x4000000080000000_z));
	REQUIRE(B(-0x80000001_z) * B(-0x7fffffff_z) == B(0x3fffffffffffffff_z));
	REQUIRE(B(-0x80000001_z) * B(-0x10001_z) == B(0x800080010001_z));
	REQUIRE(B(-0x80000001_z) * B(-0x10000_z) == B(0x800000010000_z));
	REQUIRE(B(-0x80000001_z) * B(-0xffff_z) == B(0x7fff8000ffff_z));
	REQUIRE(B(-0x80000001_z) * B(-0x8001_z) == B(0x400080008001_z));
	REQUIRE(B(-0x80000001_z) * B(-0x8000_z) == B(0x400000008000_z));
	REQUIRE(B(-0x80000001_z) * B(-0x7fff_z) == B(0x3fff80007fff_z));
	REQUIRE(B(-0x80000001_z) * B(0x7fff_z) == B(-0x3fff80007fff_z));
	REQUIRE(B(-0x80000001_z) * B(0x8000_z) == B(-0x400000008000_z));
	REQUIRE(B(-0x80000001_z) * B(0x8001_z) == B(-0x400080008001_z));
	REQUIRE(B(-0x80000001_z) * B(0xffff_z) == B(-0x7fff8000ffff_z));
	REQUIRE(B(-0x80000001_z) * B(0x10000_z) == B(-0x800000010000_z));
	REQUIRE(B(-0x80000001_z) * B(0x10001_z) == B(-0x800080010001_z));
	REQUIRE(B(-0x80000001_z) * B(0x7fffffff_z) == B(-0x3fffffffffffffff_z));
	REQUIRE(B(-0x80000001_z) * B(0x80000000_z) == B(-0x4000000080000000_z));
	REQUIRE(B(-0x80000001_z) * B(0x80000001_z) == B(-0x4000000100000001_z));
	REQUIRE(B(-0x80000001_z) * B(0xffffffff_z) == B(-0x800000007fffffff_z));
	REQUIRE(B(-0x80000001_z) * B(0x100000000_z) == B(-0x8000000100000000_z));
	REQUIRE(B(-0x80000001_z) * B(0x100000001_z) == B(-0x8000000180000001_z));
	REQUIRE(B(-0x80000000_z) * B(-0x100000001_z) == B(0x8000000080000000_z));
	REQUIRE(B(-0x80000000_z) * B(-0x100000000_z) == B(0x8000000000000000_z));
	REQUIRE(B(-0x80000000_z) * B(-0xffffffff_z) == B(0x7fffffff80000000_z));
	REQUIRE(B(-0x80000000_z) * B(-0x80000001_z) == B(0x4000000080000000_z));
	REQUIRE(B(-0x80000000_z) * B(-0x80000000_z) == B(0x4000000000000000_z));
	REQUIRE(B(-0x80000000_z) * B(-0x7fffffff_z) == B(0x3fffffff80000000_z));
	REQUIRE(B(-0x80000000_z) * B(-0x10001_z) == B(0x800080000000_z));
	REQUIRE(B(-0x80000000_z) * B(-0x10000_z) == B(0x800000000000_z));
	REQUIRE(B(-0x80000000_z) * B(-0xffff_z) == B(0x7fff80000000_z));
	REQUIRE(B(-0x80000000_z) * B(-0x8001_z) == B(0x400080000000_z));
	REQUIRE(B(-0x80000000_z) * B(-0x8000_z) == B(0x400000000000_z));
	REQUIRE(B(-0x80000000_z) * B(-0x7fff_z) == B(0x3fff80000000_z));
	REQUIRE(B(-0x80000000_z) * B(0x7fff_z) == B(-0x3fff80000000_z));
	REQUIRE(B(-0x80000000_z) * B(0x8000_z) == B(-0x400000000000_z));
	REQUIRE(B(-0x80000000_z) * B(0x8001_z) == B(-0x400080000000_z));
	REQUIRE(B(-0x80000000_z) * B(0xffff_z) == B(-0x7fff80000000_z));
	REQUIRE(B(-0x80000000_z) * B(0x10000_z) == B(-0x800000000000_z));
	REQUIRE(B(-0x80000000_z) * B(0x10001_z) == B(-0x800080000000_z));
	REQUIRE(B(-0x80000000_z) * B(0x7fffffff_z) == B(-0x3fffffff80000000_z));
	REQUIRE(B(-0x80000000_z) * B(0x80000000_z) == B(-0x4000000000000000_z));
	REQUIRE(B(-0x80000000_z) * B(0x80000001_z) == B(-0x4000000080000000_z));
	REQUIRE(B(-0x80000000_z) * B(0xffffffff_z) == B(-0x7fffffff80000000_z));
	REQUIRE(B(-0x80000000_z) * B(0x100000000_z) == B(-0x8000000000000000_z));
	REQUIRE(B(-0x80000000_z) * B(0x100000001_z) == B(-0x8000000080000000_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0x100000001_z) == B(0x7fffffff7fffffff_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0x100000000_z) == B(0x7fffffff00000000_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0xffffffff_z) == B(0x7ffffffe80000001_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0x80000001_z) == B(0x3fffffffffffffff_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0x80000000_z) == B(0x3fffffff80000000_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0x7fffffff_z) == B(0x3fffffff00000001_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0x10001_z) == B(0x80007ffeffff_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0x10000_z) == B(0x7fffffff0000_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0xffff_z) == B(0x7fff7fff0001_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0x8001_z) == B(0x40007fff7fff_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0x8000_z) == B(0x3fffffff8000_z));
	REQUIRE(B(-0x7fffffff_z) * B(-0x7fff_z) == B(0x3fff7fff8001_z));
	REQUIRE(B(-0x7fffffff_z) * B(0x7fff_z) == B(-0x3fff7fff8001_z));
	REQUIRE(B(-0x7fffffff_z) * B(0x8000_z) == B(-0x3fffffff8000_z));
	REQUIRE(B(-0x7fffffff_z) * B(0x8001_z) == B(-0x40007fff7fff_z));
	REQUIRE(B(-0x7fffffff_z) * B(0xffff_z) == B(-0x7fff7fff0001_z));
	REQUIRE(B(-0x7fffffff_z) * B(0x10000_z) == B(-0x7fffffff0000_z));
	REQUIRE(B(-0x7fffffff_z) * B(0x10001_z) == B(-0x80007ffeffff_z));
	REQUIRE(B(-0x7fffffff_z) * B(0x7fffffff_z) == B(-0x3fffffff00000001_z));
	REQUIRE(B(-0x7fffffff_z) * B(0x80000000_z) == B(-0x3fffffff80000000_z));
	REQUIRE(B(-0x7fffffff_z) * B(0x80000001_z) == B(-0x3fffffffffffffff_z));
	REQUIRE(B(-0x7fffffff_z) * B(0xffffffff_z) == B(-0x7ffffffe80000001_z));
	REQUIRE(B(-0x7fffffff_z) * B(0x100000000_z) == B(-0x7fffffff00000000_z));
	REQUIRE(B(-0x7fffffff_z) * B(0x100000001_z) == B(-0x7fffffff7fffffff_z));
	REQUIRE(B(-0x10001_z) * B(-0x100000001_z) == B(0x1000100010001_z));
	REQUIRE(B(-0x10001_z) * B(-0x100000000_z) == B(0x1000100000000_z));
	REQUIRE(B(-0x10001_z) * B(-0xffffffff_z) == B(0x10000fffeffff_z));
	REQUIRE(B(-0x10001_z) * B(-0x80000001_z) == B(0x800080010001_z));
	REQUIRE(B(-0x10001_z) * B(-0x80000000_z) == B(0x800080000000_z));
	REQUIRE(B(-0x10001_z) * B(-0x7fffffff_z) == B(0x80007ffeffff_z));
	REQUIRE(B(-0x10001_z) * B(-0x10001_z) == B(0x100020001_z));
	REQUIRE(B(-0x10001_z) * B(-0x10000_z) == B(0x100010000_z));
	REQUIRE(B(-0x10001_z) * B(-0xffff_z) == B(0xffffffff_z));
	REQUIRE(B(-0x10001_z) * B(-0x8001_z) == B(0x80018001_z));
	REQUIRE(B(-0x10001_z) * B(-0x8000_z) == B(0x80008000_z));
	REQUIRE(B(-0x10001_z) * B(-0x7fff_z) == B(0x7fff7fff_z));
	REQUIRE(B(-0x10001_z) * B(0x7fff_z) == B(-0x7fff7fff_z));
	REQUIRE(B(-0x10001_z) * B(0x8000_z) == B(-0x80008000_z));
	REQUIRE(B(-0x10001_z) * B(0x8001_z) == B(-0x80018001_z));
	REQUIRE(B(-0x10001_z) * B(0xffff_z) == B(-0xffffffff_z));
	REQUIRE(B(-0x10001_z) * B(0x10000_z) == B(-0x100010000_z));
	REQUIRE(B(-0x10001_z) * B(0x10001_z) == B(-0x100020001_z));
	REQUIRE(B(-0x10001_z) * B(0x7fffffff_z) == B(-0x80007ffeffff_z));
	REQUIRE(B(-0x10001_z) * B(0x80000000_z) == B(-0x800080000000_z));
	REQUIRE(B(-0x10001_z) * B(0x80000001_z) == B(-0x800080010001_z));
	REQUIRE(B(-0x10001_z) * B(0xffffffff_z) == B(-0x10000fffeffff_z));
	REQUIRE(B(-0x10001_z) * B(0x100000000_z) == B(-0x1000100000000_z));
	REQUIRE(B(-0x10001_z) * B(0x100000001_z) == B(-0x1000100010001_z));
	REQUIRE(B(-0x10000_z) * B(-0x100000001_z) == B(0x1000000010000_z));
	REQUIRE(B(-0x10000_z) * B(-0x100000000_z) == B(0x1000000000000_z));
	REQUIRE(B(-0x10000_z) * B(-0xffffffff_z) == B(0xffffffff0000_z));
	REQUIRE(B(-0x10000_z) * B(-0x80000001_z) == B(0x800000010000_z));
	REQUIRE(B(-0x10000_z) * B(-0x80000000_z) == B(0x800000000000_z));
	REQUIRE(B(-0x10000_z) * B(-0x7fffffff_z) == B(0x7fffffff0000_z));
	REQUIRE(B(-0x10000_z) * B(-0x10001_z) == B(0x100010000_z));
	REQUIRE(B(-0x10000_z) * B(-0x10000_z) == B(0x100000000_z));
	REQUIRE(B(-0x10000_z) * B(-0xffff_z) == B(0xffff0000_z));
	REQUIRE(B(-0x10000_z) * B(-0x8001_z) == B(0x80010000_z));
	REQUIRE(B(-0x10000_z) * B(-0x8000_z) == B(0x80000000_z));
	REQUIRE(B(-0x10000_z) * B(-0x7fff_z) == B(0x7fff0000_z));
	REQUIRE(B(-0x10000_z) * B(0x7fff_z) == B(-0x7fff0000_z));
	REQUIRE(B(-0x10000_z) * B(0x8000_z) == B(-0x80000000_z));
	REQUIRE(B(-0x10000_z) * B(0x8001_z) == B(-0x80010000_z));
	REQUIRE(B(-0x10000_z) * B(0xffff_z) == B(-0xffff0000_z));
	REQUIRE(B(-0x10000_z) * B(0x10000_z) == B(-0x100000000_z));
	REQUIRE(B(-0x10000_z) * B(0x10001_z) == B(-0x100010000_z));
	REQUIRE(B(-0x10000_z) * B(0x7fffffff_z) == B(-0x7fffffff0000_z));
	REQUIRE(B(-0x10000_z) * B(0x80000000_z) == B(-0x800000000000_z));
	REQUIRE(B(-0x10000_z) * B(0x80000001_z) == B(-0x800000010000_z));
	REQUIRE(B(-0x10000_z) * B(0xffffffff_z) == B(-0xffffffff0000_z));
	REQUIRE(B(-0x10000_z) * B(0x100000000_z) == B(-0x1000000000000_z));
	REQUIRE(B(-0x10000_z) * B(0x100000001_z) == B(-0x1000000010000_z));
	REQUIRE(B(-0xffff_z) * B(-0x100000001_z) == B(0xffff0000ffff_z));
	REQUIRE(B(-0xffff_z) * B(-0x100000000_z) == B(0xffff00000000_z));
	REQUIRE(B(-0xffff_z) * B(-0xffffffff_z) == B(0xfffeffff0001_z));
	REQUIRE(B(-0xffff_z) * B(-0x80000001_z) == B(0x7fff8000ffff_z));
	REQUIRE(B(-0xffff_z) * B(-0x80000000_z) == B(0x7fff80000000_z));
	REQUIRE(B(-0xffff_z) * B(-0x7fffffff_z) == B(0x7fff7fff0001_z));
	REQUIRE(B(-0xffff_z) * B(-0x10001_z) == B(0xffffffff_z));
	REQUIRE(B(-0xffff_z) * B(-0x10000_z) == B(0xffff0000_z));
	REQUIRE(B(-0xffff_z) * B(-0xffff_z) == B(0xfffe0001_z));
	REQUIRE(B(-0xffff_z) * B(-0x8001_z) == B(0x80007fff_z));
	REQUIRE(B(-0xffff_z) * B(-0x8000_z) == B(0x7fff8000_z));
	REQUIRE(B(-0xffff_z) * B(-0x7fff_z) == B(0x7ffe8001_z));
	REQUIRE(B(-0xffff_z) * B(0x7fff_z) == B(-0x7ffe8001_z));
	REQUIRE(B(-0xffff_z) * B(0x8000_z) == B(-0x7fff8000_z));
	REQUIRE(B(-0xffff_z) * B(0x8001_z) == B(-0x80007fff_z));
	REQUIRE(B(-0xffff_z) * B(0xffff_z) == B(-0xfffe0001_z));
	REQUIRE(B(-0xffff_z) * B(0x10000_z) == B(-0xffff0000_z));
	REQUIRE(B(-0xffff_z) * B(0x10001_z) == B(-0xffffffff_z));
	REQUIRE(B(-0xffff_z) * B(0x7fffffff_z) == B(-0x7fff7fff0001_z));
	REQUIRE(B(-0xffff_z) * B(0x80000000_z) == B(-0x7fff80000000_z));
	REQUIRE(B(-0xffff_z) * B(0x80000001_z) == B(-0x7fff8000ffff_z));
	REQUIRE(B(-0xffff_z) * B(0xffffffff_z) == B(-0xfffeffff0001_z));
	REQUIRE(B(-0xffff_z) * B(0x100000000_z) == B(-0xffff00000000_z));
	REQUIRE(B(-0xffff_z) * B(0x100000001_z) == B(-0xffff0000ffff_z));
	REQUIRE(B(-0x8001_z) * B(-0x100000001_z) == B(0x800100008001_z));
	REQUIRE(B(-0x8001_z) * B(-0x100000000_z) == B(0x800100000000_z));
	REQUIRE(B(-0x8001_z) * B(-0xffffffff_z) == B(0x8000ffff7fff_z));
	REQUIRE(B(-0x8001_z) * B(-0x80000001_z) == B(0x400080008001_z));
	REQUIRE(B(-0x8001_z) * B(-0x80000000_z) == B(0x400080000000_z));
	REQUIRE(B(-0x8001_z) * B(-0x7fffffff_z) == B(0x40007fff7fff_z));
	REQUIRE(B(-0x8001_z) * B(-0x10001_z) == B(0x80018001_z));
	REQUIRE(B(-0x8001_z) * B(-0x10000_z) == B(0x80010000_z));
	REQUIRE(B(-0x8001_z) * B(-0xffff_z) == B(0x80007fff_z));
	REQUIRE(B(-0x8001_z) * B(-0x8001_z) == B(0x40010001_z));
	REQUIRE(B(-0x8001_z) * B(-0x8000_z) == B(0x40008000_z));
	REQUIRE(B(-0x8001_z) * B(-0x7fff_z) == B(0x3fffffff_z));
	REQUIRE(B(-0x8001_z) * B(0x7fff_z) == B(-0x3fffffff_z));
	REQUIRE(B(-0x8001_z) * B(0x8000_z) == B(-0x40008000_z));
	REQUIRE(B(-0x8001_z) * B(0x8001_z) == B(-0x40010001_z));
	REQUIRE(B(-0x8001_z) * B(0xffff_z) == B(-0x80007fff_z));
	REQUIRE(B(-0x8001_z) * B(0x10000_z) == B(-0x80010000_z));
	REQUIRE(B(-0x8001_z) * B(0x10001_z) == B(-0x80018001_z));
	REQUIRE(B(-0x8001_z) * B(0x7fffffff_z) == B(-0x40007fff7fff_z));
	REQUIRE(B(-0x8001_z) * B(0x80000000_z) == B(-0x400080000000_z));
	REQUIRE(B(-0x8001_z) * B(0x80000001_z) == B(-0x400080008001_z));
	REQUIRE(B(-0x8001_z) * B(0xffffffff_z) == B(-0x8000ffff7fff_z));
	REQUIRE(B(-0x8001_z) * B(0x100000000_z) == B(-0x800100000000_z));
	REQUIRE(B(-0x8001_z) * B(0x100000001_z) == B(-0x800100008001_z));
	REQUIRE(B(-0x8000_z) * B(-0x100000001_z) == B(0x800000008000_z));
	REQUIRE(B(-0x8000_z) * B(-0x100000000_z) == B(0x800000000000_z));
	REQUIRE(B(-0x8000_z) * B(-0xffffffff_z) == B(0x7fffffff8000_z));
	REQUIRE(B(-0x8000_z) * B(-0x80000001_z) == B(0x400000008000_z));
	REQUIRE(B(-0x8000_z) * B(-0x80000000_z) == B(0x400000000000_z));
	REQUIRE(B(-0x8000_z) * B(-0x7fffffff_z) == B(0x3fffffff8000_z));
	REQUIRE(B(-0x8000_z) * B(-0x10001_z) == B(0x80008000_z));
	REQUIRE(B(-0x8000_z) * B(-0x10000_z) == B(0x80000000_z));
	REQUIRE(B(-0x8000_z) * B(-0xffff_z) == B(0x7fff8000_z));
	REQUIRE(B(-0x8000_z) * B(-0x8001_z) == B(0x40008000_z));
	REQUIRE(B(-0x8000_z) * B(-0x8000_z) == B(0x40000000_z));
	REQUIRE(B(-0x8000_z) * B(-0x7fff_z) == B(0x3fff8000_z));
	REQUIRE(B(-0x8000_z) * B(0x7fff_z) == B(-0x3fff8000_z));
	REQUIRE(B(-0x8000_z) * B(0x8000_z) == B(-0x40000000_z));
	REQUIRE(B(-0x8000_z) * B(0x8001_z) == B(-0x40008000_z));
	REQUIRE(B(-0x8000_z) * B(0xffff_z) == B(-0x7fff8000_z));
	REQUIRE(B(-0x8000_z) * B(0x10000_z) == B(-0x80000000_z));
	REQUIRE(B(-0x8000_z) * B(0x10001_z) == B(-0x80008000_z));
	REQUIRE(B(-0x8000_z) * B(0x7fffffff_z) == B(-0x3fffffff8000_z));
	REQUIRE(B(-0x8000_z) * B(0x80000000_z) == B(-0x400000000000_z));
	REQUIRE(B(-0x8000_z) * B(0x80000001_z) == B(-0x400000008000_z));
	REQUIRE(B(-0x8000_z) * B(0xffffffff_z) == B(-0x7fffffff8000_z));
	REQUIRE(B(-0x8000_z) * B(0x100000000_z) == B(-0x800000000000_z));
	REQUIRE(B(-0x8000_z) * B(0x100000001_z) == B(-0x800000008000_z));
	REQUIRE(B(-0x7fff_z) * B(-0x100000001_z) == B(0x7fff00007fff_z));
	REQUIRE(B(-0x7fff_z) * B(-0x100000000_z) == B(0x7fff00000000_z));
	REQUIRE(B(-0x7fff_z) * B(-0xffffffff_z) == B(0x7ffeffff8001_z));
	REQUIRE(B(-0x7fff_z) * B(-0x80000001_z) == B(0x3fff80007fff_z));
	REQUIRE(B(-0x7fff_z) * B(-0x80000000_z) == B(0x3fff80000000_z));
	REQUIRE(B(-0x7fff_z) * B(-0x7fffffff_z) == B(0x3fff7fff8001_z));
	REQUIRE(B(-0x7fff_z) * B(-0x10001_z) == B(0x7fff7fff_z));
	REQUIRE(B(-0x7fff_z) * B(-0x10000_z) == B(0x7fff0000_z));
	REQUIRE(B(-0x7fff_z) * B(-0xffff_z) == B(0x7ffe8001_z));
	REQUIRE(B(-0x7fff_z) * B(-0x8001_z) == B(0x3fffffff_z));
	REQUIRE(B(-0x7fff_z) * B(-0x8000_z) == B(0x3fff8000_z));
	REQUIRE(B(-0x7fff_z) * B(-0x7fff_z) == B(0x3fff0001_z));
	REQUIRE(B(-0x7fff_z) * B(0x7fff_z) == B(-0x3fff0001_z));
	REQUIRE(B(-0x7fff_z) * B(0x8000_z) == B(-0x3fff8000_z));
	REQUIRE(B(-0x7fff_z) * B(0x8001_z) == B(-0x3fffffff_z));
	REQUIRE(B(-0x7fff_z) * B(0xffff_z) == B(-0x7ffe8001_z));
	REQUIRE(B(-0x7fff_z) * B(0x10000_z) == B(-0x7fff0000_z));
	REQUIRE(B(-0x7fff_z) * B(0x10001_z) == B(-0x7fff7fff_z));
	REQUIRE(B(-0x7fff_z) * B(0x7fffffff_z) == B(-0x3fff7fff8001_z));
	REQUIRE(B(-0x7fff_z) * B(0x80000000_z) == B(-0x3fff80000000_z));
	REQUIRE(B(-0x7fff_z) * B(0x80000001_z) == B(-0x3fff80007fff_z));
	REQUIRE(B(-0x7fff_z) * B(0xffffffff_z) == B(-0x7ffeffff8001_z));
	REQUIRE(B(-0x7fff_z) * B(0x100000000_z) == B(-0x7fff00000000_z));
	REQUIRE(B(-0x7fff_z) * B(0x100000001_z) == B(-0x7fff00007fff_z));
	REQUIRE(B(0x7fff_z) * B(-0x100000001_z) == B(-0x7fff00007fff_z));
	REQUIRE(B(0x7fff_z) * B(-0x100000000_z) == B(-0x7fff00000000_z));
	REQUIRE(B(0x7fff_z) * B(-0xffffffff_z) == B(-0x7ffeffff8001_z));
	REQUIRE(B(0x7fff_z) * B(-0x80000001_z) == B(-0x3fff80007fff_z));
	REQUIRE(B(0x7fff_z) * B(-0x80000000_z) == B(-0x3fff80000000_z));
	REQUIRE(B(0x7fff_z) * B(-0x7fffffff_z) == B(-0x3fff7fff8001_z));
	REQUIRE(B(0x7fff_z) * B(-0x10001_z) == B(-0x7fff7fff_z));
	REQUIRE(B(0x7fff_z) * B(-0x10000_z) == B(-0x7fff0000_z));
	REQUIRE(B(0x7fff_z) * B(-0xffff_z) == B(-0x7ffe8001_z));
	REQUIRE(B(0x7fff_z) * B(-0x8001_z) == B(-0x3fffffff_z));
	REQUIRE(B(0x7fff_z) * B(-0x8000_z) == B(-0x3fff8000_z));
	REQUIRE(B(0x7fff_z) * B(-0x7fff_z) == B(-0x3fff0001_z));
	REQUIRE(B(0x7fff_z) * B(0x7fff_z) == B(0x3fff0001_z));
	REQUIRE(B(0x7fff_z) * B(0x8000_z) == B(0x3fff8000_z));
	REQUIRE(B(0x7fff_z) * B(0x8001_z) == B(0x3fffffff_z));
	REQUIRE(B(0x7fff_z) * B(0xffff_z) == B(0x7ffe8001_z));
	REQUIRE(B(0x7fff_z) * B(0x10000_z) == B(0x7fff0000_z));
	REQUIRE(B(0x7fff_z) * B(0x10001_z) == B(0x7fff7fff_z));
	REQUIRE(B(0x7fff_z) * B(0x7fffffff_z) == B(0x3fff7fff8001_z));
	REQUIRE(B(0x7fff_z) * B(0x80000000_z) == B(0x3fff80000000_z));
	REQUIRE(B(0x7fff_z) * B(0x80000001_z) == B(0x3fff80007fff_z));
	REQUIRE(B(0x7fff_z) * B(0xffffffff_z) == B(0x7ffeffff8001_z));
	REQUIRE(B(0x7fff_z) * B(0x100000000_z) == B(0x7fff00000000_z));
	REQUIRE(B(0x7fff_z) * B(0x100000001_z) == B(0x7fff00007fff_z));
	REQUIRE(B(0x8000_z) * B(-0x100000001_z) == B(-0x800000008000_z));
	REQUIRE(B(0x8000_z) * B(-0x100000000_z) == B(-0x800000000000_z));
	REQUIRE(B(0x8000_z) * B(-0xffffffff_z) == B(-0x7fffffff8000_z));
	REQUIRE(B(0x8000_z) * B(-0x80000001_z) == B(-0x400000008000_z));
	REQUIRE(B(0x8000_z) * B(-0x80000000_z) == B(-0x400000000000_z));
	REQUIRE(B(0x8000_z) * B(-0x7fffffff_z) == B(-0x3fffffff8000_z));
	REQUIRE(B(0x8000_z) * B(-0x10001_z) == B(-0x80008000_z));
	REQUIRE(B(0x8000_z) * B(-0x10000_z) == B(-0x80000000_z));
	REQUIRE(B(0x8000_z) * B(-0xffff_z) == B(-0x7fff8000_z));
	REQUIRE(B(0x8000_z) * B(-0x8001_z) == B(-0x40008000_z));
	REQUIRE(B(0x8000_z) * B(-0x8000_z) == B(-0x40000000_z));
	REQUIRE(B(0x8000_z) * B(-0x7fff_z) == B(-0x3fff8000_z));
	REQUIRE(B(0x8000_z) * B(0x7fff_z) == B(0x3fff8000_z));
	REQUIRE(B(0x8000_z) * B(0x8000_z) == B(0x40000000_z));
	REQUIRE(B(0x8000_z) * B(0x8001_z) == B(0x40008000_z));
	REQUIRE(B(0x8000_z) * B(0xffff_z) == B(0x7fff8000_z));
	REQUIRE(B(0x8000_z) * B(0x10000_z) == B(0x80000000_z));
	REQUIRE(B(0x8000_z) * B(0x10001_z) == B(0x80008000_z));
	REQUIRE(B(0x8000_z) * B(0x7fffffff_z) == B(0x3fffffff8000_z));
	REQUIRE(B(0x8000_z) * B(0x80000000_z) == B(0x400000000000_z));
	REQUIRE(B(0x8000_z) * B(0x80000001_z) == B(0x400000008000_z));
	REQUIRE(B(0x8000_z) * B(0xffffffff_z) == B(0x7fffffff8000_z));
	REQUIRE(B(0x8000_z) * B(0x100000000_z) == B(0x800000000000_z));
	REQUIRE(B(0x8000_z) * B(0x100000001_z) == B(0x800000008000_z));
	REQUIRE(B(0x8001_z) * B(-0x100000001_z) == B(-0x800100008001_z));
	REQUIRE(B(0x8001_z) * B(-0x100000000_z) == B(-0x800100000000_z));
	REQUIRE(B(0x8001_z) * B(-0xffffffff_z) == B(-0x8000ffff7fff_z));
	REQUIRE(B(0x8001_z) * B(-0x80000001_z) == B(-0x400080008001_z));
	REQUIRE(B(0x8001_z) * B(-0x80000000_z) == B(-0x400080000000_z));
	REQUIRE(B(0x8001_z) * B(-0x7fffffff_z) == B(-0x40007fff7fff_z));
	REQUIRE(B(0x8001_z) * B(-0x10001_z) == B(-0x80018001_z));
	REQUIRE(B(0x8001_z) * B(-0x10000_z) == B(-0x80010000_z));
	REQUIRE(B(0x8001_z) * B(-0xffff_z) == B(-0x80007fff_z));
	REQUIRE(B(0x8001_z) * B(-0x8001_z) == B(-0x40010001_z));
	REQUIRE(B(0x8001_z) * B(-0x8000_z) == B(-0x40008000_z));
	REQUIRE(B(0x8001_z) * B(-0x7fff_z) == B(-0x3fffffff_z));
	REQUIRE(B(0x8001_z) * B(0x7fff_z) == B(0x3fffffff_z));
	REQUIRE(B(0x8001_z) * B(0x8000_z) == B(0x40008000_z));
	REQUIRE(B(0x8001_z) * B(0x8001_z) == B(0x40010001_z));
	REQUIRE(B(0x8001_z) * B(0xffff_z) == B(0x80007fff_z));
	REQUIRE(B(0x8001_z) * B(0x10000_z) == B(0x80010000_z));
	REQUIRE(B(0x8001_z) * B(0x10001_z) == B(0x80018001_z));
	REQUIRE(B(0x8001_z) * B(0x7fffffff_z) == B(0x40007fff7fff_z));
	REQUIRE(B(0x8001_z) * B(0x80000000_z) == B(0x400080000000_z));
	REQUIRE(B(0x8001_z) * B(0x80000001_z) == B(0x400080008001_z));
	REQUIRE(B(0x8001_z) * B(0xffffffff_z) == B(0x8000ffff7fff_z));
	REQUIRE(B(0x8001_z) * B(0x100000000_z) == B(0x800100000000_z));
	REQUIRE(B(0x8001_z) * B(0x100000001_z) == B(0x800100008001_z));
	REQUIRE(B(0xffff_z) * B(-0x100000001_z) == B(-0xffff0000ffff_z));
	REQUIRE(B(0xffff_z) * B(-0x100000000_z) == B(-0xffff00000000_z));
	REQUIRE(B(0xffff_z) * B(-0xffffffff_z) == B(-0xfffeffff0001_z));
	REQUIRE(B(0xffff_z) * B(-0x80000001_z) == B(-0x7fff8000ffff_z));
	REQUIRE(B(0xffff_z) * B(-0x80000000_z) == B(-0x7fff80000000_z));
	REQUIRE(B(0xffff_z) * B(-0x7fffffff_z) == B(-0x7fff7fff0001_z));
	REQUIRE(B(0xffff_z) * B(-0x10001_z) == B(-0xffffffff_z));
	REQUIRE(B(0xffff_z) * B(-0x10000_z) == B(-0xffff0000_z));
	REQUIRE(B(0xffff_z) * B(-0xffff_z) == B(-0xfffe0001_z));
	REQUIRE(B(0xffff_z) * B(-0x8001_z) == B(-0x80007fff_z));
	REQUIRE(B(0xffff_z) * B(-0x8000_z) == B(-0x7fff8000_z));
	REQUIRE(B(0xffff_z) * B(-0x7fff_z) == B(-0x7ffe8001_z));
	REQUIRE(B(0xffff_z) * B(0x7fff_z) == B(0x7ffe8001_z));
	REQUIRE(B(0xffff_z) * B(0x8000_z) == B(0x7fff8000_z));
	REQUIRE(B(0xffff_z) * B(0x8001_z) == B(0x80007fff_z));
	REQUIRE(B(0xffff_z) * B(0xffff_z) == B(0xfffe0001_z));
	REQUIRE(B(0xffff_z) * B(0x10000_z) == B(0xffff0000_z));
	REQUIRE(B(0xffff_z) * B(0x10001_z) == B(0xffffffff_z));
	REQUIRE(B(0xffff_z) * B(0x7fffffff_z) == B(0x7fff7fff0001_z));
	REQUIRE(B(0xffff_z) * B(0x80000000_z) == B(0x7fff80000000_z));
	REQUIRE(B(0xffff_z) * B(0x80000001_z) == B(0x7fff8000ffff_z));
	REQUIRE(B(0xffff_z) * B(0xffffffff_z) == B(0xfffeffff0001_z));
	REQUIRE(B(0xffff_z) * B(0x100000000_z) == B(0xffff00000000_z));
	REQUIRE(B(0xffff_z) * B(0x100000001_z) == B(0xffff0000ffff_z));
	REQUIRE(B(0x10000_z) * B(-0x100000001_z) == B(-0x1000000010000_z));
	REQUIRE(B(0x10000_z) * B(-0x100000000_z) == B(-0x1000000000000_z));
	REQUIRE(B(0x10000_z) * B(-0xffffffff_z) == B(-0xffffffff0000_z));
	REQUIRE(B(0x10000_z) * B(-0x80000001_z) == B(-0x800000010000_z));
	REQUIRE(B(0x10000_z) * B(-0x80000000_z) == B(-0x800000000000_z));
	REQUIRE(B(0x10000_z) * B(-0x7fffffff_z) == B(-0x7fffffff0000_z));
	REQUIRE(B(0x10000_z) * B(-0x10001_z) == B(-0x100010000_z));
	REQUIRE(B(0x10000_z) * B(-0x10000_z) == B(-0x100000000_z));
	REQUIRE(B(0x10000_z) * B(-0xffff_z) == B(-0xffff0000_z));
	REQUIRE(B(0x10000_z) * B(-0x8001_z) == B(-0x80010000_z));
	REQUIRE(B(0x10000_z) * B(-0x8000_z) == B(-0x80000000_z));
	REQUIRE(B(0x10000_z) * B(-0x7fff_z) == B(-0x7fff0000_z));
	REQUIRE(B(0x10000_z) * B(0x7fff_z) == B(0x7fff0000_z));
	REQUIRE(B(0x10000_z) * B(0x8000_z) == B(0x80000000_z));
	REQUIRE(B(0x10000_z) * B(0x8001_z) == B(0x80010000_z));
	REQUIRE(B(0x10000_z) * B(0xffff_z) == B(0xffff0000_z));
	REQUIRE(B(0x10000_z) * B(0x10000_z) == B(0x100000000_z));
	REQUIRE(B(0x10000_z) * B(0x10001_z) == B(0x100010000_z));
	REQUIRE(B(0x10000_z) * B(0x7fffffff_z) == B(0x7fffffff0000_z));
	REQUIRE(B(0x10000_z) * B(0x80000000_z) == B(0x800000000000_z));
	REQUIRE(B(0x10000_z) * B(0x80000001_z) == B(0x800000010000_z));
	REQUIRE(B(0x10000_z) * B(0xffffffff_z) == B(0xffffffff0000_z));
	REQUIRE(B(0x10000_z) * B(0x100000000_z) == B(0x1000000000000_z));
	REQUIRE(B(0x10000_z) * B(0x100000001_z) == B(0x1000000010000_z));
	REQUIRE(B(0x10001_z) * B(-0x100000001_z) == B(-0x1000100010001_z));
	REQUIRE(B(0x10001_z) * B(-0x100000000_z) == B(-0x1000100000000_z));
	REQUIRE(B(0x10001_z) * B(-0xffffffff_z) == B(-0x10000fffeffff_z));
	REQUIRE(B(0x10001_z) * B(-0x80000001_z) == B(-0x800080010001_z));
	REQUIRE(B(0x10001_z) * B(-0x80000000_z) == B(-0x800080000000_z));
	REQUIRE(B(0x10001_z) * B(-0x7fffffff_z) == B(-0x80007ffeffff_z));
	REQUIRE(B(0x10001_z) * B(-0x10001_z) == B(-0x100020001_z));
	REQUIRE(B(0x10001_z) * B(-0x10000_z) == B(-0x100010000_z));
	REQUIRE(B(0x10001_z) * B(-0xffff_z) == B(-0xffffffff_z));
	REQUIRE(B(0x10001_z) * B(-0x8001_z) == B(-0x80018001_z));
	REQUIRE(B(0x10001_z) * B(-0x8000_z) == B(-0x80008000_z));
	REQUIRE(B(0x10001_z) * B(-0x7fff_z) == B(-0x7fff7fff_z));
	REQUIRE(B(0x10001_z) * B(0x7fff_z) == B(0x7fff7fff_z));
	REQUIRE(B(0x10001_z) * B(0x8000_z) == B(0x80008000_z));
	REQUIRE(B(0x10001_z) * B(0x8001_z) == B(0x80018001_z));
	REQUIRE(B(0x10001_z) * B(0xffff_z) == B(0xffffffff_z));
	REQUIRE(B(0x10001_z) * B(0x10000_z) == B(0x100010000_z));
	REQUIRE(B(0x10001_z) * B(0x10001_z) == B(0x100020001_z));
	REQUIRE(B(0x10001_z) * B(0x7fffffff_z) == B(0x80007ffeffff_z));
	REQUIRE(B(0x10001_z) * B(0x80000000_z) == B(0x800080000000_z));
	REQUIRE(B(0x10001_z) * B(0x80000001_z) == B(0x800080010001_z));
	REQUIRE(B(0x10001_z) * B(0xffffffff_z) == B(0x10000fffeffff_z));
	REQUIRE(B(0x10001_z) * B(0x100000000_z) == B(0x1000100000000_z));
	REQUIRE(B(0x10001_z) * B(0x100000001_z) == B(0x1000100010001_z));
	REQUIRE(B(0x7fffffff_z) * B(-0x100000001_z) == B(-0x7fffffff7fffffff_z));
	REQUIRE(B(0x7fffffff_z) * B(-0x100000000_z) == B(-0x7fffffff00000000_z));
	REQUIRE(B(0x7fffffff_z) * B(-0xffffffff_z) == B(-0x7ffffffe80000001_z));
	REQUIRE(B(0x7fffffff_z) * B(-0x80000001_z) == B(-0x3fffffffffffffff_z));
	REQUIRE(B(0x7fffffff_z) * B(-0x80000000_z) == B(-0x3fffffff80000000_z));
	REQUIRE(B(0x7fffffff_z) * B(-0x7fffffff_z) == B(-0x3fffffff00000001_z));
	REQUIRE(B(0x7fffffff_z) * B(-0x10001_z) == B(-0x80007ffeffff_z));
	REQUIRE(B(0x7fffffff_z) * B(-0x10000_z) == B(-0x7fffffff0000_z));
	REQUIRE(B(0x7fffffff_z) * B(-0xffff_z) == B(-0x7fff7fff0001_z));
	REQUIRE(B(0x7fffffff_z) * B(-0x8001_z) == B(-0x40007fff7fff_z));
	REQUIRE(B(0x7fffffff_z) * B(-0x8000_z) == B(-0x3fffffff8000_z));
	REQUIRE(B(0x7fffffff_z) * B(-0x7fff_z) == B(-0x3fff7fff8001_z));
	REQUIRE(B(0x7fffffff_z) * B(0x7fff_z) == B(0x3fff7fff8001_z));
	REQUIRE(B(0x7fffffff_z) * B(0x8000_z) == B(0x3fffffff8000_z));
	REQUIRE(B(0x7fffffff_z) * B(0x8001_z) == B(0x40007fff7fff_z));
	REQUIRE(B(0x7fffffff_z) * B(0xffff_z) == B(0x7fff7fff0001_z));
	REQUIRE(B(0x7fffffff_z) * B(0x10000_z) == B(0x7fffffff0000_z));
	REQUIRE(B(0x7fffffff_z) * B(0x10001_z) == B(0x80007ffeffff_z));
	REQUIRE(B(0x7fffffff_z) * B(0x7fffffff_z) == B(0x3fffffff00000001_z));
	REQUIRE(B(0x7fffffff_z) * B(0x80000000_z) == B(0x3fffffff80000000_z));
	REQUIRE(B(0x7fffffff_z) * B(0x80000001_z) == B(0x3fffffffffffffff_z));
	REQUIRE(B(0x7fffffff_z) * B(0xffffffff_z) == B(0x7ffffffe80000001_z));
	REQUIRE(B(0x7fffffff_z) * B(0x100000000_z) == B(0x7fffffff00000000_z));
	REQUIRE(B(0x7fffffff_z) * B(0x100000001_z) == B(0x7fffffff7fffffff_z));
	REQUIRE(B(0x80000000_z) * B(-0x100000001_z) == B(-0x8000000080000000_z));
	REQUIRE(B(0x80000000_z) * B(-0x100000000_z) == B(-0x8000000000000000_z));
	REQUIRE(B(0x80000000_z) * B(-0xffffffff_z) == B(-0x7fffffff80000000_z));
	REQUIRE(B(0x80000000_z) * B(-0x80000001_z) == B(-0x4000000080000000_z));
	REQUIRE(B(0x80000000_z) * B(-0x80000000_z) == B(-0x4000000000000000_z));
	REQUIRE(B(0x80000000_z) * B(-0x7fffffff_z) == B(-0x3fffffff80000000_z));
	REQUIRE(B(0x80000000_z) * B(-0x10001_z) == B(-0x800080000000_z));
	REQUIRE(B(0x80000000_z) * B(-0x10000_z) == B(-0x800000000000_z));
	REQUIRE(B(0x80000000_z) * B(-0xffff_z) == B(-0x7fff80000000_z));
	REQUIRE(B(0x80000000_z) * B(-0x8001_z) == B(-0x400080000000_z));
	REQUIRE(B(0x80000000_z) * B(-0x8000_z) == B(-0x400000000000_z));
	REQUIRE(B(0x80000000_z) * B(-0x7fff_z) == B(-0x3fff80000000_z));
	REQUIRE(B(0x80000000_z) * B(0x7fff_z) == B(0x3fff80000000_z));
	REQUIRE(B(0x80000000_z) * B(0x8000_z) == B(0x400000000000_z));
	REQUIRE(B(0x80000000_z) * B(0x8001_z) == B(0x400080000000_z));
	REQUIRE(B(0x80000000_z) * B(0xffff_z) == B(0x7fff80000000_z));
	REQUIRE(B(0x80000000_z) * B(0x10000_z) == B(0x800000000000_z));
	REQUIRE(B(0x80000000_z) * B(0x10001_z) == B(0x800080000000_z));
	REQUIRE(B(0x80000000_z) * B(0x7fffffff_z) == B(0x3fffffff80000000_z));
	REQUIRE(B(0x80000000_z) * B(0x80000000_z) == B(0x4000000000000000_z));
	REQUIRE(B(0x80000000_z) * B(0x80000001_z) == B(0x4000000080000000_z));
	REQUIRE(B(0x80000000_z) * B(0xffffffff_z) == B(0x7fffffff80000000_z));
	REQUIRE(B(0x80000000_z) * B(0x100000000_z) == B(0x8000000000000000_z));
	REQUIRE(B(0x80000000_z) * B(0x100000001_z) == B(0x8000000080000000_z));
	REQUIRE(B(0x80000001_z) * B(-0x100000001_z) == B(-0x8000000180000001_z));
	REQUIRE(B(0x80000001_z) * B(-0x100000000_z) == B(-0x8000000100000000_z));
	REQUIRE(B(0x80000001_z) * B(-0xffffffff_z) == B(-0x800000007fffffff_z));
	REQUIRE(B(0x80000001_z) * B(-0x80000001_z) == B(-0x4000000100000001_z));
	REQUIRE(B(0x80000001_z) * B(-0x80000000_z) == B(-0x4000000080000000_z));
	REQUIRE(B(0x80000001_z) * B(-0x7fffffff_z) == B(-0x3fffffffffffffff_z));
	REQUIRE(B(0x80000001_z) * B(-0x10001_z) == B(-0x800080010001_z));
	REQUIRE(B(0x80000001_z) * B(-0x10000_z) == B(-0x800000010000_z));
	REQUIRE(B(0x80000001_z) * B(-0xffff_z) == B(-0x7fff8000ffff_z));
	REQUIRE(B(0x80000001_z) * B(-0x8001_z) == B(-0x400080008001_z));
	REQUIRE(B(0x80000001_z) * B(-0x8000_z) == B(-0x400000008000_z));
	REQUIRE(B(0x80000001_z) * B(-0x7fff_z) == B(-0x3fff80007fff_z));
	REQUIRE(B(0x80000001_z) * B(0x7fff_z) == B(0x3fff80007fff_z));
	REQUIRE(B(0x80000001_z) * B(0x8000_z) == B(0x400000008000_z));
	REQUIRE(B(0x80000001_z) * B(0x8001_z) == B(0x400080008001_z));
	REQUIRE(B(0x80000001_z) * B(0xffff_z) == B(0x7fff8000ffff_z));
	REQUIRE(B(0x80000001_z) * B(0x10000_z) == B(0x800000010000_z));
	REQUIRE(B(0x80000001_z) * B(0x10001_z) == B(0x800080010001_z));
	REQUIRE(B(0x80000001_z) * B(0x7fffffff_z) == B(0x3fffffffffffffff_z));
	REQUIRE(B(0x80000001_z) * B(0x80000000_z) == B(0x4000000080000000_z));
	REQUIRE(B(0x80000001_z) * B(0x80000001_z) == B(0x4000000100000001_z));
	REQUIRE(B(0x80000001_z) * B(0xffffffff_z) == B(0x800000007fffffff_z));
	REQUIRE(B(0x80000001_z) * B(0x100000000_z) == B(0x8000000100000000_z));
	REQUIRE(B(0x80000001_z) * B(0x100000001_z) == B(0x8000000180000001_z));
	REQUIRE(B(0xffffffff_z) * B(-0x100000001_z) == B(-0xffffffffffffffff_z));
	REQUIRE(B(0xffffffff_z) * B(-0x100000000_z) == B(-0xffffffff00000000_z));
	REQUIRE(B(0xffffffff_z) * B(-0xffffffff_z) == B(-0xfffffffe00000001_z));
	REQUIRE(B(0xffffffff_z) * B(-0x80000001_z) == B(-0x800000007fffffff_z));
	REQUIRE(B(0xffffffff_z) * B(-0x80000000_z) == B(-0x7fffffff80000000_z));
	REQUIRE(B(0xffffffff_z) * B(-0x7fffffff_z) == B(-0x7ffffffe80000001_z));
	REQUIRE(B(0xffffffff_z) * B(-0x10001_z) == B(-0x10000fffeffff_z));
	REQUIRE(B(0xffffffff_z) * B(-0x10000_z) == B(-0xffffffff0000_z));
	REQUIRE(B(0xffffffff_z) * B(-0xffff_z) == B(-0xfffeffff0001_z));
	REQUIRE(B(0xffffffff_z) * B(-0x8001_z) == B(-0x8000ffff7fff_z));
	REQUIRE(B(0xffffffff_z) * B(-0x8000_z) == B(-0x7fffffff8000_z));
	REQUIRE(B(0xffffffff_z) * B(-0x7fff_z) == B(-0x7ffeffff8001_z));
	REQUIRE(B(0xffffffff_z) * B(0x7fff_z) == B(0x7ffeffff8001_z));
	REQUIRE(B(0xffffffff_z) * B(0x8000_z) == B(0x7fffffff8000_z));
	REQUIRE(B(0xffffffff_z) * B(0x8001_z) == B(0x8000ffff7fff_z));
	REQUIRE(B(0xffffffff_z) * B(0xffff_z) == B(0xfffeffff0001_z));
	REQUIRE(B(0xffffffff_z) * B(0x10000_z) == B(0xffffffff0000_z));
	REQUIRE(B(0xffffffff_z) * B(0x10001_z) == B(0x10000fffeffff_z));
	REQUIRE(B(0xffffffff_z) * B(0x7fffffff_z) == B(0x7ffffffe80000001_z));
	REQUIRE(B(0xffffffff_z) * B(0x80000000_z) == B(0x7fffffff80000000_z));
	REQUIRE(B(0xffffffff_z) * B(0x80000001_z) == B(0x800000007fffffff_z));
	REQUIRE(B(0xffffffff_z) * B(0xffffffff_z) == B(0xfffffffe00000001_z));
	REQUIRE(B(0xffffffff_z) * B(0x100000000_z) == B(0xffffffff00000000_z));
	REQUIRE(B(0xffffffff_z) * B(0x100000001_z) == B(0xffffffffffffffff_z));
	REQUIRE(B(0x100000000_z) * B(-0x100000001_z) == B(-0x10000000100000000_z));
	REQUIRE(B(0x100000000_z) * B(-0x100000000_z) == B(-0x10000000000000000_z));
	REQUIRE(B(0x100000000_z) * B(-0xffffffff_z) == B(-0xffffffff00000000_z));
	REQUIRE(B(0x100000000_z) * B(-0x80000001_z) == B(-0x8000000100000000_z));
	REQUIRE(B(0x100000000_z) * B(-0x80000000_z) == B(-0x8000000000000000_z));
	REQUIRE(B(0x100000000_z) * B(-0x7fffffff_z) == B(-0x7fffffff00000000_z));
	REQUIRE(B(0x100000000_z) * B(-0x10001_z) == B(-0x1000100000000_z));
	REQUIRE(B(0x100000000_z) * B(-0x10000_z) == B(-0x1000000000000_z));
	REQUIRE(B(0x100000000_z) * B(-0xffff_z) == B(-0xffff00000000_z));
	REQUIRE(B(0x100000000_z) * B(-0x8001_z) == B(-0x800100000000_z));
	REQUIRE(B(0x100000000_z) * B(-0x8000_z) == B(-0x800000000000_z));
	REQUIRE(B(0x100000000_z) * B(-0x7fff_z) == B(-0x7fff00000000_z));
	REQUIRE(B(0x100000000_z) * B(0x7fff_z) == B(0x7fff00000000_z));
	REQUIRE(B(0x100000000_z) * B(0x8000_z) == B(0x800000000000_z));
	REQUIRE(B(0x100000000_z) * B(0x8001_z) == B(0x800100000000_z));
	REQUIRE(B(0x100000000_z) * B(0xffff_z) == B(0xffff00000000_z));
	REQUIRE(B(0x100000000_z) * B(0x10000_z) == B(0x1000000000000_z));
	REQUIRE(B(0x100000000_z) * B(0x10001_z) == B(0x1000100000000_z));
	REQUIRE(B(0x100000000_z) * B(0x7fffffff_z) == B(0x7fffffff00000000_z));
	REQUIRE(B(0x100000000_z) * B(0x80000000_z) == B(0x8000000000000000_z));
	REQUIRE(B(0x100000000_z) * B(0x80000001_z) == B(0x8000000100000000_z));
	REQUIRE(B(0x100000000_z) * B(0xffffffff_z) == B(0xffffffff00000000_z));
	REQUIRE(B(0x100000000_z) * B(0x100000000_z) == B(0x10000000000000000_z));
	REQUIRE(B(0x100000000_z) * B(0x100000001_z) == B(0x10000000100000000_z));
	REQUIRE(B(0x100000001_z) * B(-0x100000001_z) == B(-0x10000000200000001_z));
	REQUIRE(B(0x100000001_z) * B(-0x100000000_z) == B(-0x10000000100000000_z));
	REQUIRE(B(0x100000001_z) * B(-0xffffffff_z) == B(-0xffffffffffffffff_z));
	REQUIRE(B(0x100000001_z) * B(-0x80000001_z) == B(-0x8000000180000001_z));
	REQUIRE(B(0x100000001_z) * B(-0x80000000_z) == B(-0x8000000080000000_z));
	REQUIRE(B(0x100000001_z) * B(-0x7fffffff_z) == B(-0x7fffffff7fffffff_z));
	REQUIRE(B(0x100000001_z) * B(-0x10001_z) == B(-0x1000100010001_z));
	REQUIRE(B(0x100000001_z) * B(-0x10000_z) == B(-0x1000000010000_z));
	REQUIRE(B(0x100000001_z) * B(-0xffff_z) == B(-0xffff0000ffff_z));
	REQUIRE(B(0x100000001_z) * B(-0x8001_z) == B(-0x800100008001_z));
	REQUIRE(B(0x100000001_z) * B(-0x8000_z) == B(-0x800000008000_z));
	REQUIRE(B(0x100000001_z) * B(-0x7fff_z) == B(-0x7fff00007fff_z));
	REQUIRE(B(0x100000001_z) * B(0x7fff_z) == B(0x7fff00007fff_z));
	REQUIRE(B(0x100000001_z) * B(0x8000_z) == B(0x800000008000_z));
	REQUIRE(B(0x100000001_z) * B(0x8001_z) == B(0x800100008001_z));
	REQUIRE(B(0x100000001_z) * B(0xffff_z) == B(0xffff0000ffff_z));
	REQUIRE(B(0x100000001_z) * B(0x10000_z) == B(0x1000000010000_z));
	REQUIRE(B(0x100000001_z) * B(0x10001_z) == B(0x1000100010001_z));
	REQUIRE(B(0x100000001_z) * B(0x7fffffff_z) == B(0x7fffffff7fffffff_z));
	REQUIRE(B(0x100000001_z) * B(0x80000000_z) == B(0x8000000080000000_z));
	REQUIRE(B(0x100000001_z) * B(0x80000001_z) == B(0x8000000180000001_z));
	REQUIRE(B(0x100000001_z) * B(0xffffffff_z) == B(0xffffffffffffffff_z));
	REQUIRE(B(0x100000001_z) * B(0x100000000_z) == B(0x10000000100000000_z));
	REQUIRE(B(0x100000001_z) * B(0x100000001_z) == B(0x10000000200000001_z));
}
