#include "../src/intn/intn.h"
#include "../src/generic_traits.h"
#include <avakar/bigint.h>
#include "catch.hpp"

using avakar::_intn::intn;
using II = intn<64, true, avakar::_bigint::generic_traits<uint16_t, uint32_t>>;
using UU = intn<64, false, avakar::_bigint::generic_traits<uint16_t, uint32_t>>;
using avakar::operator""_z;

template <typename T>
static T implicit(T const & v)
{
	return v;
}

#define I(v) (implicit<II>(v ## _z))
#define U(v) (implicit<UU>(v ## _z))

TEST_CASE("intn: default")
{
	REQUIRE(II{} == 0_z);
	REQUIRE_FALSE(II{} != 0_z);
	REQUIRE_FALSE(II{} == 1_z);
	REQUIRE(II{} != 1_z);
}

TEST_CASE("intn: signed vs unsigned")
{
	REQUIRE(II(-1_z) < 0);
}

TEST_CASE("intn: signed addition")
{
	REQUIRE(I(-1) + I(-1) == I(-2));
	REQUIRE(I(0) + I(-1) == I(-1));
	REQUIRE(I(-1) + I(0) == I(-1));

	REQUIRE(I(0) + I(0) == I(0));
	REQUIRE(I(0) + I(1) == I(1));
	REQUIRE(I(1) + I(0) == I(1));
	REQUIRE(I(1) + I(1) == I(2));

	REQUIRE(I(0x7fff) + I(-1) == I(0x7ffe));
	REQUIRE(I(0x7fff) + I( 1) == I(0x8000));
	REQUIRE(I(0x7fff) + I( 2) == I(0x8001));
	REQUIRE(I(0x8000) + I(-1) == I(0x7fff));
	REQUIRE(I(0x8000) + I( 1) == I(0x8001));
	REQUIRE(I(0x8000) + I( 2) == I(0x8002));
	REQUIRE(I(0x8001) + I(-1) == I(0x8000));
	REQUIRE(I(0x8001) + I(-2) == I(0x7fff));

	REQUIRE(I(0x0ffff) + I(-1) == I(0x0fffe));
	REQUIRE(I(0x0ffff) + I( 0) == I(0x0ffff));
	REQUIRE(I(0x0ffff) + I( 1) == I(0x10000));
	REQUIRE(I(0x0ffff) + I( 2) == I(0x10001));

	REQUIRE(I(0x10000) + I(-1) == I(0x0ffff));
	REQUIRE(I(0x10000) + I( 0) == I(0x10000));
	REQUIRE(I(0x10000) + I( 1) == I(0x10001));
	REQUIRE(I(0x10001) + I(-2) == I(0x0ffff));
	REQUIRE(I(0x10001) + I(-1) == I(0x10000));

	REQUIRE(I(0x7fffffffffffffff) + I(-1) == I( 0x7ffffffffffffffe));
	REQUIRE(I(0x7fffffffffffffff) + I( 0) == I( 0x7fffffffffffffff));
	REQUIRE(I(0x7fffffffffffffff) + I( 1) == I(-0x8000000000000000));
	REQUIRE(I(0x7fffffffffffffff) + I( 2) == I(-0x7fffffffffffffff));
}
