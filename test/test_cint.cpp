#include "../src/cint/digits.h"
#include "../src/cint/fwd.h"
#include "../src/cint/prepend.h"
#include "../src/cint/trim.h"
#include "../src/cint/complement.h"
#include "../src/cint/add.h"
#include "../src/cint/mul.h"
#include "../src/cint/bitwise.h"
#include "../src/cint/shift.h"
#include "../src/cint/strtoc.h"
#include "../src/cint/cint.h"
#include "../src/cint/make.h"
#include "../src/cint/digitize.h"

#include "catch.hpp"

using D = avakar::_cint::digit_t;

template <D d0, D... dn>
using C = avakar::_cint::cint<d0, dn...>;

struct R
{
	R(D hi, D lo)
		: _hi(hi), _lo(lo)
	{
	}

	operator std::pair<D, D>() const
	{
		return { _hi, _lo };
	}

	friend bool operator==(R const & lhs, R const & rhs)
	{
		return lhs._hi == rhs._hi && lhs._lo == rhs._lo;
	}

	D _hi;
	D _lo;
};

TEST_CASE("cint small digit operations")
{
	using avakar::_cint::sext;
	REQUIRE(sext(0) == 0);
	REQUIRE(sext(1) == 0);
	REQUIRE(sext(0x7fffffff) == 0);
	REQUIRE(sext(0x80000000) == 0xffffffff);
	REQUIRE(sext(0xffffffff) == 0xffffffff);

	using avakar::_cint::neg_digit;
	REQUIRE(neg_digit(0) == 0);
	REQUIRE(neg_digit(1) == 0xffffffff);
	REQUIRE(neg_digit(0x7fffffff) == 0x80000001);
	REQUIRE(neg_digit(0x80000000) == 0x80000000);
	REQUIRE(neg_digit(0x80000001) == 0x7fffffff);
	REQUIRE(neg_digit(0xffffffff) == 1);

#define A(a, b, c) R{ avakar::_cint::add_digits<a, b, c>::hi, avakar::_cint::add_digits<a, b, c>::lo }
#define M(a, b, c) R{ avakar::_cint::mul_digits<a, b, c>::hi, avakar::_cint::mul_digits<a, b, c>::lo }

	REQUIRE(A(0, 0, 0) == R{ 0, 0 });
	REQUIRE(A(1, 1, 1) == R{ 0, 3 });
	REQUIRE(A(0xff, 1, 1) == R{ 0, 0x101 });
	
	REQUIRE(A(0xffffffff, 0x00000000, 0) == R{ 0, 0xffffffff });
	REQUIRE(A(0xffffffff, 0x00000001, 0) == R{ 1, 0x00000000 });
	REQUIRE(A(0xffffffff, 0x00000001, 1) == R{ 1, 0x00000001 });
	REQUIRE(A(0xffffffff, 0xffffffff, 1) == R{ 1, 0xffffffff });

	REQUIRE(A(0xffffffff, 0xffffffff, 0xffffffff) == R{ 2, 0xfffffffd });

	REQUIRE(M(0, 0, 0) == R{ 0, 0 });
	REQUIRE(M(1, 1, 0) == R{ 0, 1 });
	REQUIRE(M(1, 1, 0xffffffff) == R{ 1, 0 });

	REQUIRE(M(0xffffffff, 1, 0) == R{ 0, 0xffffffff });
	REQUIRE(M(0xffffffff, 1, 1) == R{ 1, 0x00000000 });
	REQUIRE(M(0xffffffff, 1, 2) == R{ 1, 0x00000001 });

	REQUIRE(M(0xffffffff, 2, 0) == R{ 1, 0xfffffffe });
	REQUIRE(M(0xffffffff, 2, 1) == R{ 1, 0xffffffff });
	REQUIRE(M(0xffffffff, 2, 2) == R{ 2, 0x00000000 });
	REQUIRE(M(0xffffffff, 2, 3) == R{ 2, 0x00000001 });

	REQUIRE(M(0xffffffff, 0xffffffff, 0) == R{ 0xfffffffe, 0x00000001 });
	REQUIRE(M(0xffffffff, 0xffffffff, 1) == R{ 0xfffffffe, 0x00000002 });
	REQUIRE(M(0xffffffff, 0xffffffff, 0xffffffff) == R{ 0xffffffff, 0x00000000 });
}


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
	TT(trim_t<C<0xffffffff>>, C<0xffffffff>);

	TT(trim_t<C<0, 0>>, C<0>);
	TT(trim_t<C<1, 0>>, C<1>);
	TT(trim_t<C<0x7fffffff, 0>>, C<0x7fffffff>);
	TT(trim_t<C<0x80000000, 0>>, C<0x80000000, 0>);
	TT(trim_t<C<0xffffffff, 0>>, C<0xffffffff, 0>);

	TT(trim_t<C<0, 0, 0>>, C<0>);
	TT(trim_t<C<1, 0, 0>>, C<1>);
	TT(trim_t<C<0x7fffffff, 0, 0>>, C<0x7fffffff>);
	TT(trim_t<C<0x80000000, 0, 0>>, C<0x80000000, 0>);
	TT(trim_t<C<0xffffffff, 0, 0>>, C<0xffffffff, 0>);

	TT(trim_t<C<0, 0xffffffff>>, C<0, 0xffffffff>);
	TT(trim_t<C<1, 0xffffffff>>, C<1, 0xffffffff>);
	TT(trim_t<C<0x7fffffff, 0xffffffff>>, C<0x7fffffff, 0xffffffff>);
	TT(trim_t<C<0x80000000, 0xffffffff>>, C<0x80000000>);
	TT(trim_t<C<0xffffffff, 0xffffffff>>, C<0xffffffff>);

	TT(trim_t<C<0, 0xffffffff, 0xffffffff>>, C<0, 0xffffffff>);
	TT(trim_t<C<1, 0xffffffff, 0xffffffff>>, C<1, 0xffffffff>);
	TT(trim_t<C<0x7fffffff, 0xffffffff, 0xffffffff>>, C<0x7fffffff, 0xffffffff>);
	TT(trim_t<C<0x80000000, 0xffffffff, 0xffffffff>>, C<0x80000000>);
	TT(trim_t<C<0xffffffff, 0xffffffff, 0xffffffff>>, C<0xffffffff>);

	TT(trim_t<C<0, 0, 0xffffffff>>, C<0, 0, 0xffffffff>);
	TT(trim_t<C<0, 0xffffffff, 0xffffffff>>, C<0, 0xffffffff>);
}

