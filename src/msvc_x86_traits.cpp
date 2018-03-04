#include "msvc_x86_traits.h"
#include <intrin.h>
#include <cassert>
using namespace avakar::_bigint;

uint32_t msvc_x86_traits::sext(uint32_t d)
{
	return (uint32_t)((int32_t)d >> 31);
}

bool msvc_x86_traits::is_negative(uint32_t d)
{
	return d & 0x80000000;
}

uint32_t msvc_x86_traits::addn(uint32_t * dest, uint32_t const * src, size_t len)
{
	unsigned char carry = 0;
	for (size_t i = 0; i != len; ++i)
		carry = _addcarry_u32(carry, dest[i], src[i], &dest[i]);
	return carry;
}

uint32_t msvc_x86_traits::subn(uint32_t * dest, uint32_t const * src, size_t len)
{
	unsigned char borrow = 0;
	for (size_t i = 0; i != len; ++i)
		borrow = _subborrow_u32(borrow, dest[i], src[i], &dest[i]);
	return borrow;
}

uint32_t msvc_x86_traits::adds(uint32_t * dest, uint32_t src, size_t dest_len)
{
	for (size_t i = 0; src && i != dest_len; ++i)
	{
		unsigned char carry = _addcarry_u32(0, dest[i], src, &dest[i]);
		src = sext(src) + carry;
	}

	return src;
}

uint32_t msvc_x86_traits::mul(uint32_t * dest, uint32_t const * a, size_t a_len, uint32_t b)
{
	uint32_t carry = 0;
	for (size_t i = 0; i != a_len; ++i)
	{
		uint64_t r = __emulu(a[i], b);

		unsigned char c = _addcarry_u32(0, dest[i], (uint32_t)r, &dest[i]);
		c += _addcarry_u32(0, dest[i], carry, &dest[i]);

		carry = (r >> 32) + c;
	}

	return carry;
}
