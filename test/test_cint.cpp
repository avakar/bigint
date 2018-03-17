#include "../src/cint/digits.h"
#include "../src/cint/shift.h"
#include "../src/cint/prepend.h"
#include "../src/cint/trim.h"
#include "../src/cint/compare.h"
#include "../src/cint/complement.h"
#include "../src/cint/add.h"
#include "../src/cint/cint.h"
#include "../src/cint/strtoc.h"
#include "../src/cint/make.h"

#include "catch.hpp"

struct R
{
	R(uint16_t hi, uint16_t lo)
		: _hi(hi), _lo(lo)
	{
	}

	operator std::pair<uint16_t, uint16_t>() const
	{
		return { _hi, _lo };
	}

	friend bool operator==(R const & lhs, R const & rhs)
	{
		return lhs._hi == rhs._hi && lhs._lo == rhs._lo;
	}

	uint16_t _hi;
	uint16_t _lo;
};

TEST_CASE("cint small digit operations")
{
	using X = avakar::_cint::digits<uint16_t>;

#define A(a, b, c) R{ avakar::_cint::add_digits<uint16_t, a, b, c>::hi, avakar::_cint::add_digits<uint16_t, a, b, c>::lo }
#define M(a, b, c) R{ avakar::_cint::mul_digits<uint16_t, a, b, c>::hi, avakar::_cint::mul_digits<uint16_t, a, b, c>::lo }

	using avakar::_cint::sext;

	REQUIRE((X::min == 0));
	REQUIRE((X::max == 0xffff));
	REQUIRE((X::width == 16));
	REQUIRE((X::sign_mask == 0x8000));

	REQUIRE(sext<uint16_t>(0) == 0);
	REQUIRE(sext<uint16_t>(1) == 0);
	REQUIRE(sext<uint16_t>(0x7fff) == 0);
	REQUIRE(sext<uint16_t>(0x8000) == 0xffff);
	REQUIRE(sext<uint16_t>(0xffff) == 0xffff);

	REQUIRE(A(0, 0, 0) == R{ 0, 0 });
	REQUIRE(A(1, 1, 1) == R{ 0, 3 });
	REQUIRE(A(0xff, 1, 1) == R{ 0, 0x101 });
	
	REQUIRE(A(0xffff, 0x0000, 0) == R{ 0, 0xffff });
	REQUIRE(A(0xffff, 0x0001, 0) == R{ 1, 0x0000 });
	REQUIRE(A(0xffff, 0x0001, 1) == R{ 1, 0x0001 });
	REQUIRE(A(0xffff, 0xffff, 1) == R{ 1, 0xffff });

	REQUIRE(A(0xffff, 0xffff, 0xffff) == R{ 2, 0xfffd });

	REQUIRE(M(0, 0, 0) == R{ 0, 0 });
	REQUIRE(M(1, 1, 0) == R{ 0, 1 });
	REQUIRE(M(1, 1, 0xffff) == R{ 1, 0 });

	REQUIRE(M(0xffff, 1, 0) == R{ 0, 0xffff });
	REQUIRE(M(0xffff, 1, 1) == R{ 1, 0x0000 });
	REQUIRE(M(0xffff, 1, 2) == R{ 1, 0x0001 });

	REQUIRE(M(0xffff, 2, 0) == R{ 1, 0xfffe });
	REQUIRE(M(0xffff, 2, 1) == R{ 1, 0xffff });
	REQUIRE(M(0xffff, 2, 2) == R{ 2, 0x0000 });
	REQUIRE(M(0xffff, 2, 3) == R{ 2, 0x0001 });

	REQUIRE(M(0xffff, 0xffff, 0) == R{ 0xfffe, 0x0001 });
	REQUIRE(M(0xffff, 0xffff, 1) == R{ 0xfffe, 0x0002 });
	REQUIRE(M(0xffff, 0xffff, 0xffff) == R{ 0xffff, 0x0000 });
}

template <uint16_t d0, uint16_t... dn>
using C = avakar::_cint::cint<uint16_t, d0, dn...>;

#define TT(...) REQUIRE((std::is_same<__VA_ARGS__>::value));

