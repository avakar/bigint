#ifndef AVAKAR_BIGINT_CINT_COMPARE_H
#define AVAKAR_BIGINT_CINT_COMPARE_H

#include "add.h"
#include "trim.h"
#include "fwd.h"
#include "digits.h"
#include <type_traits>

namespace avakar {
namespace _cint {

template <typename A, typename B>
using is_equal = std::is_same<trim_t<A>, trim_t<B>>;

template <typename A>
using is_zero = is_equal<A, cint<0>>;

template <typename C>
struct is_negative
	: is_negative<tail_t<C>>
{
};

template <digit_t a0>
struct is_negative<cint<a0>>
	: std::integral_constant<bool, (a0 & sign_mask) != 0>
{
};

template <typename A, typename B>
struct is_less
	: is_negative<sub_t<A, B>>
{
};


template <typename C>
struct is_positive;

template <digit_t d0>
struct is_positive<cint<d0>>
	: std::integral_constant<bool, (d0 != 0) && (d0 & sign_mask) == 0>
{
};

template <digit_t d0, digit_t d1, digit_t... dn>
struct is_positive<cint<d0, d1, dn...>>
	: std::integral_constant<bool, (d0 == 0) ? is_positive<cint<d1, dn...>>::value : !is_negative<cint<d1, dn...>>::value>
{
};

}
}

#endif // AVAKAR_BIGINT_CINT_COMPARE_H
