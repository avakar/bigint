#ifndef AVAKAR_BIGINT_CINT_DIGITS_H
#define AVAKAR_BIGINT_CINT_DIGITS_H

#include <cstdint>
#include <limits>
#include <utility>

namespace avakar {
namespace _cint {

using digit_t = std::uint_least32_t;

static constexpr digit_t digit_max = 0xffffffff;
static constexpr digit_t digit_width = 32;
static constexpr digit_t sign_mask = 0x80000000;

constexpr digit_t sext(digit_t v)
{
	return v & sign_mask? digit_max: 0;
}

constexpr digit_t neg_digit(digit_t v)
{
	return v == 0? 0: ((~v + 1) & digit_max);
}

template <digit_t a, digit_t b, digit_t c>
struct add_digits
{
	static constexpr auto _r
		= (std::uint_least64_t)a
		+ (std::uint_least64_t)b
		+ (std::uint_least64_t)c;

	static constexpr digit_t lo = _r & digit_max;
	static constexpr digit_t hi = (_r >> digit_width) & digit_max;
};

template <digit_t a, digit_t b, digit_t c>
struct mul_digits
{
	static constexpr auto _r
		= (std::uint_least64_t)a
		* (std::uint_least64_t)b
		+ (std::uint_least64_t)c;

	static constexpr digit_t lo = _r & digit_max;
	static constexpr digit_t hi = (_r >> digit_width) & digit_max;
};

template <typename T>
struct is_unsigned_integer
	: std::integral_constant<bool,
	std::is_integral<T>::value
	&& std::is_unsigned<T>::value
	&& !std::is_same<T, bool>::value
	&& !std::is_same<T, wchar_t>::value
	&& !std::is_same<T, char16_t>::value
	&& !std::is_same<T, char32_t>::value
	>
{
};

template <typename T>
struct is_valid_digit
	: std::integral_constant<bool,
		is_unsigned_integer<T>::value
		&& std::numeric_limits<T>::digits % 2 == 0
	>
{
};

}
}

#endif // AVAKAR_BIGINT_CINT_DIGITS_H