TEST_CASE("prepend doesn't normalize")
{
	using avakar::_cint::prepend_t;

	TT(prepend_t<C<0>, 0>, C<0, 0>);
	TT(prepend_t<C<0>, 1>, C<1, 0>);
	TT(prepend_t<C<0>, 0x7fff>, C<0x7fff, 0>);
	TT(prepend_t<C<0>, 0x8000>, C<0x8000, 0>);
	TT(prepend_t<C<0>, 0xffff>, C<0xffff, 0>);

	TT(prepend_t<C<0xffff>, 0>, C<0, 0xffff>);
	TT(prepend_t<C<0xffff>, 1>, C<1, 0xffff>);
	TT(prepend_t<C<0xffff>, 0x7fff>, C<0x7fff, 0xffff>);
	TT(prepend_t<C<0xffff>, 0x8000>, C<0x8000, 0xffff>);
	TT(prepend_t<C<0xffff>, 0xffff>, C<0xffff, 0xffff>);

	TT(prepend_t<C<1, 2>, 0xffff>, C<0xffff, 1, 2>);
}

TEST_CASE("cint: trim")
{
	using avakar::_cint::trim_t;

	TT(trim_t<C<0>>, C<0>);
	TT(trim_t<C<0xffff>>, C<0xffff>);

	TT(trim_t<C<0, 0>>, C<0>);
	TT(trim_t<C<1, 0>>, C<1>);
	TT(trim_t<C<0x7fff, 0>>, C<0x7fff>);
	TT(trim_t<C<0x8000, 0>>, C<0x8000, 0>);
	TT(trim_t<C<0xffff, 0>>, C<0xffff, 0>);

	TT(trim_t<C<0, 0, 0>>, C<0>);
	TT(trim_t<C<1, 0, 0>>, C<1>);
	TT(trim_t<C<0x7fff, 0, 0>>, C<0x7fff>);
	TT(trim_t<C<0x8000, 0, 0>>, C<0x8000, 0>);
	TT(trim_t<C<0xffff, 0, 0>>, C<0xffff, 0>);

	TT(trim_t<C<0, 0xffff>>, C<0, 0xffff>);
	TT(trim_t<C<1, 0xffff>>, C<1, 0xffff>);
	TT(trim_t<C<0x7fff, 0xffff>>, C<0x7fff, 0xffff>);
	TT(trim_t<C<0x8000, 0xffff>>, C<0x8000>);
	TT(trim_t<C<0xffff, 0xffff>>, C<0xffff>);

	TT(trim_t<C<0, 0xffff, 0xffff>>, C<0, 0xffff>);
	TT(trim_t<C<1, 0xffff, 0xffff>>, C<1, 0xffff>);
	TT(trim_t<C<0x7fff, 0xffff, 0xffff>>, C<0x7fff, 0xffff>);
	TT(trim_t<C<0x8000, 0xffff, 0xffff>>, C<0x8000>);
	TT(trim_t<C<0xffff, 0xffff, 0xffff>>, C<0xffff>);

	TT(trim_t<C<0, 0, 0xffff>>, C<0, 0, 0xffff>);
	TT(trim_t<C<0, 0xffff, 0xffff>>, C<0, 0xffff>);
}

TEST_CASE("cint: complement")
{
	using avakar::_cint::com_t;

	TT(com_t<C<0>>, C<0xffff>);
	TT(com_t<C<0, 0>>, C<0xffff>);
	TT(com_t<C<1>>, C<0xfffe>);
	TT(com_t<C<0x8000, 0, 0>>, C<0x7fff, 0xffff>);

	TT(com_t<C<0xffff>>, C<0>);
}

TEST_CASE("cint: add")
{
	using avakar::_cint::add_t;

	TT(add_t<C<1>, C<2>>, C<3>);
	TT(add_t<C<1, 0>, C<2>>, C<3>);

	TT(add_t<C<1, 0, 0>, C<2>>, C<3>);
	TT(add_t<C<1, 2, 0>, C<1>>, C<2, 2>);

	TT(add_t<C<1, 2, 0>, C<1, 1>>, C<2, 3>);

	TT(add_t<C<0xffff>, C<1>>, C<0>);
	TT(add_t<C<0xffff, 0xffff>, C<1>>, C<0>);

	TT(add_t<C<0xffff>, C<0xffff>>, C<0xfffe>);

	TT(add_t<C<0xffff, 0>, C<0xffff>>, C<0xfffe, 0>);
}

