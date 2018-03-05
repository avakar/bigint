#ifndef AVAKAR_BIGINT_CINT_CINT_H
#define AVAKAR_BIGINT_CINT_CINT_H

#include "digits.h"
#include "traits.h"
#include "fwd.h"

namespace avakar {
namespace _cint {

template <typename D, D d0, D... dn>
struct cint
{
	using digit = D;
	using digit_width = cint<D, digits<D>::width>;

	constexpr explicit operator bool() const
	{
		return !is_zero<cint<D, d0, dn...>>::value;
	}
};

}
}

#endif // AVAKAR_BIGINT_CINT_CINT_H
