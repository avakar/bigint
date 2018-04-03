#ifndef AVAKAR_BIGINT_INTN_INTN_H
#define AVAKAR_BIGINT_INTN_INTN_H

#include "../digitizer.h"
#include "../cint/cint.h"
#include "../cint/make.h"
#include <algorithm>
#include <cstddef>
#include <string>

namespace avakar {
namespace _intn {

using std::size_t;
using _cint::operator""_z;

template <size_t width, bool signed_>
struct _intn_limits;

template <size_t width>
struct _intn_limits<width, /*signed_=*/true>
{
	static constexpr auto width_v = _cint::make_t<size_t, width>{};

	static constexpr auto min = -1_z << (width_v - 1_z);
	static constexpr auto max = (1_z << (width_v - 1_z)) - 1_z;
};

template <size_t width>
struct _intn_limits<width, /*signed_=*/false>
{
	static constexpr auto width_v = _cint::make_t<size_t, width>{};

	static constexpr auto min = 0_z;
	static constexpr auto max = (1_z << width_v) - 1_z;
};

template <size_t width, bool signed_, typename A>
struct _cint_fits;

template <size_t width, bool signed_, _cint::digit_t d0, _cint::digit_t... dn>
struct _cint_fits<width, signed_, _cint::cint<d0, dn...>>
{
	using _limits = _intn_limits<width, signed_>;
	using _c = _cint::cint<d0, dn...>;

	static constexpr bool value = (_limits::min <= _c{} && _c{} <= _limits::max);
};

template <size_t width, bool signed_, typename Traits>
struct intn
{
	using digit_type = typename Traits::digit_type;

	intn()
		: _digits{}
	{
	}

	template <
		typename A,
		typename std::enable_if<_cint_fits<width, signed_, A>::value, int>::type = 0>
	intn(A)
		: intn(_cint::digitize_fixed_t<digit_type, _digit_count, A>{})
	{
	}

	template <
		typename A,
		typename std::enable_if<!_cint_fits<width, signed_, A>::value, int>::type = 0>
	explicit intn(A)
		: intn(_cint::digitize_fixed_t<digit_type, _digit_count, A>{})
	{
	}

	template <
		typename I,
		typename std::enable_if<std::is_integral<I>::value, int>::type = 0>
	intn(I const & v)
	{
	}

	explicit operator bool() const
	{
		for (digit_type d : _digits)
		{
			if (d != 0)
				return true;
		}

		return false;
	}

	intn & operator++()
	{
		Traits::adds(_digits, 1, _digit_count);
		return *this;
	}

	intn operator++(int)
	{
		intn r = *this;
		++r;
		return r;
	}

	intn & operator--()
	{
		Traits::adds(_digits, digit_type(-1), _digit_count);
		return *this;
	}

	intn operator--(int)
	{
		intn r = *this;
		--*this;
		return r;
	}

	intn operator+() const
	{
		return *this;
	}

	intn operator-() const
	{
		intn r = ~*this;
		return ++r;
	}

	intn operator~() const
	{
		intn r;
		for (size_t i = 0; i != _digit_count; ++i)
			r._digits[i] = ~_digits[i];
		return r;
	}

	intn & operator+=(intn const & rhs)
	{
		Traits::addn(_digits, rhs._digits, _digit_count);
		return *this;
	}

	intn & operator-=(intn const & rhs)
	{
		Traits::subn(_digits, rhs._digits, _digit_count);
		return *this;
	}

	intn & operator*=(intn const & rhs)
	{
		return *this = *this * rhs;
	}

	intn & operator^=(intn const & rhs)
	{
		for (size_t i = 0; i != _digit_count; ++i)
			_digits[i] ^= rhs._digits[i];
		return *this;
	}

	intn & operator&=(intn const & rhs)
	{
		for (size_t i = 0; i != _digit_count; ++i)
			_digits[i] &= rhs._digits[i];
		return *this;
	}

	intn & operator|=(intn const & rhs)
	{
		for (size_t i = 0; i != _digit_count; ++i)
			_digits[i] |= rhs._digits[i];
		return *this;
	}

	friend intn operator+(intn lhs, intn const & rhs)
	{
		return lhs += rhs;
	}

	friend intn operator-(intn lhs, intn const & rhs)
	{
		return lhs -= rhs;
	}

	friend intn operator*(intn const & lhs, intn const & rhs)
	{
		intn r;
		for (size_t i = 0; i != _digit_count; ++i)
			Traits::mul(&r._digits[i], lhs._digits, _digit_count - i, rhs._digits[i]);
		return r;
	}

	friend intn operator^(intn lhs, intn const & rhs)
	{
		return lhs ^= rhs;
	}

	friend intn operator&(intn lhs, intn const & rhs)
	{
		return lhs &= rhs;
	}

	friend intn operator|(intn lhs, intn const & rhs)
	{
		return lhs |= rhs;
	}

	friend bool operator==(intn const & lhs, intn const & rhs)
	{
		return std::equal(lhs._digits, lhs._digits + _digit_count, rhs._digits);
	}

	friend bool operator!=(intn const & lhs, intn const & rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(intn const & lhs, intn const & rhs)
	{
		return Traits::cmpn(lhs._digits, rhs._digits, _digit_count) != 0;
	}

	friend bool operator>(intn const & lhs, intn const & rhs)
	{
		return rhs < lhs;
	}

	friend bool operator<=(intn const & lhs, intn const & rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>=(intn const & lhs, intn const & rhs)
	{
		return !(lhs < rhs);
	}

private:
	template <digit_type... dn>
	intn(_cint::digit_sequence<digit_type, dn...>)
		: _digits{ dn... }
	{
	}

	static constexpr digit_type _digit_width = std::numeric_limits<digit_type>::digits;
	static constexpr size_t _digit_count = (width + _digit_width - 1) / _digit_width;

	digit_type _digits[_digit_count];
};

}
}

#endif // AVAKAR_BIGINT_INTN_INTN_H