TEST_CASE("cint: mul")
{
	using avakar::_cint::mul_t;

	TT(mul_t<C<0>, C<0>>, C<0>);
	TT(mul_t<C<1>, C<0>>, C<0>);
	TT(mul_t<C<0>, C<1>>, C<0>);
	TT(mul_t<C<0xffff>, C<0>>, C<0>);
	TT(mul_t<C<0>, C<0xffff>>, C<0>);

	TT(mul_t<C<1>, C<1>>, C<1>);
	TT(mul_t<C<0xffff>, C<1>>, C<0xffff>);
	TT(mul_t<C<1>, C<0xffff>>, C<0xffff>);
	TT(mul_t<C<0xffff>, C<0xffff>>, C<1>);

	TT(mul_t<C<2>, C<1>>, C<2>);
	TT(mul_t<C<0xffff>, C<2>>, C<0xfffe>);
	TT(mul_t<C<2>, C<0xffff>>, C<0xfffe>);
	TT(mul_t<C<0xfffe>, C<0xffff>>, C<2>);

	TT(mul_t<C<0, 1>, C<1>>, C<0, 1>);
	TT(mul_t<C<0, 1>, C<2>>, C<0, 2>);
	TT(mul_t<C<1, 1>, C<1>>, C<1, 1>);
	TT(mul_t<C<1, 1>, C<2>>, C<2, 2>);
	TT(mul_t<C<0x8000, 1>, C<1>>, C<0x8000, 1>);
	TT(mul_t<C<0x8000, 1>, C<2>>, C<0, 3>);

	TT(mul_t<C<0, 0xffff>, C<1>>, C<0, 0xffff>);
	TT(mul_t<C<0, 1>, C<2>>, C<0, 2>);
	TT(mul_t<C<1, 1>, C<1>>, C<1, 1>);
	TT(mul_t<C<1, 1>, C<2>>, C<2, 2>);
	TT(mul_t<C<0x8000, 1>, C<1>>, C<0x8000, 1>);
	TT(mul_t<C<0x8000, 1>, C<2>>, C<0, 3>);

	TT(mul_t<C<0, 1>, C<0, 1>>, C<0, 0, 1>);
	TT(mul_t<C<0, 1>, C<0, 0xffff>>, C<0, 0, 0xffff>);

	TT(mul_t<C<0x7fff>, C<0x7fff>>, C<1, 0x3fff>);
	TT(mul_t<C<0xffff, 0x7fff>, C<0xffff, 0x7fff>>, C<1, 0, 0xffff, 0x3fff>);
}

TEST_CASE("cint: bitwise")
{
	using avakar::_cint::bitwise_and_t;
	using avakar::_cint::bitwise_or_t;
	using avakar::_cint::bitwise_xor_t;

	TT(bitwise_and_t<C<0>, C<0>>, C<0>);
	TT(bitwise_and_t<C<1>, C<0>>, C<0>);
	TT(bitwise_and_t<C<1>, C<1>>, C<1>);
	TT(bitwise_and_t<C<0xffff>, C<1>>, C<1>);
	TT(bitwise_and_t<C<0xffff>, C<0xffff, 0>>, C<0xffff, 0>);
	TT(bitwise_and_t<C<0xffff, 0>, C<0xffff, 0>>, C<0xffff, 0>);
	TT(bitwise_and_t<C<0xaaaa, 0x5555>, C<0x5555, 0xaaaa>>, C<0>);

	TT(bitwise_or_t<C<0>, C<0>>, C<0>);
	TT(bitwise_or_t<C<1>, C<0>>, C<1>);
	TT(bitwise_or_t<C<1>, C<1>>, C<1>);
	TT(bitwise_or_t<C<0xffff>, C<1>>, C<0xffff>);
	TT(bitwise_or_t<C<0xffff>, C<0xffff, 0>>, C<0xffff>);
	TT(bitwise_or_t<C<0xffff, 0>, C<0xffff, 0>>, C<0xffff, 0>);
	TT(bitwise_or_t<C<0xaaaa, 0x5555>, C<0x5555, 0xaaaa>>, C<0xffff>);

	TT(bitwise_xor_t<C<0>, C<0>>, C<0>);
	TT(bitwise_xor_t<C<1>, C<0>>, C<1>);
	TT(bitwise_xor_t<C<1>, C<1>>, C<0>);
	TT(bitwise_xor_t<C<0xffff>, C<1>>, C<0xfffe>);
	TT(bitwise_xor_t<C<0xffff>, C<0xffff, 0>>, C<0, 0xffff>);
	TT(bitwise_xor_t<C<0xffff, 0>, C<0xffff, 0>>, C<0>);
	TT(bitwise_xor_t<C<0xaaaa, 0x5555>, C<0x5555, 0xaaaa>>, C<0xffff>);
	TT(bitwise_xor_t<C<0xaaaa, 0x5555>, C<0x5555, 0xaaaa, 0>>, C<0xffff, 0xffff, 0>);
}

