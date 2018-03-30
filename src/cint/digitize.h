#ifndef AVAKAR_BIGINT_CINT_DIGITIZE_H
#define AVAKAR_BIGINT_CINT_DIGITIZE_H

#include "make.h"
#include "shift.h"
#include "fwd.h"
#include "digits.h"
#include <limits>
#include <type_traits>

namespace avakar {
namespace _cint {

template <typename T, T... dn>
struct digit_sequence
{
};

template <typename T, typename I>
struct _digitize;

template <typename T, typename I>
using digitize_t = typename _digitize<T, I>::type;



template <typename T, T bits, typename A, typename = void>
struct _extract;

template <typename T, T bits, digit_t a0, digit_t... an>
struct _extract<T, bits, cint<a0, an...>, typename std::enable_if<(bits < digit_width)>::type>
{
	static constexpr T r = (T)a0 & T(((T)1 << bits) - 1);
	static constexpr bool is_negative = (r & T((T)1 << (bits - 1))) != 0;
	using next = shift_right_t<cint<a0, an...>, make_t<T, bits>>;
};

template <typename T, T bits, digit_t a0, digit_t... an>
struct _extract<T, bits, cint<a0, an...>, typename std::enable_if<(bits == digit_width)>::type>
{
	static constexpr T r = (T)a0;
	static constexpr bool is_negative = (r & T((T)1 << (bits - 1))) != 0;
	using next = shift_right_t<cint<a0, an...>, make_t<T, bits>>;
};

template <typename T, T bits, digit_t a0, digit_t... an>
struct _extract<T, bits, cint<a0, an...>, typename std::enable_if<(bits > digit_width)>::type>
{
	using _n = _extract<T, bits - digit_width, shift_right_t<cint<a0, an...>, make_t<T, digit_width>>>;

	static constexpr T r = (T)a0 | (_n::r << digit_width);
	static constexpr bool is_negative = _n::is_negative;
	using next = typename _n::next;
};

template <typename A, typename Seq, bool negative, typename = void>
struct _digitize_next;

template <typename A, typename T, T... dn, bool negative>
struct _digitize_next<A, digit_sequence<T, dn...>, negative>
{
	using _e = _extract<T, std::numeric_limits<T>::digits, A>;
	using type = typename _digitize_next<typename _e::next, digit_sequence<T, dn..., _e::r>, _e::is_negative>::type;
};

template <typename T, T... dn>
struct _digitize_next<cint<0>, digit_sequence<T, dn...>, false>
{
	using type = digit_sequence<T, dn...>;
};

template <typename T, T... dn>
struct _digitize_next<cint<digit_max>, digit_sequence<T, dn...>, true>
{
	using type = digit_sequence<T, dn...>;
};

template <typename T, digit_t a0, digit_t... an>
struct _digitize<T, cint<a0, an...>>
{
	using _e = _extract<T, std::numeric_limits<T>::digits, cint<a0, an...>>;
	using type = typename _digitize_next<typename _e::next, digit_sequence<T, _e::r>, _e::is_negative>::type;
};

}
}

#endif // AVAKAR_BIGINT_CINT_DIGITIZE_H
