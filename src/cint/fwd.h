#ifndef AVAKAR_BIGINT_CINT_FWD_H
#define AVAKAR_BIGINT_CINT_FWD_H

#include "digits.h"
#include <type_traits>

namespace avakar {
namespace _cint {

template <digit_t d0, digit_t... dn>
struct cint;

template <typename T>
struct is_cint;

using digit_width_t = cint<digit_width>;

template <typename A>
struct head;

template <typename X>
struct tail;

template <typename C>
using tail_t = typename tail<C>::type;



template <typename T>
struct is_cint
	: std::false_type
{
};

template <digit_t a0, digit_t... an>
struct is_cint<cint<a0, an...>>
	: std::true_type
{
};

template <digit_t d0, digit_t... dn>
struct head<cint<d0, dn...>>
	: std::integral_constant<digit_t, d0>
{
};

template <digit_t d0, digit_t d1, digit_t... dn>
struct tail<cint<d0, d1, dn...>>
{
	using type = cint<d1, dn...>;
};

template <digit_t d0>
struct tail<cint<d0>>
{
	using type = cint<sext(d0)>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_FWD_H
