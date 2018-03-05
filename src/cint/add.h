#ifndef AVAKAR_BIGINT_CINT_ADD_H
#define AVAKAR_BIGINT_CINT_ADD_H

#include "trim.h"
#include "complement.h"
#include "prepend.h"
#include "digits.h"
#include "cint.h"

namespace avakar {
namespace _cint {

template <typename A, typename B, typename A::digit c>
struct _add;

template <typename A, typename B>
using add_t = trim_t<typename _add<A, B, 0>::type>;

template <typename A>
using neg_t = add_t<com_t<A>, cint<typename A::digit, 1>>;

template <typename A, typename B>
using sub_t = add_t<A, neg_t<B>>;

template <typename A, typename B, typename A::digit c>
struct _add
{
	static constexpr auto _r = digits<typename A::digit>::add(head<A>::value, head<B>::value, c);

	using type = prepend_t<
		typename _add<tail_t<A>, tail_t<B>, _r.first>::type,
		_r.second>;
};

template <typename D, D a0, D b0, D c>
struct _add<cint<D, a0>, cint<D, b0>, c>
{
	static constexpr auto _lo = digits<D>::add(a0, b0, c);
	static constexpr auto _hi = digits<D>::add(sext(a0), sext(b0), _lo.first);

	using type = cint<D, _lo.second, _hi.second>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_ADD_H
