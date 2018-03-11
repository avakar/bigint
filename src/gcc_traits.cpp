#include "gcc_traits.h"
#include <cassert>
using namespace avakar::_bigint;

uint32_t gcc_traits::sext(uint32_t d)
{
	return (uint32_t)((int32_t)d >> 31);
}

bool gcc_traits::is_negative(uint32_t d)
{
	return d & 0x80000000;
}

uint32_t gcc_traits::addn(uint32_t * dest, uint32_t const * src, size_t len)
{
	unsigned char carry = 0;
	for (size_t i = 0; i != len; ++i)
	{
		uint32_t tmp;
		carry = __builtin_add_overflow(dest[i], carry, &tmp);
		carry |= __builtin_add_overflow(tmp, src[i], &dest[i]);
	}
	return carry;
}

uint32_t gcc_traits::subn(uint32_t * dest, uint32_t const * src, size_t len)
{
	unsigned char borrow = 0;
	for (size_t i = 0; i != len; ++i)
	{
		uint32_t tmp;
		borrow = __builtin_sub_overflow(dest[i], borrow, &tmp);
		borrow |= __builtin_sub_overflow(tmp, src[i], &dest[i]);
	}
	return borrow;
}

uint32_t gcc_traits::adds(uint32_t * dest, uint32_t src, size_t dest_len)
{
	for (size_t i = 0; src && i != dest_len; ++i)
	{
		unsigned char carry = __builtin_add_overflow(dest[i], src, &dest[i]);
		src = sext(src) + carry;
	}

	return src;
}

uint32_t gcc_traits::mul(uint32_t * dest, uint32_t const * a, size_t a_len, uint32_t b)
{
	uint32_t carry = 0;
	for (size_t i = 0; i != a_len; ++i)
	{
		uint64_t r;
		__builtin_mul_overflow(a[i], b, &r);

		uint32_t tmp;
		unsigned char c = __builtin_add_overflow(dest[i], (uint32_t)r, &tmp);
		c += __builtin_add_overflow(tmp, carry, &dest[i]);

		carry = (r >> 32) + c;
	}

	return carry;
}
