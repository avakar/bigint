#ifndef AVAKAR_BIGINT_CINT_MUL_H
#define AVAKAR_BIGINT_CINT_MUL_H

#include "add.h"
#include "trim.h"
#include "prepend.h"
#include "fwd.h"
#include "digits.h"

namespace avakar {
namespace _cint {

template <typename A, typename B, typename = void>
struct _mul;

template <typename A, typename B>
using mul_t = trim_t<typename _mul<A, B, typename std::enable_if<is_cint<A>::value && is_cint<B>::value>::type>::type>;



template <typename A, digit_t b, digit_t c, typename = void>
struct _mul_one
{
	using _r = mul_digits<head<A>::value, b, c>;

	using type = prepend_t<
		typename _mul_one<tail_t<A>, b, _r::hi>::type,
		_r::lo
		>;
};

template <digit_t a0, digit_t b, digit_t c>
struct _mul_one<cint<a0>, b, c, typename std::enable_if<(a0 & sign_mask) == 0>::type>
{
	using _r = mul_digits<a0, b, c>;

	using type = cint<_r::lo, _r::hi>;
};

template <digit_t a0, digit_t b, digit_t c>
struct _mul_one<cint<a0>, b, c, typename std::enable_if<(a0 & sign_mask) != 0>::type>
{
	using _r = mul_digits<a0, b, c>;
	using _s = add_digits<_r::hi, neg_digit(b), 0>;

	using type = cint<_r::lo, _s::lo>;
};

template <typename A, typename B, typename>
struct _mul
{
	using type = add_t<
		prepend_t<mul_t<A, tail_t<B>>, 0>,
		typename _mul_one<A, head<B>::value, 0>::type>;
};

template <typename A, digit_t b0>
struct _mul<A, cint<b0>, typename std::enable_if<(b0 & sign_mask) == 0>::type>
	: _mul_one<A, b0, 0>
{
};

template <typename A, digit_t b0>
struct _mul<A, cint<b0>, typename std::enable_if<(b0 & sign_mask) != 0>::type>
{
	using type = sub_t<
		typename _mul_one<A, b0, 0>::type,
		prepend_t<A, 0>>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_MUL_H
