#ifndef AVAKAR_BIGINT_CINT_PREPEND_H
#define AVAKAR_BIGINT_CINT_PREPEND_H

#include "fwd.h"

namespace avakar {
namespace _cint {

template <typename C, digit_t d>
struct prepend;

template <typename C, digit_t d>
using prepend_t = typename prepend<C, d>::type;



template <digit_t d0, digit_t... dn, digit_t d>
struct prepend<cint<d0, dn...>, d>
{
	using type = cint<d, d0, dn...>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_PREPEND_H
