#ifndef AVAKAR_BIGINT_CINT_FWD_H
#define AVAKAR_BIGINT_CINT_FWD_H

#include "digits.h"
#include <type_traits>

namespace avakar {
namespace _cint {

template <typename D, D d0, D... dn>
struct cint;

template <typename A>
struct head;

template <typename X>
struct tail;

template <typename C>
using tail_t = typename tail<C>::type;

template <typename D>
using cwidth_t = cint<D, digits<D>::width>;



template <typename D, D d0, D... dn>
struct head<cint<D, d0, dn...>>
	: std::integral_constant<D, d0>
{
};

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

}
}

#endif // AVAKAR_BIGINT_CINT_FWD_H
