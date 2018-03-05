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
using is_zero = is_equal<A, cint<digit_t<A>, 0>>;

template <typename C>
struct is_negative
	: is_negative<tail_t<C>>
{
};

template <typename D, D a0>
struct is_negative<cint<D, a0>>
	: std::integral_constant<bool, (a0 & digits<D>::sign_mask) != 0>
{
};

template <typename A, typename B>
struct is_less
	: is_negative<sub_t<A, B>>
{
};


template <typename C>
struct is_positive;

template <typename D, D d0>
struct is_positive<cint<D, d0>>
	: std::integral_constant<bool, (d0 != 0) && (d0 & digits<D>::sign_mask) == 0>
{
};

template <typename D, D d0, D d1, D... dn>
struct is_positive<cint<D, d0, d1, dn...>>
	: std::integral_constant<bool, (d0 == 0) ? is_positive<cint<D, d1, dn...>>::value : !is_negative<cint<D, d1, dn...>>::value>
{
};

}
}

#endif // AVAKAR_BIGINT_CINT_COMPARE_H
