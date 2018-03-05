#ifndef AVAKAR_BIGINT_CINT_ADD_H
#define AVAKAR_BIGINT_CINT_ADD_H

#include "trim.h"
#include "complement.h"
#include "prepend.h"
#include "digits.h"

namespace avakar {
namespace _cint {

template <typename A, typename B, digit_t<A> c>
struct _add;

template <typename A, typename B>
using add_t = trim_t<typename _add<A, B, 0>::type>;

template <typename A>
using neg_t = add_t<com_t<A>, cint<digit_t<A>, 1>>;

template <typename A, typename B>
using sub_t = add_t<A, neg_t<B>>;

template <typename A, typename B, digit_t<A> c>
struct _add
{
	using _r = add_digits<digit_t<A>, head<A>::value, head<B>::value, c>;

	using type = prepend_t<
		typename _add<tail_t<A>, tail_t<B>, _r::hi>::type,
		_r::lo>;
};

template <typename D, D a0, D b0, D c>
struct _add<cint<D, a0>, cint<D, b0>, c>
{
	using _lo = add_digits<D, a0, b0, c>;
	using _hi = add_digits<D, sext(a0), sext(b0), _lo::hi>;

	using type = cint<D, _lo::lo, _hi::lo>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_ADD_H
