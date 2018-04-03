#ifndef AVAKAR_BIGINT_GENERIC_TRAITS_H
#define AVAKAR_BIGINT_GENERIC_TRAITS_H

#include "cint/digits.h"

namespace avakar {
namespace _bigint {

template <typename D, typename DD>
struct generic_traits
{
	using digit_type = D;
	static constexpr digit_type sign_mask = digit_type(1) << (std::numeric_limits<digit_type>::digits - 1);

	static digit_type sext(digit_type d)
	{
		return is_negative(d)? std::numeric_limits<digit_type>::max(): 0;
	}

	static bool is_negative(digit_type d)
	{
		return d & sign_mask;
	}

	static digit_type addn(digit_type * dest, digit_type const * src, size_t len)
	{
		digit_type carry = 0;
		for (size_t i = 0; i != len; ++i)
		{
			dest[i] += carry;
			carry = (dest[i] < carry);
			dest[i] += src[i];
			carry |= (dest[i] < src[i]);
		}

		return carry;
	}

	static digit_type subn(digit_type * dest, digit_type const * src, size_t len)
	{
		digit_type borrow = 0;
		for (size_t i = 0; i != len; ++i)
		{
			digit_type new_borrow = dest[i] < borrow;
			dest[i] -= borrow;
			new_borrow |= dest[i] < src[i];
			dest[i] -= src[i];

			borrow = new_borrow;
		}

		return borrow;
	}

	static digit_type adds(digit_type * dest, digit_type src, size_t dest_len)
	{
		for (size_t i = 0; src && i != dest_len; ++i)
		{
			dest[i] += src;
			src = sext(src) + (dest[i] < src);
		}

		return src;
	}

	static digit_type mul(digit_type * dest, digit_type const * a, size_t a_len, digit_type b)
	{
		digit_type carry = 0;
		for (size_t i = 0; i != a_len; ++i)
		{
			DD r = (DD)a[i] * b;

			digit_type lo = (digit_type)r;

			dest[i] += lo;
			digit_type new_carry = (dest[i] < lo);
			dest[i] += carry;
			new_carry += (dest[i] < carry);

			carry = new_carry + (r >> std::numeric_limits<digit_type>::digits);
		}

		return carry;
	}

	static digit_type cmpn(digit_type const * lhs, digit_type const * rhs, size_t len)
	{
		digit_type borrow = 0;
		for (size_t i = 0; i != len; ++i)
			borrow = (lhs[i] < borrow) | (lhs[i] - borrow < rhs[i]);
		return borrow;
	}
};

}
}

#endif // AVAKAR_BIGINT_GENERIC_TRAITS_H
