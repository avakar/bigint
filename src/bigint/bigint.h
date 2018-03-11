#ifndef AVAKAR_BIGINT_BIGINT_BIGINT_H
#define AVAKAR_BIGINT_BIGINT_BIGINT_H

#include "../cint/cint.h"

#include <type_traits>
#include <algorithm>
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include <cassert>
#include <stdexcept>

namespace avakar {
namespace _bigint {

using _cint::cint;

template <typename D, size_t bits, typename = void>
struct _bit_extractor
{
	static constexpr size_t _width = std::numeric_limits<D>::digits;
	using _next = _bit_extractor<D, bits - _width>;

	static constexpr size_t last_bit_digit = _next::last_bit_digit + 1;
	static constexpr size_t sext_bit_digit = _next::sext_bit_digit + 1;
	static constexpr D sign_mask = _next::sign_mask;
	static constexpr D sext_mask = _next::sext_mask;

	template <typename U>
	static void extract(D * dest, U const & src)
	{
		*dest = static_cast<D>(src);
		_next::extract(dest + 1, src >> _width);
	}
};

template <typename D, size_t bits>
struct _bit_extractor<D, bits, typename std::enable_if<(bits == std::numeric_limits<D>::digits)>::type>
{
	static constexpr size_t last_bit_digit = 0;
	static constexpr size_t sext_bit_digit = 1;
	static constexpr D sign_mask = (D)1 << (bits - 1);
	static constexpr D sext_mask = 0;

	template <typename U>
	static void extract(D * dest, U const & src)
	{
		*dest = static_cast<D>(src);
	}
};

template <typename D, size_t bits>
struct _bit_extractor<D, bits, typename std::enable_if<(bits < std::numeric_limits<D>::digits)>::type>
{
	static constexpr size_t last_bit_digit = 0;
	static constexpr size_t sext_bit_digit = 0;
	static constexpr D sign_mask = (D)1 << (bits - 1);
	static constexpr D sext_mask = ~(D((sign_mask - 1) << 1) | (D)1);

	template <typename U>
	static void extract(D * dest, U const & src)
	{
		*dest = static_cast<D>(src);
	}
};

template <typename D, typename I, typename = void>
struct _digitizer;

template <typename D, typename I>
struct _digitizer<D, I, typename std::enable_if<_cint::is_unsigned_integer<I>::value>::type>
{
	using _extr = _bit_extractor<D, std::numeric_limits<I>::digits>;
	static constexpr size_t needed_digits = _extr::sext_bit_digit + 1;

	static constexpr void digitize(D * dest, I const & src)
	{
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

	static void digitize(D * dest, I const & src)
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
	static constexpr void digitize(D * dest, bool src)
	{
		*dest = src;
	}
};


template <typename T, typename = void>
struct _is_unscoped_enum
	: std::false_type
{
};

template <typename T>
using is_unscoped_enum = _is_unscoped_enum<T>;

template <typename T>
struct _is_unscoped_enum<T, typename std::enable_if<std::is_enum<T>::value>::type>
	: std::is_convertible<T, typename std::underlying_type<T>::type>
{
};

template <typename T>
struct _span
{
	T & back() { return ptr[size - 1]; }

	T * ptr;
	size_t size;
};

template <typename Traits, typename Alloc = std::allocator<typename Traits::digit_type>>
struct bigint
{
	using _digit = typename Traits::digit_type;

	bigint()
		: _digits{ 0 }
	{
	}

	template <_digit... dn>
	bigint(cint<_digit, dn...>)
		: _digits{ dn... }
	{
	}

	template <typename T,
		typename std::enable_if<std::is_integral<T>::value, int>::type = 1>
	bigint(T const & v)
	{
		using digitizer = _digitizer<_digit, T>;
		_digits.resize(digitizer::needed_digits);
		digitizer::digitize(_digits.data(), v);
	}

	template <
		typename T,
		typename std::enable_if<is_unscoped_enum<T>::value, int>::type = 1>
	bigint(T const & v)
		: bigint(typename std::underlying_type<T>::type(v))
	{
	}

	/*template <
		typename T,
		typename std::enable_if<std::is_integral<T>::value, int>::type = 1>
	explicit operator T() const
	{
		return 0;
	}*/

	friend bigint operator+(bigint const & lhs, bigint const & rhs)
	{
		if (lhs._digits.size() < rhs._digits.size())
			return rhs + lhs;

		bigint r = lhs;
		auto dest = r._get_span();
		auto src = rhs._get_span();

		_digit carry = _traits::addn(dest.ptr, src.ptr, src.size);
		carry += _traits::sext(src.back());
		carry = _traits::adds(dest.ptr + src.size, carry, dest.size - src.size);
		carry += _traits::sext(lhs._get_span().back());

		if (carry != _traits::sext(dest.back()))
			r._digits.push_back(carry);

		return r;
	}

	friend bigint operator-(bigint const & lhs, bigint const & rhs)
	{
		// TODO: this is not the most efficient way
		return lhs + (-rhs);
	}

