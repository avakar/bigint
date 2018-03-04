#ifndef AVAKAR_BIGINT_CINT_TRAITS_H
#define AVAKAR_BIGINT_CINT_TRAITS_H

#include "fwd.h"

namespace avakar {
namespace _cint {

template <typename X>
struct tail;

template <typename C>
using tail_t = typename tail<C>::type;

template <typename C>
struct is_zero;



template <typename D, D d0, D d1, D... dn>
struct tail<cint<D, d0, d1, dn...>>
{
	using type = cint<D, d1, dn...>;
};

template <typename D, D d0>
struct tail<cint<D, d0>>
{
	using type = cint<D, sext(d0)>;
};

template <typename C>
struct is_zero
	: std::false_type
{
};

template <typename D>
struct is_zero<cint<D, 0>>
	: std::true_type
{
};

template <typename D, D... dn>
struct is_zero<cint<D, 0, 0, dn...>>
	: is_zero<cint<D, 0, dn...>>
{
};

}
}

#endif // AVAKAR_BIGINT_CINT_TRAITS_H
