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

template <typename T, T v, typename = void>
struct make;

template <typename T, T v>
using make_t = trim_t<typename make<T, v>::type>;



template <typename T, T v>
struct make<T, v, typename std::enable_if<std::is_signed<T>::value && (v < 0)>::type>
{
	using _unsigned = typename std::make_unsigned<T>::type;
	using _sub = shift_left_t<cint<1>, make_t<_unsigned, std::numeric_limits<_unsigned>::digits>>;

	using type = sub_t<
		make_t<_unsigned, (_unsigned)v>,
		_sub
		>;
};

template <typename T, T v>
struct make<T, v, typename std::enable_if<std::is_signed<T>::value && (v >= 0)>::type>
{
	using _unsigned = typename std::make_unsigned<T>::type;
	using type = make_t<_unsigned, (_unsigned)v>;
};

template <typename T, T v>
struct make<T, v, typename std::enable_if<std::is_unsigned<T>::value && (digit_t)v != v>::type>
{
	using type = prepend_t<
		make_t<T, (v >> digit_width)>,
		(digit_t)v
	>;
};

template <typename T, T v>
struct make<T, v, typename std::enable_if<std::is_unsigned<T>::value && (digit_t)v == v>::type>
{
	using type = cint<(digit_t)v, 0>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_MAKE_H