	friend bigint operator*(bigint const & lhs, bigint const & rhs)
	{
		auto ls = lhs._get_span();
		auto rs = rhs._get_span();

		size_t r_size = ls.size + rs.size;
		if (r_size < ls.size)
			throw std::length_error("the number is too large");

		bigint r;
		r._digits.resize(r_size);

		for (size_t i = 0; i != rs.size; ++i)
			r._digits[i + ls.size] = _traits::mul(r._digits.data() + i, ls.ptr, ls.size, rs.ptr[i]);

		if (_traits::is_negative(ls.back()))
			_traits::subn(r._digits.data() + ls.size, rs.ptr, rs.size);
		if (_traits::is_negative(rs.back()))
			_traits::subn(r._digits.data() + rs.size, ls.ptr, ls.size);

		return r;
	}

	friend bigint operator&(bigint lhs, bigint const & rhs)
	{
		lhs &= rhs;
		return lhs;
	}

	friend bigint operator|(bigint lhs, bigint const & rhs)
	{
		lhs |= rhs;
		return lhs;
	}

	friend bigint operator^(bigint lhs, bigint const & rhs)
	{
		lhs ^= rhs;
		return lhs;
	}

	bigint const & operator+() const
	{
		return *this;
	}

	bigint operator-() const
	{
		bigint r = *this;
		auto d = r._get_span();

		for (size_t i = 0; i != d.size; ++i)
			d.ptr[i] = ~d.ptr[i];

		_digit carry = _traits::sext(d.back());
		carry += _traits::adds(d.ptr, 1, d.size);
		if (_traits::sext(d.back()) != carry)
			r._digits.push_back(carry);

		return r;
	}

	bigint operator~() const
	{
		bigint r = *this;
		auto d = r._get_span();

		for (size_t i = 0; i != d.size; ++i)
			d.ptr[i] = ~d.ptr[i];

		return r;
	}

	bigint & operator+=(bigint const & rhs)
	{
		return *this = *this + rhs;
	}

	bigint & operator-=(bigint const & rhs)
	{
		return *this = *this - rhs;
	}

	bigint & operator*=(bigint const & rhs)
	{
		return *this = *this * rhs;
	}

	bigint & operator&=(bigint const & rhs)
	{
		this->_resize(rhs._digits.size());

		_digit const * src = rhs._digits.data();
		_digit const * src_last = src + rhs._digits.size();
		auto src_gen = [&]() {
			if (src == src_last)
				return _traits::sext(src[-1]);
			return *src++;
		};

		for (_digit & dig: _digits)
			dig &= src_gen();
		return *this;
	}

	bigint & operator|=(bigint const & rhs)
	{
		this->_resize(rhs._digits.size());

		_digit const * src = rhs._digits.data();
		_digit const * src_last = src + rhs._digits.size();
		auto src_gen = [&]() {
			if (src == src_last)
				return _traits::sext(src[-1]);
			return *src++;
		};

		for (_digit & dig : _digits)
			dig |= src_gen();
		return *this;
	}

	bigint & operator^=(bigint const & rhs)
	{
		this->_resize(rhs._digits.size());

		_digit const * src = rhs._digits.data();
		_digit const * src_last = src + rhs._digits.size();
		auto src_gen = [&]() {
			if (src == src_last)
				return _traits::sext(src[-1]);
			return *src++;
		};

		for (_digit & dig : _digits)
			dig ^= src_gen();
		return *this;
	}

	friend bool operator==(bigint const & lhs, bigint const & rhs)
	{
		_digit const * lhs_first = lhs._digits.data();
		_digit const * lhs_last = lhs_first + lhs._digits.size();

		_digit const * rhs_first = rhs._digits.data();
		_digit const * rhs_last = rhs_first + rhs._digits.size();

		while (lhs_first != lhs_last && rhs_first != rhs_last)
		{
			if (*lhs_first++ != *rhs_first++)
				return false;
		}

		if (lhs_first != lhs_last)
		{
			_digit s = _cint::sext(rhs_last[-1]);
			while (lhs_first != lhs_last)
			{
				if (*lhs_first++ != s)
					return false;
			}
		}
		else
		{
			_digit s = _cint::sext(lhs_last[-1]);
			while (rhs_first != rhs_last)
			{
				if (*rhs_first++ != s)
					return false;
			}
		}

		return true;
	}

	friend bool operator!=(bigint const & lhs, bigint const & rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(bigint const & lhs, bigint const & rhs)
	{
		// TODO: inefficient, requires allocation
		bigint diff = lhs - rhs;
		return diff._get_span().back() & _cint::digits<_digit>::sign_mask;
	}

	friend bool operator>(bigint const & lhs, bigint const & rhs)
	{
		return rhs < lhs;
	}

	friend bool operator<=(bigint const & lhs, bigint const & rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>=(bigint const & lhs, bigint const & rhs)
	{
		return !(lhs < rhs);
	}

private:
	using _traits = Traits;

	void _resize(size_t size)
	{
		if (_digits.size() >= size)
			return;

		_digits.resize(size, _traits::sext(_digits.back()));
	}

	_span<_digit> _get_span() { return { _digits.data(), _digits.size() }; }
	_span<_digit const> _get_span() const { return { _digits.data(), _digits.size() }; }

	std::vector<_digit> _digits;
};

}
}

#endif // AVAKAR_BIGINT_BIGINT_BIGINT_H