TEST_CASE("cint: complement")
{
	using avakar::_cint::com_t;

	TT(com_t<C<0>>, C<0xffffffff>);
	TT(com_t<C<0, 0>>, C<0xffffffff>);
	TT(com_t<C<1>>, C<0xfffffffe>);
	TT(com_t<C<0x80000000, 0, 0>>, C<0x7fffffff, 0xffffffff>);

	TT(com_t<C<0xffffffff>>, C<0>);
}

TEST_CASE("cint: add")
{
	using avakar::_cint::add_t;

	TT(add_t<C<1>, C<2>>, C<3>);
	TT(add_t<C<1, 0>, C<2>>, C<3>);

	TT(add_t<C<1, 0, 0>, C<2>>, C<3>);
	TT(add_t<C<1, 2, 0>, C<1>>, C<2, 2>);

	TT(add_t<C<1, 2, 0>, C<1, 1>>, C<2, 3>);

	TT(add_t<C<0xffffffff>, C<1>>, C<0>);
	TT(add_t<C<0xffffffff, 0xffffffff>, C<1>>, C<0>);

	TT(add_t<C<0xffffffff>, C<0xffffffff>>, C<0xfffffffe>);

	TT(add_t<C<0xffffffff, 0>, C<0xffffffff>>, C<0xfffffffe, 0>);
}

