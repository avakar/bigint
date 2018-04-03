#ifndef AVAKAR_BIGINT_DIGITIZER_H
#define AVAKAR_BIGINT_DIGITIZER_H

#include <limits>

namespace avakar {
namespace _bigint {

template <typename D, size_t bits, typename = void>
struct _digit_properties
{
	static constexpr size_t _width = std::numeric_limits<D>::digits;
	using _next = _digit_properties<D, bits - _width>;

	static constexpr size_t last_bit_digit = _next::last_bit_digit + 1;
	static constexpr size_t sext_bit_digit = _next::sext_bit_digit + 1;
	static constexpr D sign_mask = _next::sign_mask;
	static constexpr D sext_mask = _next::sext_mask;
};

template <typename D, size_t bits>
struct _digit_properties<D, bits, typename std::enable_if<(bits == std::numeric_limits<D>::digits)>::type>
{
	static constexpr size_t last_bit_digit = 0;
	static constexpr size_t sext_bit_digit = 1;
	static constexpr D sign_mask = (D)1 << (bits - 1);
	static constexpr D sext_mask = 0;
};

template <typename D, size_t bits>
struct _digit_properties<D, bits, typename std::enable_if<(bits < std::numeric_limits<D>::digits)>::type>
{
	static constexpr size_t last_bit_digit = 0;
	static constexpr size_t sext_bit_digit = 0;
	static constexpr D sign_mask = (D)1 << (bits - 1);
	static constexpr D sext_mask = ~(D((sign_mask - 1) << 1) | (D)1);
};

template <typename D, typename T>
using digit_properties_t = _digit_properties<D, std::numeric_limits<T>::digits>;

template <typename D, typename I, size_t len, typename = void>
struct _digitizer;

template <typename D, typename I, size_t len>
struct _digitizer<D, I, len, typename std::enable_if<_cint::is_unsigned_integer<I>::value>::type>
{
	static void digitize(D * dest, I src)
	{
		dest[0] = (D)src;


		for (size_t i = 0; i != len; ++i)
		{
			dest[i] = (D)src;
			src >> 
		}
		_extr::extract(dest, src);
	}
};

template <typename D, typename I>
struct _digitizer<D, I, typename std::enable_if<!_cint::is_unsigned_integer<I>::value>::type>
{
	// XXX assumption
	using _u = typename std::make_unsigned<I>::type;

	using _extr = _bit_extractor<D, std::numeric_limits<_u>::digits>;
	static constexpr size_t needed_digits = _extr::last_bit_digit + 1;

	static void digitize(D * dest, size_t len, I const & src)
	{
		_extr::extract(dest, static_cast<_u>(src));
		if (dest[_extr::last_bit_digit] & _extr::sign_mask)

			dest[_extr::last_bit_digit] |= _extr::sext_mask;
	}
};

template <typename D>
struct _digitizer<D, bool>
{
	static constexpr size_t needed_digits = 1;
	static void digitize(D * dest, size_t len, bool src)
	{
		dest[0] = src;
		std::fill(dest + 1, dest + len, 0);
	}
};


}
}

#endif // AVAKAR_BIGINT_DIGITIZER_H