TEST_CASE("cint: shift")
{
	using avakar::_cint::shift_left_t;
	using avakar::_cint::shift_right_t;

	TT(shift_left_t<C<0>, C<0>>, C<0>);
	TT(shift_left_t<C<1>, C<0>>, C<1>);
	TT(shift_left_t<C<0x100>, C<1>>, C<0x200>);
	TT(shift_left_t<C<0x100>, C<9>>, C<0, 2>);
	TT(shift_left_t<C<0x100>, C<16>>, C<0, 0x100>);
	TT(shift_left_t<C<0x100>, C<100>>, C<0, 0, 0, 0, 0, 0, 0x1000>);

	TT(shift_left_t<C<0x100>, C<0xffff>>, C<0x80>);
	TT(shift_left_t<C<0x100>, C<0xff0f>>, C<0>);
	TT(shift_left_t<C<0x100>, C<0x8000>>, C<0>);

	TT(shift_right_t<C<0x100>, C<1>>, C<0x80>);
	TT(shift_right_t<C<0x100>, C<0xf1>>, C<0>);
	TT(shift_right_t<C<0x100>, C<0x7fff>>, C<0>);

	TT(shift_right_t<C<0, 0x100>, C<1>>, C<0, 0x80>);
}

using avakar::_cint::parse_literal_t;

template <char... cn>
using P = parse_literal_t<uint16_t, cn...>;

TEST_CASE("cint: strtoc")
{
	TT(P<'0'>, C<0>);
	TT(P<'1'>, C<1>);
	TT(P<'9'>, C<9>);
	TT(P<'1', '0'>, C<10>);
	TT(P<'1', '1'>, C<11>);
	TT(P<'1', '2'>, C<12>);
	TT(P<'3', '2', '7', '6', '7'>, C<0x7fff>);
	TT(P<'3', '2', '7', '6', '8'>, C<0x8000, 0>);
	TT(P<'6', '5', '5', '3', '5'>, C<0xffff, 0>);
	TT(P<'6', '5', '5', '3', '6'>, C<0x0000, 1>);

	TT(P<'0', '1', '2'>, C<10>);
	TT(P<'0', 'x', '1', '2'>, C<0x12>);
	TT(P<'0', 'x', 'f', 'f', 'f', 'f'>, C<0xffff, 0>);
	TT(P<'0', 'x', '0', 'f', 'f', 'f', 'f'>, C<0xffff, 0>);
	TT(P<'0', 'x', '1', '0', '0', '0', '0'>, C<0x0000, 1>);
}

#define V(...) (C<__VA_ARGS__>{})