TEST_CASE("cint: mul")
{
	using avakar::_cint::mul_t;

	TT(mul_t<C<0>, C<0>>, C<0>);
	TT(mul_t<C<1>, C<0>>, C<0>);
	TT(mul_t<C<0>, C<1>>, C<0>);
	TT(mul_t<C<0xffffffff>, C<0>>, C<0>);
	TT(mul_t<C<0>, C<0xffffffff>>, C<0>);

	TT(mul_t<C<1>, C<1>>, C<1>);
	TT(mul_t<C<0xffffffff>, C<1>>, C<0xffffffff>);
	TT(mul_t<C<1>, C<0xffffffff>>, C<0xffffffff>);
	TT(mul_t<C<0xffffffff>, C<0xffffffff>>, C<1>);

	TT(mul_t<C<2>, C<1>>, C<2>);
	TT(mul_t<C<0xffffffff>, C<2>>, C<0xfffffffe>);
	TT(mul_t<C<2>, C<0xffffffff>>, C<0xfffffffe>);
	TT(mul_t<C<0xfffffffe>, C<0xffffffff>>, C<2>);

	TT(mul_t<C<0, 1>, C<1>>, C<0, 1>);
	TT(mul_t<C<0, 1>, C<2>>, C<0, 2>);
	TT(mul_t<C<1, 1>, C<1>>, C<1, 1>);
	TT(mul_t<C<1, 1>, C<2>>, C<2, 2>);
	TT(mul_t<C<0x80000000, 1>, C<1>>, C<0x80000000, 1>);
	TT(mul_t<C<0x80000000, 1>, C<2>>, C<0, 3>);

	TT(mul_t<C<0, 0xffffffff>, C<1>>, C<0, 0xffffffff>);
	TT(mul_t<C<0, 1>, C<2>>, C<0, 2>);
	TT(mul_t<C<1, 1>, C<1>>, C<1, 1>);
	TT(mul_t<C<1, 1>, C<2>>, C<2, 2>);
	TT(mul_t<C<0x80000000, 1>, C<1>>, C<0x80000000, 1>);
	TT(mul_t<C<0x80000000, 1>, C<2>>, C<0, 3>);

	TT(mul_t<C<0, 1>, C<0, 1>>, C<0, 0, 1>);
	TT(mul_t<C<0, 1>, C<0, 0xffffffff>>, C<0, 0, 0xffffffff>);

	TT(mul_t<C<0x7fffffff>, C<0x7fffffff>>, C<1, 0x3fffffff>);
	TT(mul_t<C<0xffffffff, 0x7fffffff>, C<0xffffffff, 0x7fffffff>>, C<1, 0, 0xffffffff, 0x3fffffff>);
}

TEST_CASE("cint: bitwise")
{
	using avakar::_cint::bitwise_and_t;
	using avakar::_cint::bitwise_or_t;
	using avakar::_cint::bitwise_xor_t;

	TT(bitwise_and_t<C<0>, C<0>>, C<0>);
	TT(bitwise_and_t<C<1>, C<0>>, C<0>);
	TT(bitwise_and_t<C<1>, C<1>>, C<1>);
	TT(bitwise_and_t<C<0xffffffff>, C<1>>, C<1>);
	TT(bitwise_and_t<C<0xffffffff>, C<0xffffffff, 0>>, C<0xffffffff, 0>);
	TT(bitwise_and_t<C<0xffffffff, 0>, C<0xffffffff, 0>>, C<0xffffffff, 0>);
	TT(bitwise_and_t<C<0xaaaaaaaa, 0x55555555>, C<0x55555555, 0xaaaaaaaa>>, C<0>);

	TT(bitwise_or_t<C<0>, C<0>>, C<0>);
	TT(bitwise_or_t<C<1>, C<0>>, C<1>);
	TT(bitwise_or_t<C<1>, C<1>>, C<1>);
	TT(bitwise_or_t<C<0xffffffff>, C<1>>, C<0xffffffff>);
	TT(bitwise_or_t<C<0xffffffff>, C<0xffffffff, 0>>, C<0xffffffff>);
	TT(bitwise_or_t<C<0xffffffff, 0>, C<0xffffffff, 0>>, C<0xffffffff, 0>);
	TT(bitwise_or_t<C<0xaaaaaaaa, 0x55555555>, C<0x55555555, 0xaaaaaaaa>>, C<0xffffffff>);

	TT(bitwise_xor_t<C<0>, C<0>>, C<0>);
	TT(bitwise_xor_t<C<1>, C<0>>, C<1>);
	TT(bitwise_xor_t<C<1>, C<1>>, C<0>);
	TT(bitwise_xor_t<C<0xffffffff>, C<1>>, C<0xfffffffe>);
	TT(bitwise_xor_t<C<0xffffffff>, C<0xffffffff, 0>>, C<0, 0xffffffff>);
	TT(bitwise_xor_t<C<0xffffffff, 0>, C<0xffffffff, 0>>, C<0>);
	TT(bitwise_xor_t<C<0xaaaaaaaa, 0x55555555>, C<0x55555555, 0xaaaaaaaa>>, C<0xffffffff>);
	TT(bitwise_xor_t<C<0xaaaaaaaa, 0x55555555>, C<0x55555555, 0xaaaaaaaa, 0>>, C<0xffffffff, 0xffffffff, 0>);
}

