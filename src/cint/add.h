#ifndef AVAKAR_BIGINT_CINT_ADD_H
#define AVAKAR_BIGINT_CINT_ADD_H

#include "trim.h"
#include "complement.h"
#include "prepend.h"
#include "digits.h"

namespace avakar {
namespace _cint {

template <typename A, typename B, digit_t c>
struct _add;

template <typename A, typename B>
using add_t = trim_t<typename _add<A, B, 0>::type>;

template <typename A>
using neg_t = add_t<com_t<A>, cint<1>>;

template <typename A, typename B>
using sub_t = add_t<A, neg_t<B>>;

template <digit_t a0, digit_t... an, digit_t b0, digit_t... bn, digit_t c>
struct _add<cint<a0, an...>, cint<b0, bn...>, c>
{
	using _r = add_digits<a0, b0, c>;

	using type = prepend_t<
		typename _add<tail_t<cint<a0, an...>>, tail_t<cint<b0, bn...>>, _r::hi>::type,
		_r::lo>;
};

template <digit_t a0, digit_t b0, digit_t c>
struct _add<cint<a0>, cint<b0>, c>
{
	using _lo = add_digits<a0, b0, c>;
	using _hi = add_digits<sext(a0), sext(b0), _lo::hi>;

	using type = cint<_lo::lo, _hi::lo>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_ADD_H
