#ifndef AVAKAR_BIGINT_CINT_BITWISE_H
#define AVAKAR_BIGINT_CINT_BITWISE_H

#include "trim.h"
#include "prepend.h"

namespace avakar {
namespace _cint {

template <typename A, typename B>
struct _bitwise_and;

template <typename A, typename B>
struct _bitwise_or;

template <typename A, typename B>
struct _bitwise_xor;

template <typename A, typename B>
using bitwise_and_t = trim_t<typename _bitwise_and<A, B>::type>;

template <typename A, typename B>
using bitwise_or_t = trim_t<typename _bitwise_or<A, B>::type>;

template <typename A, typename B>
using bitwise_xor_t = trim_t<typename _bitwise_xor<A, B>::type>;



template <digit_t a0, digit_t... an, digit_t b0, digit_t... bn>
struct _bitwise_and<cint<a0, an...>, cint<b0, bn...>>
{
	using type = prepend_t<
		bitwise_and_t<tail_t<cint<a0, an...>>, tail_t<cint<b0, bn...>>>,
		a0 & b0
		>;
};

template <digit_t a0, digit_t b0>
struct _bitwise_and<cint<a0>, cint<b0>>
{
	using type = cint<a0 & b0>;
};

template <digit_t a0, digit_t... an, digit_t b0, digit_t... bn>
struct _bitwise_or<cint<a0, an...>, cint<b0, bn...>>
{
	using type = prepend_t<
		bitwise_or_t<tail_t<cint<a0, an...>>, tail_t<cint<b0, bn...>>>,
		a0 | b0
	>;
};

template <digit_t a0, digit_t b0>
struct _bitwise_or<cint<a0>, cint<b0>>
{
	using type = cint<a0 | b0>;
};

template <digit_t a0, digit_t... an, digit_t b0, digit_t... bn>
struct _bitwise_xor<cint<a0, an...>, cint<b0, bn...>>
{
	using type = prepend_t<
		bitwise_xor_t<tail_t<cint<a0, an...>>, tail_t<cint<b0, bn...>>>,
		a0 ^ b0
	>;
};

template <digit_t a0, digit_t b0>
struct _bitwise_xor<cint<a0>, cint<b0>>
{
	using type = cint<a0 ^ b0>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_BITWISE_H