TEST_CASE("cint: shift")
{
	using avakar::_cint::shift_left_t;
	using avakar::_cint::shift_right_t;

	TT(shift_left_t<C<0>, C<0>>, C<0>);
	TT(shift_left_t<C<1>, C<0>>, C<1>);
	TT(shift_left_t<C<0x100>, C<1>>, C<0x200>);
	TT(shift_left_t<C<0x100>, C<25>>, C<0, 2>);
	TT(shift_left_t<C<0x100>, C<32>>, C<0, 0x100>);
	TT(shift_left_t<C<0x100>, C<100>>, C<0, 0, 0, 0x1000>);

	TT(shift_left_t<C<0x100>, C<0xffffffff>>, C<0x80>);
	TT(shift_left_t<C<0x100>, C<0xffffff0f>>, C<0>);
	TT(shift_left_t<C<0x100>, C<0x80000000>>, C<0>);

	TT(shift_left_t<C<0, 1>, C<0>>, C<0, 1>);
	TT(shift_left_t<C<1, 1>, C<0>>, C<1, 1>);
	TT(shift_left_t<C<0x100, 1>, C<1>>, C<0x200, 2>);
	TT(shift_left_t<C<0x100, 1>, C<25>>, C<0, 0x02000002>);
	TT(shift_left_t<C<0x100, 1>, C<32>>, C<0, 0x100, 1>);
	TT(shift_left_t<C<0x100, 1>, C<100>>, C<0, 0, 0, 0x1000, 0x10>);

	TT(shift_left_t<C<0x100, 1>, C<0xffffffff>>, C<0x80000080, 0>);
	TT(shift_left_t<C<0x100, 1>, C<0xffffffe0>>, C<1>);
	TT(shift_left_t<C<0x100, 1>, C<0xffffff0f>>, C<0>);
	TT(shift_left_t<C<0x100, 1>, C<0x80000000>>, C<0>);

	TT(shift_left_t<C<0, 1, 1>, C<0>>, C<0, 1, 1>);
	TT(shift_left_t<C<1, 1, 1>, C<0>>, C<1, 1, 1>);
	TT(shift_left_t<C<0x100, 1, 1>, C<1>>, C<0x200, 2, 2>);
	TT(shift_left_t<C<0x100, 1, 1>, C<25>>, C<0, 0x02000002, 0x02000000>);
	TT(shift_left_t<C<0x100, 1, 1>, C<32>>, C<0, 0x100, 1, 1>);
	TT(shift_left_t<C<0x100, 1, 1>, C<100>>, C<0, 0, 0, 0x1000, 0x10, 0x10>);

	TT(shift_left_t<C<0x100, 1, 1>, C<0xffffffff>>, C<0x80000080, 0x80000000, 0>);
	TT(shift_left_t<C<0x100, 1, 1>, C<0xffffffe0>>, C<1, 1>);
	TT(shift_left_t<C<0x100, 1, 1>, C<0xffffff0f>>, C<0>);
	TT(shift_left_t<C<0x100, 1, 1>, C<0x80000000>>, C<0>);

	TT(shift_right_t<C<0x100>, C<1>>, C<0x80>);
	TT(shift_right_t<C<0x100>, C<0xf1>>, C<0>);
	TT(shift_right_t<C<0x100>, C<0x7fffffff>>, C<0>);

	TT(shift_right_t<C<0, 0x100>, C<1>>, C<0, 0x80>);
}

template <char... cn>
using P = avakar::_cint::parse_literal_t<cn...>;

