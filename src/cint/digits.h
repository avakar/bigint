#ifndef AVAKAR_BIGINT_CINT_DIGITS_H
#define AVAKAR_BIGINT_CINT_DIGITS_H

#include <limits>
#include <utility>

namespace avakar {
namespace _cint {

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

template <typename D>
struct digits
{
	static_assert(is_valid_digit<D>::value, "D is not a valid digit type");

	static constexpr D min = std::numeric_limits<D>::min();
	static constexpr D max = std::numeric_limits<D>::max();
	static constexpr D width = std::numeric_limits<D>::digits;
	static constexpr D sign_mask = (D)1 << (width - 1);

	static constexpr D _hwidth = width / 2;
	static constexpr D _lomask = ((D)1 << _hwidth) - 1;

	using result = std::pair<D, D>;

	static constexpr D neg(D v)
	{
		return ~v + 1;
	}

	// computes `hi:lo = a + b + c`
	static constexpr result add(D a, D b, D c)
	{
		D _r0 = (a & _lomask) + (b & _lomask) + (c & _lomask);
		D _r1 = (a >> _hwidth) + (b >> _hwidth) + (c >> _hwidth) + (_r0 >> _hwidth);

		D hi = _r1 >> _hwidth;
		D lo = ((_r1 & _lomask) << _hwidth) | (_r0 & _lomask);

		return { hi, lo };
	}

	// computes `hi:lo = a * b + c`
	static constexpr result mul(D a, D b, D c)
	{
		D _r0 = (a & _lomask) * (b & _lomask);
		D _r1 = (a & _lomask) * (b >> _hwidth);
		D _r2 = (a >> _hwidth) * (b & _lomask);
		D _r3 = (a >> _hwidth) * (b >> _hwidth);

		D _s0 = (_r0 & _lomask) + (c & _lomask);
		D _s1 = (_r2 & _lomask) + (_r1 & _lomask) + (_r0 >> _hwidth) + (_s0 >> _hwidth) + (c >> _hwidth);
		D _s2 = (_r3 & _lomask) + (_r2 >> _hwidth) + (_r1 >> _hwidth) + (_s1 >> _hwidth);
		D _s3 = (_r3 >> _hwidth) + (_s2 >> _hwidth);

		D lo = (_s0 & _lomask) | ((_s1 & _lomask) << _hwidth);
		D hi = (_s2 & _lomask) | ((_s3 & _lomask) << _hwidth);

		return { hi, lo };
	}

	static constexpr result shl(D a, D s)
	{
		return { a >> (width - s), a << s };
	}
};

template <typename D>
constexpr D sext(D v)
{
	return v & digits<D>::sign_mask? digits<D>::max: digits<D>::min;
}

}
}

#endif // AVAKAR_BIGINT_CINT_DIGITS_H
