#ifndef AVAKAR_BIGINT_CINT_TRAITS_H
#define AVAKAR_BIGINT_CINT_TRAITS_H

#include "fwd.h"

namespace avakar {
namespace _cint {

template <typename C>
struct is_zero;



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