TEST_CASE("cint: strtoc")
{
	TT(P<'0'>, C<0>);
	TT(P<'1'>, C<1>);
	TT(P<'9'>, C<9>);
	TT(P<'1', '0'>, C<10>);
	TT(P<'1', '1'>, C<11>);
	TT(P<'1', '2'>, C<12>);
	TT(P<'3', '2', '7', '6', '7'>, C<0x7fff>);
	TT(P<'3', '2', '7', '6', '8'>, C<0x8000>);
	TT(P<'6', '5', '5', '3', '5'>, C<0xffff>);
	TT(P<'6', '5', '5', '3', '6'>, C<0x10000>);

	TT(P<'2', '1', '4', '7', '4', '8', '3', '6', '4', '7'>, C<0x7fffffff>);
	TT(P<'2', '1', '4', '7', '4', '8', '3', '6', '4', '8'>, C<0x80000000, 0>);
	TT(P<'2', '1', '4', '7', '4', '8', '3', '6', '4', '9'>, C<0x80000001, 0>);

	TT(P<'4', '2', '9', '4', '9', '6', '7', '2', '9', '5'>, C<0xffffffff, 0>);
	TT(P<'4', '2', '9', '4', '9', '6', '7', '2', '9', '6'>, C<0x00000000, 1>);

	TT(P<'0', '1', '2'>, C<10>);
	TT(P<'0', 'x', '1', '2'>, C<0x12>);
	TT(P<'0', 'x', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f'>, C<0xffffffff, 0>);
	TT(P<'0', 'x', '0', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f'>, C<0xffffffff, 0>);
	TT(P<'0', 'x', '1', '0', '0', '0', '0', '0', '0', '0', '0'>, C<0x00000000, 1>);
}

#define V(...) (C<__VA_ARGS__>{})

TEST_CASE("cint: bool")
{
	REQUIRE(V(1));
	REQUIRE(V(1, 1));
	REQUIRE(V(1, 0));
	REQUIRE(V(0xffffffff));
	REQUIRE(V(0xffffffff));
	REQUIRE(V(0xffffffff, 0));
	REQUIRE_FALSE(V(0));
	REQUIRE_FALSE(V(0, 0));

	REQUIRE_FALSE(!V(1));
	REQUIRE_FALSE(!V(1, 1));
	REQUIRE_FALSE(!V(1, 0));
	REQUIRE_FALSE(!V(0xffffffff));
	REQUIRE_FALSE(!V(0xffffffff));
	REQUIRE_FALSE(!V(0xffffffff, 0));
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
	REQUIRE(V(0xffffffff) < V(0));

	REQUIRE(V(1) > V(0));
	REQUIRE_FALSE(V(0) > V(0));
	REQUIRE_FALSE(V(0xffffffff) > V(0));

	REQUIRE(V(1) >= V(0));
	REQUIRE(V(0) >= V(0));
	REQUIRE_FALSE(V(0xffffffff) >= V(0));

	REQUIRE_FALSE(V(1) <= V(0));
	REQUIRE(V(0) <= V(0));
	REQUIRE(V(0xffffffff) <= V(0));

	REQUIRE(+V(1, 0) == V(1));

	REQUIRE(-V(0) == V(0));
	REQUIRE(-V(1) == V(0xffffffff));

	REQUIRE(V(1) + V(2) == V(3));

	REQUIRE(~V(0) == V(0xffffffff));
	REQUIRE(~V(0xffffffff) == V(0));
	REQUIRE(~V(0x80000000) == V(0x7fffffff));

	REQUIRE((V(1) << V(5)) == V(32));
	REQUIRE((V(1) >> V(0)) == V(1));
	REQUIRE((V(1) >> V(1)) == V(0));
	REQUIRE((V(1) >> V(2)) == V(0));


	REQUIRE((V(0x55) & V(0x5a)) == V(0x50));
	REQUIRE((V(0x55) | V(0x5a)) == V(0x5f));
	REQUIRE((V(0x55) ^ V(0x5a)) == V(0x0f));
}

template <typename T, T v>
using M = avakar::_cint::make_t<T, v>;

TEST_CASE("cint: make")
{
	TT(M<uint32_t, 0>, C<0>);
	TT(M<uint32_t, 1>, C<1>);
	TT(M<uint32_t, 0x7fffffff>, C<0x7fffffff>);
	TT(M<uint32_t, 0x80000000>, C<0x80000000, 0>);
	TT(M<uint32_t, 0xffffffff>, C<0xffffffff, 0>);
	TT(M<uint64_t, 0x100000000>, C<0, 1>);
	TT(M<uint64_t, 0x7fffffff00000000>, C<0, 0x7fffffff>);
	TT(M<uint64_t, 0x8000000000000000>, C<0, 0x80000000, 0>);
	TT(M<uint64_t, 0xffffffffffffffff>, C<0xffffffff, 0xffffffff, 0>);


	TT(M<int32_t, 0>, C<0>);
	TT(M<int32_t, 1>, C<1>);
	TT(M<int32_t, 0x7fffffff>, C<0x7fffffff>);
	TT(M<int64_t, 0x80000000>, C<0x80000000, 0>);
	TT(M<int64_t, 0xffffffff>, C<0xffffffff, 0>);
	TT(M<int64_t, 0x100000000>, C<0, 1>);
	TT(M<int64_t, 0x7fffffffffffffff>, C<0xffffffff, 0x7fffffff>);

	TT(M<int64_t, -1>, C<0xffffffff>);
	TT(M<int64_t, -0x7fffffff>, C<0x80000001>);
	TT(M<int64_t, -0x80000000ll>, C<0x80000000>);
	TT(M<int64_t, -0x80000001ll>, C<0x7fffffff, 0xffffffff>);
	TT(M<int64_t, -0x7fffffffffffffffll>, C<0x00000001, 0x80000000>);
}

TEST_CASE("cint: operator _z")
{
	using avakar::_cint::operator""_z;

	REQUIRE(0_z + 0_z == 0_z);
	REQUIRE(1_z * -2_z == -2_z);
}

template <uint16_t... dn>
using S16 = avakar::_cint::digit_sequence<uint16_t, dn...>;

template <uint32_t... dn>
using S32 = avakar::_cint::digit_sequence<uint32_t, dn...>;

template <uint64_t... dn>
using S64 = avakar::_cint::digit_sequence<uint64_t, dn...>;

TEST_CASE("cint: digitize")
{
	using avakar::_cint::digitize_t;

	TT(digitize_t<uint16_t, C<0>>, S16<0>);
	TT(digitize_t<uint16_t, C<1>>, S16<1>);
	TT(digitize_t<uint16_t, C<0x7fff>>, S16<0x7fff>);
	TT(digitize_t<uint16_t, C<0x8000>>, S16<0x8000, 0>);
	TT(digitize_t<uint16_t, C<0x8001>>, S16<0x8001, 0>);
	TT(digitize_t<uint16_t, C<0xffff>>, S16<0xffff, 0>);
	TT(digitize_t<uint16_t, C<0x10000>>, S16<0x0000, 1>);
	TT(digitize_t<uint16_t, C<0x17fff>>, S16<0x7fff, 1>);
	TT(digitize_t<uint16_t, C<0x18000>>, S16<0x8000, 1>);
	TT(digitize_t<uint16_t, C<0x1ffff>>, S16<0xffff, 1>);
	TT(digitize_t<uint16_t, C<0x20000>>, S16<0x0000, 2>);
	TT(digitize_t<uint16_t, C<0x7fffffff>>, S16<0xffff, 0x7fff>);
	TT(digitize_t<uint16_t, C<0x80000000, 0>>, S16<0x0000, 0x8000, 0>);
	TT(digitize_t<uint16_t, C<0x80000001, 0>>, S16<0x0001, 0x8000, 0>);
	TT(digitize_t<uint16_t, C<0xffffffff, 0>>, S16<0xffff, 0xffff, 0>);
	TT(digitize_t<uint16_t, C<0x00000000, 1>>, S16<0x0000, 0x0000, 1>);

	TT(digitize_t<uint16_t, C<0xffffffff>>, S16<0xffff>);
	TT(digitize_t<uint16_t, C<0xfffffffe>>, S16<0xfffe>);
	TT(digitize_t<uint16_t, C<0xffff8000>>, S16<0x8000>);
	TT(digitize_t<uint16_t, C<0xffff7fff>>, S16<0x7fff, 0xffff>);
	TT(digitize_t<uint16_t, C<0xfffeffff>>, S16<0xffff, 0xfffe>);
	TT(digitize_t<uint16_t, C<0x80000000>>, S16<0x0000, 0x8000>);
	TT(digitize_t<uint16_t, C<0x7fffffff, 0xffffffff>>, S16<0xffff, 0x7fff, 0xffff>);

	TT(digitize_t<uint32_t, C<0>>, S32<0>);
	TT(digitize_t<uint32_t, C<1>>, S32<1>);
	TT(digitize_t<uint32_t, C<0x7fffffff>>, S32<0x7fffffff>);
	TT(digitize_t<uint32_t, C<0x80000000, 0>>, S32<0x80000000, 0>);
	TT(digitize_t<uint32_t, C<0x80000001, 0>>, S32<0x80000001, 0>);
	TT(digitize_t<uint32_t, C<0xffffffff, 0>>, S32<0xffffffff, 0>);
	TT(digitize_t<uint32_t, C<0x00000000, 1>>, S32<0x00000000, 1>);

	TT(digitize_t<uint32_t, C<0xffffffff>>, S32<0xffffffff>);
	TT(digitize_t<uint32_t, C<0xfffffffe>>, S32<0xfffffffe>);
	TT(digitize_t<uint32_t, C<0x80000000>>, S32<0x80000000>);
	TT(digitize_t<uint32_t, C<0x7fffffff, 0xffffffff>>, S32<0x7fffffff, 0xffffffff>);

	TT(digitize_t<uint64_t, C<0>>, S64<0>);
	TT(digitize_t<uint64_t, C<1>>, S64<1>);
	TT(digitize_t<uint64_t, C<0x7fffffff>>, S64<0x7fffffff>);
	TT(digitize_t<uint64_t, C<0x80000000, 0>>, S64<0x80000000>);
	TT(digitize_t<uint64_t, C<0x80000001, 0>>, S64<0x80000001>);
	TT(digitize_t<uint64_t, C<0xffffffff, 0>>, S64<0xffffffff>);
	TT(digitize_t<uint64_t, C<0x00000000, 1>>, S64<0x100000000>);

	TT(digitize_t<uint64_t, C<0xffffffff>>, S64<0xffffffffffffffff>);
	TT(digitize_t<uint64_t, C<0xfffffffe>>, S64<0xfffffffffffffffe>);
	TT(digitize_t<uint64_t, C<0x80000000>>, S64<0xffffffff80000000>);
	TT(digitize_t<uint64_t, C<0x7fffffff, 0xffffffff>>, S64<0xffffffff7fffffff>);
	TT(digitize_t<uint64_t, C<0x00000000, 0x80000000>>, S64<0x8000000000000000>);
	TT(digitize_t<uint64_t, C<0xffffffff, 0x7fffffff, 0xffffffff>>, S64<0x7fffffffffffffff, 0xffffffffffffffff>);
}

enum E : int16_t { e1, e2, e3 };
enum class F : int16_t { e1, e2, e3 };

TEST_CASE("cint: convert")
{
	using avakar::_cint::operator""_z;

#define CC(type, value) { type _v = value ## _z; REQUIRE(_v == (type)value); }
#define CCE(type, value) { type _v = (type)value ## _z; REQUIRE(_v == (type)value); }

	CCE(uint8_t, -0x10001);
	CCE(uint8_t, -0x10000);
	CCE(uint8_t, -0xffff);
	CCE(uint8_t, -0xfffe);
	CCE(uint8_t, -0x8001);
	CCE(uint8_t, -0x8000);
	CCE(uint8_t, -0x7fff);
	CCE(uint8_t, -0x7ffe);
	CCE(uint8_t, -2);
	CCE(uint8_t, -1);
	CC(uint8_t, 0);
	CC(uint8_t, 1);
	CC(uint8_t, 0x00ff);
	CCE(uint8_t, 0x0100);
	CCE(uint8_t, 0x0101);
	CCE(uint8_t, 0x7fff);
	CCE(uint8_t, 0x8000);
	CCE(uint8_t, 0x8001);
	CCE(uint8_t, 0xfffe);
	CCE(uint8_t, 0xffff);
	CCE(uint8_t, 0x10000);
	CCE(uint8_t, 0x10001);
	CCE(uint8_t, 0x1ffff);
	CCE(uint8_t, 0x20000);
	CCE(uint8_t, 0x7fffffff);
	CCE(uint8_t, 0x80000000);
	CCE(uint8_t, 0x80000001);

	CCE(uint16_t, -0x10001);
	CCE(uint16_t, -0x10000);
	CCE(uint16_t, -0xffff);
	CCE(uint16_t, -0xfffe);
	CCE(uint16_t, -0x8001);
	CCE(uint16_t, -0x8000);
	CCE(uint16_t, -0x7fff);
	CCE(uint16_t, -0x7ffe);
	CCE(uint16_t, -2);
	CCE(uint16_t, -1);
	CC(uint16_t, 0);
	CC(uint16_t, 1);
	CC(uint16_t, 0x00ff);
	CC(uint16_t, 0x0100);
	CC(uint16_t, 0x0101);
	CC(uint16_t, 0x7fff);
	CC(uint16_t, 0x8000);
	CC(uint16_t, 0x8001);
	CC(uint16_t, 0xfffe);
	CC(uint16_t, 0xffff);
	CCE(uint16_t, 0x10000);
	CCE(uint16_t, 0x10001);
	CCE(uint16_t, 0x1ffff);
	CCE(uint16_t, 0x20000);
	CCE(uint16_t, 0x7fffffff);
	CCE(uint16_t, 0x80000000);
	CCE(uint16_t, 0x80000001);

	CCE(int16_t, -0x10001);
	CCE(int16_t, -0x10000);
	CCE(int16_t, -0xffff);
	CCE(int16_t, -0xfffe);
	CCE(int16_t, -0x8001);
	CC(int16_t, -0x8000);
	CC(int16_t, -0x7fff);
	CC(int16_t, -0x7ffe);
	CC(int16_t, -2);
	CC(int16_t, -1);
	CC(int16_t, 0);
	CC(int16_t, 1);
	CC(int16_t, 0x00ff);
	CC(int16_t, 0x0100);
	CC(int16_t, 0x0101);
	CC(int16_t, 0x7fff);
	CCE(int16_t, 0x8000);
	CCE(int16_t, 0x8001);
	CCE(int16_t, 0xfffe);
	CCE(int16_t, 0xffff);
	CCE(int16_t, 0x10000);
	CCE(int16_t, 0x10001);
	CCE(int16_t, 0x1ffff);
	CCE(int16_t, 0x20000);
	CCE(int16_t, 0x7fffffff);
	CCE(int16_t, 0x80000000);
	CCE(int16_t, 0x80000001);

	CCE(int8_t, -0x10001);
	CCE(int8_t, -0x10000);
	CCE(int8_t, -0xffff);
	CCE(int8_t, -0xfffe);
	CCE(int8_t, -0x8001);
	CCE(int8_t, -0x8000);
	CCE(int8_t, -0x7fff);
	CCE(int8_t, -0x7ffe);
	CC(int8_t, -2);
	CC(int8_t, -1);
	CC(int8_t, 0);
	CC(int8_t, 1);
	CCE(int8_t, 0x00ff);
	CCE(int8_t, 0x0100);
	CCE(int8_t, 0x0101);
	CCE(int8_t, 0x7fff);
	CCE(int8_t, 0x8000);
	CCE(int8_t, 0x8001);
	CCE(int8_t, 0xfffe);
	CCE(int8_t, 0xffff);
	CCE(int8_t, 0x10000);
	CCE(int8_t, 0x10001);
	CCE(int8_t, 0x1ffff);
	CCE(int8_t, 0x20000);
	CCE(int8_t, 0x7fffffff);
	CCE(int8_t, 0x80000000);
	CCE(int8_t, 0x80000001);

	CC(E, -1);
	CC(E, 0);
	CC(E, 0x7fff);
	CCE(E, 0x8000);

	CCE(F, -1);
	CCE(F, 0);
	CCE(F, 0x7fff);
	CCE(F, 0x8000);
}
