#ifndef AVAKAR_BIGINT_CINT_COM_H
#define AVAKAR_BIGINT_CINT_COM_H

#include "trim.h"
#include "fwd.h"
#include "digits.h"

namespace avakar {
namespace _cint {

template <typename C>
struct _com;

template <typename C>
using com_t = trim_t<typename _com<C>::type>;


template <digit_t d0, digit_t... dn>
struct _com<cint<d0, dn...>>
{
	using type = cint<d0 ^ digit_max, (dn ^ digit_max)...>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_COM_H
