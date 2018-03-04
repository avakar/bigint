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


template <typename D, D... dn>
struct _com<cint<D, dn...>>
{
	using type = cint<D, (dn ^ digits<D>::max)...>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_COM_H
