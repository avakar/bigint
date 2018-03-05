#ifndef AVAKAR_BIGINT_CINT_PREPEND_H
#define AVAKAR_BIGINT_CINT_PREPEND_H

#include "fwd.h"

namespace avakar {
namespace _cint {

template <typename C, digit_t<C> d>
struct prepend;

template <typename C, digit_t<C> d>
using prepend_t = typename prepend<C, d>::type;



template <typename D, D d, D... dn>
struct prepend<cint<D, dn...>, d>
{
	using type = cint<D, d, dn...>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_PREPEND_H
