#ifndef AVAKAR_BIGINT_CINT_MUL_H
#define AVAKAR_BIGINT_CINT_MUL_H

#include "add.h"
#include "trim.h"
#include "prepend.h"
#include "fwd.h"
#include "digits.h"

namespace avakar {
namespace _cint {

template <typename A, typename B>
struct mul;

template <typename A, typename B>
using mul_t = trim_t<typename mul<A, B>::type>;



template <typename A, digit_t<A> b, digit_t<A> c, typename = void>
struct _mul_one
{
	using _r = mul_digits<digit_t<A>, head<A>::value, b, c>;

	using type = prepend_t<
		typename _mul_one<tail_t<A>, b, _r::hi>::type,
		_r::lo
		>;
};

template <typename D, D a0, D b, D c>
struct _mul_one<cint<D, a0>, b, c, typename std::enable_if<(a0 & digits<D>::sign_mask) == 0>::type>
{
	using _r = mul_digits<D, a0, b, c>;

	using type = cint<D, _r::lo, _r::hi>;
};

template <typename D, D a0, D b, D c>
struct _mul_one<cint<D, a0>, b, c, typename std::enable_if<(a0 & digits<D>::sign_mask) != 0>::type>
{
	using _r = mul_digits<D, a0, b, c>;

	using type = cint<D, _r::lo, add_digits<D, _r::hi, neg_digit(b), 0>::lo>;
};

template <typename A, typename B, typename = void>
struct _mul_all
{
	using type = add_t<
		prepend_t<mul_t<A, tail_t<B>>, 0>,
		typename _mul_one<A, head<B>::value, 0>::type>;
};

template <typename D, typename A, D b0>
struct _mul_all<A, cint<D, b0>, typename std::enable_if<(b0 & digits<D>::sign_mask) == 0>::type>
	: _mul_one<A, b0, 0>
{
};

template <typename D, typename A, D b0>
struct _mul_all<A, cint<D, b0>, typename std::enable_if<(b0 & digits<D>::sign_mask) != 0>::type>
{
	using type = sub_t<
		typename _mul_one<A, b0, 0>::type,
		prepend_t<A, 0>>;
};

template <typename A, typename B>
struct mul
	: _mul_all<A, B>
{
};

}
}

#endif // AVAKAR_BIGINT_CINT_MUL_H
