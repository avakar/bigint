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


template <typename C, digit_t d>
struct _prepend_trim;

template <digit_t d0, digit_t d>
struct _prepend_trim<cint<d0>, d>
{
	using type = typename std::conditional<
		sext(d) != d0,
		cint<d, d0>,
		cint<d>>::type;
};

template <digit_t d0, digit_t d1, digit_t... dn, digit_t d>
struct _prepend_trim<cint<d0, d1, dn...>, d>
{
	using type = cint<d, d0, d1, dn...>;
};

template <digit_t d0>
struct _trim<cint<d0>>
{
	using type = cint<d0>;
};

template <digit_t d0, digit_t d1, digit_t... dn>
struct _trim<cint<d0, d1, dn...>>
{
	using type = typename _prepend_trim<trim_t<cint<d1, dn...>>, d0>::type;
};


}
}

#endif // AVAKAR_BIGINT_CINT_TRIM_H
