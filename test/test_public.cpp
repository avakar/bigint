#include <avakar/bigint.h>
#include <avakar/intn.h>

#include "catch.hpp"

using B = avakar::bigint;

TEST_CASE("intn: public")
{
	using namespace avakar;

#define CC(v) { uint128_t x = v; REQUIRE(x == v); }
#define CCE(v) { uint128_t x{v}; REQUIRE(x == uint128_t(v)); }

	CCE(-1_z);
	CC(0_z);
	CC(1_z);

#undef CC

}
