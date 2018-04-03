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

template <typename T, size_t N, typename I, typename S = digit_sequence<T>>
struct _digitize_fixed;

template <typename T, size_t N, typename I>
using digitize_fixed_t = typename _digitize_fixed<T, N, I>::type;

template <typename T, typename A, typename = void>
struct _convert;

template <typename T, typename A>
using convert = _convert<T, A>;



template <typename T, typename A, T bits = std::numeric_limits<T>::digits, typename = void>
struct _extract;

template <typename T, digit_t a0, digit_t... an, T bits>
struct _extract<T, cint<a0, an...>, bits, typename std::enable_if<(bits < digit_width)>::type>
{
	static constexpr T value = (T)a0 & T(((T)1 << bits) - 1);
	using next = shift_right_t<cint<a0, an...>, make_t<T, bits>>;
};

template <typename T, digit_t a0, digit_t... an, T bits>
struct _extract<T, cint<a0, an...>, bits, typename std::enable_if<(bits == digit_width)>::type>
{
	static constexpr T value = (T)a0;
	using next = shift_right_t<cint<a0, an...>, make_t<T, bits>>;
};

template <typename T, digit_t a0, digit_t... an, T bits>
struct _extract<T, cint<a0, an...>, bits, typename std::enable_if<(bits > digit_width)>::type>
{
	using _n = _extract<T, shift_right_t<cint<a0, an...>, make_t<T, digit_width>>, bits - digit_width>;

	static constexpr T value = (T)a0 | (_n::value << digit_width);
	using next = typename _n::next;
};

template <typename A, typename Seq, bool prev_sign, typename = void>
struct _digitize_next;

template <typename A, typename T, T... dn, bool prev_sign>
struct _digitize_next<A, digit_sequence<T, dn...>, prev_sign>
{
	using _e = _extract<T, A>;
	using type = typename _digitize_next<typename _e::next, digit_sequence<T, dn..., _e::value>, sign_flag(_e::value)>::type;
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
	using _e = _extract<T, cint<a0, an...>>;
	using type = typename _digitize_next<typename _e::next, digit_sequence<T, _e::value>, sign_flag(_e::value)>::type;
};

template <typename T, size_t N, typename I, T... dn>
struct _digitize_fixed<T, N, I, digit_sequence<T, dn...>>
{
	using _e = _extract<T, I>;
	using type = typename _digitize_fixed<T, N - 1, typename _e::next, digit_sequence<T, dn..., _e::value>>::type;
};

template <typename T, typename I, T... dn>
struct _digitize_fixed<T, 0, I, digit_sequence<T, dn...>>
{
	using type = digit_sequence<T, dn...>;
};

template <typename T, typename A>
struct _convert<T, A, typename std::enable_if<is_unsigned_integer<T>::value>::type>
{
	using _e = _extract<T, A>;

	static constexpr T value = _e::value;
	using next = typename _e::next;
	static constexpr bool implicit = is_equal<next, cint<0>>::value;
};

template <typename T, typename A>
struct _convert<T, A, typename std::enable_if<!is_unsigned_integer<T>::value && std::is_integral<T>::value>::type>
{
	using _unsigned = typename std::make_unsigned<T>::type;
	static_assert(std::numeric_limits<T>::digits + 1 == std::numeric_limits<_unsigned>::digits,
		"the assumption that the unsigned integer type corresponding to "
		"a signed integer has the same number of bits in the value representation is false");

	using _conv = _convert<_unsigned, A>;

	// XXX: assumption about the behavior of out-of-range cast to signed
	static constexpr T value = (T)_conv::value;
	using next = typename _conv::next;
	static constexpr bool implicit = value < 0 ? is_equal<next, cint<digit_max>>::value : is_equal<next, cint<0>>::value;
};

template <typename T, typename A>
struct _convert<T, A, typename std::enable_if<std::is_enum<T>::value>::type>
{
	using _underlying = typename std::underlying_type<T>::type;
	using _conv = _convert<_underlying, A>;

	static constexpr T value = (T)_conv::value;
	using next = typename _conv::next;
	static constexpr bool implicit = std::is_convertible<T, _underlying>::value && _conv::implicit;
};

template <typename A>
struct _convert<bool, A>
{
};

}
}

#endif // AVAKAR_BIGINT_CINT_DIGITIZE_H
