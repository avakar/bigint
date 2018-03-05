#ifndef AVAKAR_BIGINT_CINT_BITWISE_H
#define AVAKAR_BIGINT_CINT_BITWISE_H

#include "trim.h"
#include "prepend.h"
#include "cint.h"

namespace avakar {
namespace _cint {

template <typename A, typename B>
struct bitwise_and
{
	using type = prepend_t<
		typename bitwise_and<tail_t<A>, tail_t<B>>::type,
		head<A>::value & head<B>::value
		>;
};

template <typename D, D a0, D b0>
struct bitwise_and<cint<D, a0>, cint<D, b0>>
{
	using type = cint<D, a0 & b0>;
};

template <typename A, typename B>
using bitwise_and_t = trim_t<typename bitwise_and<A, B>::type>;


template <typename A, typename B>
struct bitwise_or
{
	using type = prepend_t<
		typename bitwise_or<tail_t<A>, tail_t<B>>::type,
		head<A>::value | head<B>::value
	>;
};

template <typename D, D a0, D b0>
struct bitwise_or<cint<D, a0>, cint<D, b0>>
{
	using type = cint<D, a0 | b0>;
};

template <typename A, typename B>
using bitwise_or_t = trim_t<typename bitwise_or<A, B>::type>;


template <typename A, typename B>
struct bitwise_xor
{
	using type = prepend_t<
		typename bitwise_xor<tail_t<A>, tail_t<B>>::type,
		head<A>::value ^ head<B>::value
	>;
};

template <typename D, D a0, D b0>
struct bitwise_xor<cint<D, a0>, cint<D, b0>>
{
	using type = cint<D, a0 ^ b0>;
};

template <typename A, typename B>
using bitwise_xor_t = trim_t<typename bitwise_xor<A, B>::type>;

}
}

#endif // AVAKAR_BIGINT_CINT_BITWISE_H
