#ifndef AVAKAR_BIGINT_CINT_TRIM_H
#define AVAKAR_BIGINT_CINT_TRIM_H

#include "digits.h"
#include "fwd.h"
#include <type_traits>

namespace avakar {
namespace _cint {

template <typename C>
struct _trim;

template <typename C>
using trim_t = typename _trim<C>::type;


template <typename C, digit_t<C> d>
struct _prepend_trim;

template <typename D, D d0, D d>
struct _prepend_trim<cint<D, d0>, d>
{
	using type = typename std::conditional<
		sext(d) != d0,
		cint<D, d, d0>,
		cint<D, d>>::type;
};

template <typename D, D d0, D d1, D... dn, D d>
struct _prepend_trim<cint<D, d0, d1, dn...>, d>
{
	using type = cint<D, d, d0, d1, dn...>;
};

template <typename D, D d0>
struct _trim<cint<D, d0>>
{
	using type = cint<D, d0>;
};

template <typename D, D d0, D d1, D... dn>
struct _trim<cint<D, d0, d1, dn...>>
{
	using type = typename _prepend_trim<trim_t<cint<D, d1, dn...>>, d0>::type;
};


}
}

#endif // AVAKAR_BIGINT_CINT_TRIM_H