TEST_CASE("cint: bool")
{
	REQUIRE(V(1));
	REQUIRE(V(1, 1));
	REQUIRE(V(1, 0));
	REQUIRE(V(0xffff));
	REQUIRE(V(0xffff));
	REQUIRE(V(0xffff, 0));
	REQUIRE_FALSE(V(0));
	REQUIRE_FALSE(V(0, 0));

	REQUIRE_FALSE(!V(1));
	REQUIRE_FALSE(!V(1, 1));
	REQUIRE_FALSE(!V(1, 0));
	REQUIRE_FALSE(!V(0xffff));
	REQUIRE_FALSE(!V(0xffff));
	REQUIRE_FALSE(!V(0xffff, 0));
	REQUIRE(!V(0));
	REQUIRE(!V(0, 0));

	REQUIRE_FALSE((V(0) && V(0)));
	REQUIRE_FALSE((V(0) && V(1)));
	REQUIRE_FALSE((V(1) && V(0)));
	REQUIRE((V(1) && V(1)));

	REQUIRE_FALSE((V(0) || V(0)));
	REQUIRE((V(0) || V(1)));
	REQUIRE((V(1) || V(0)));
	REQUIRE((V(1) || V(1)));
}

TEST_CASE("cint: operators")
{
	REQUIRE(V(0) == V(0));
	REQUIRE(V(1) != V(0));

	REQUIRE_FALSE(V(0) < V(0));
	REQUIRE_FALSE(V(1) < V(0));
	REQUIRE(V(0xffff) < V(0));

	REQUIRE(V(1) > V(0));
	REQUIRE_FALSE(V(0) > V(0));
	REQUIRE_FALSE(V(0xffff) > V(0));

	REQUIRE(V(1) >= V(0));
	REQUIRE(V(0) >= V(0));
	REQUIRE_FALSE(V(0xffff) >= V(0));

	REQUIRE_FALSE(V(1) <= V(0));
	REQUIRE(V(0) <= V(0));
	REQUIRE(V(0xffff) <= V(0));

	REQUIRE(+V(1, 0) == V(1));

	REQUIRE(-V(0) == V(0));
	REQUIRE(-V(1) == V(0xffff));

	REQUIRE(V(1) + V(2) == V(3));

	REQUIRE(~V(0) == V(0xffff));
	REQUIRE(~V(0xffff) == V(0));
	REQUIRE(~V(0x8000) == V(0x7fff));

	REQUIRE((V(1) << V(5)) == V(32));
	REQUIRE((V(1) >> V(0)) == V(1));
	REQUIRE((V(1) >> V(1)) == V(0));
	REQUIRE((V(1) >> V(2)) == V(0));


	REQUIRE((V(0x55) & V(0x5a)) == V(0x50));
	REQUIRE((V(0x55) | V(0x5a)) == V(0x5f));
	REQUIRE((V(0x55) ^ V(0x5a)) == V(0x0f));
}

template <typename T, T v>
using M = avakar::_cint::make_t<uint16_t, T, v>;

TEST_CASE("cint: make")
{
	TT(M<uint32_t, 0>, C<0>);
	TT(M<uint32_t, 1>, C<1>);
	TT(M<uint32_t, 0x7fff>, C<0x7fff>);
	TT(M<uint32_t, 0x8000>, C<0x8000, 0>);
	TT(M<uint32_t, 0xffff>, C<0xffff, 0>);
	TT(M<uint32_t, 0x10000>, C<0, 1>);
	TT(M<uint32_t, 0x7fff0000>, C<0, 0x7fff>);
	TT(M<uint32_t, 0x80000000>, C<0, 0x8000, 0>);
	TT(M<uint32_t, 0xffffffff>, C<0xffff, 0xffff, 0>);


	TT(M<int32_t, 0>, C<0>);
	TT(M<int32_t, 1>, C<1>);
	TT(M<int32_t, 0x7fff>, C<0x7fff>);
	TT(M<int32_t, 0x8000>, C<0x8000, 0>);
	TT(M<int32_t, 0xffff>, C<0xffff, 0>);
	TT(M<int32_t, 0x10000>, C<0, 1>);
	TT(M<int32_t, 0x7fffffff>, C<0xffff, 0x7fff>);

	TT(M<int32_t, -1>, C<0xffff>);
	TT(M<int32_t, -0x7fff>, C<0x8001>);
	TT(M<int32_t, -0x8000>, C<0x8000>);
	TT(M<int32_t, -0x8001>, C<0x7fff, 0xffff>);
	TT(M<int32_t, -0x7fffffff>, C<0x0001, 0x8000>);
}
