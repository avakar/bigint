#ifndef AVAKAR_BIGINT_CINT_CINT_H
#define AVAKAR_BIGINT_CINT_CINT_H

#include "digitize.h"
#include "strtoc.h"
#include "compare.h"
#include "bitwise.h"
#include "shift.h"
#include "add.h"
#include "mul.h"
#include "fwd.h"

namespace avakar {
namespace _cint {

template <digit_t d0, digit_t... dn>
struct cint
{
	constexpr explicit operator bool() const
	{
		return !is_zero<cint>::value;
	}

	template <
		typename T,
		typename std::enable_if<convert<T, cint>::implicit, int>::type = 0>
	constexpr operator T() const
	{
		return convert<T, cint>::value;
	}

	template <
		typename T,
		typename std::enable_if<!convert<T, cint>::implicit, int>::type = 0>
	constexpr explicit operator T() const
	{
		return convert<T, cint>::value;
	}
};

template <typename A>
constexpr trim_t<A> operator+(A) { return {}; }

template <typename A>
constexpr neg_t<A> operator-(A) { return {}; }

template <typename A>
constexpr com_t<A> operator~(A) { return {}; }

template <typename A, typename B>
constexpr add_t<A, B> operator+(A, B) { return {}; }

template <typename A, typename B>
constexpr sub_t<A, B> operator-(A, B) { return {}; }

template <typename A, typename B>
constexpr mul_t<A, B> operator*(A, B) { return {}; }

template <typename A, typename B>
constexpr shift_left_t<A, B> operator<<(A, B) { return {}; }

template <typename A, typename B>
constexpr shift_right_t<A, B> operator>>(A, B) { return {}; }

template <typename A, typename B>
constexpr bitwise_and_t<A, B> operator&(A, B) { return {}; }

template <typename A, typename B>
constexpr bitwise_or_t<A, B> operator|(A, B) { return {}; }

template <typename A, typename B>
constexpr bitwise_xor_t<A, B> operator^(A, B) { return {}; }

template <digit_t... an, digit_t... bn>
constexpr bool operator==(cint<an...>, cint<bn...>) { return is_equal<cint<an...>, cint<bn...>>::value; }

template <digit_t... an, digit_t... bn>
constexpr bool operator!=(cint<an...>, cint<bn...>) { return !is_equal<cint<an...>, cint<bn...>>::value; }

template <digit_t... an, digit_t... bn>
constexpr bool operator<(cint<an...>, cint<bn...>) { return is_less<cint<an...>, cint<bn...>>::value; }

template <digit_t... an, digit_t... bn>
constexpr bool operator>(cint<an...>, cint<bn...>) { return is_less<cint<bn...>, cint<an...>>::value; }

template <digit_t... an, digit_t... bn>
constexpr bool operator<=(cint<an...>, cint<bn...>) { return !is_less<cint<bn...>, cint<an...>>::value; }

template <digit_t... an, digit_t... bn>
constexpr bool operator>=(cint<an...>, cint<bn...>) { return !is_less<cint<an...>, cint<bn...>>::value; }

template <char... cn>
constexpr parse_literal_t<cn...> operator""_z() { return {}; }

}
}

#endif // AVAKAR_BIGINT_CINT_CINT_H
