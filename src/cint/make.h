#ifndef AVAKAR_BIGINT_CINT_MAKE_H
#define AVAKAR_BIGINT_CINT_MAKE_H

#include "trim.h"
#include "add.h"
#include "shift.h"
#include "prepend.h"
#include "digits.h"
#include "fwd.h"
#include <type_traits>

namespace avakar {
namespace _cint {

template <typename D, typename T, T v, typename = void>
struct make;

template <typename D, typename T, T v>
using make_t = trim_t<typename make<D, T, v>::type>;



template <typename D, typename T, T v>
struct make<D, T, v, typename std::enable_if<std::is_signed<T>::value && (v < 0)>::type>
{
	using _unsigned = typename std::make_unsigned<T>::type;
	using _sub = shift_left_t<cint<D, 1>, make_t<D, _unsigned, digits<_unsigned>::width>>;

	using type = sub_t<
		make_t<D, _unsigned, (_unsigned)v>,
		_sub
		>;
};

template <typename D, typename T, T v>
struct make<D, T, v, typename std::enable_if<std::is_signed<T>::value && (v >= 0)>::type>
{
	using _unsigned = typename std::make_unsigned<T>::type;

	using type = make_t<D, _unsigned, (_unsigned)v>;
};

template <typename D, typename T, T v>
struct make<D, T, v, typename std::enable_if<std::is_unsigned<T>::value && (D)v != v>::type>
{
	using type = prepend_t<
		make_t<D, T, (v >> digits<D>::width)>,
		(D)v
	>;
};

template <typename D, typename T, T v>
struct make<D, T, v, typename std::enable_if<std::is_unsigned<T>::value && (D)v == v>::type>
{
	using type = cint<D, (D)v, 0>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_MAKE_H
