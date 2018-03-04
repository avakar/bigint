#include "generic_traits.h"
#include <assert.h>
using namespace avakar;

bool generic_traits::add(uint32_t * r, uint32_t const * a, uint32_t const * b, size_t n)
{
	assert(n >= 1);

	r[0] = a[0] + b[0];

	bool carry = r[0] < b[0];
	for (size_t i = 1; i != n; ++i)
	{
		r[i] = a[i] + b[i];
		bool c1 = r[i] < b[i];
		r[i] += carry;
		carry = c1 || (carry && r[i] == 0);
	}

	return carry;
}

bool generic_traits::add(uint32_t * r, uint32_t b, size_t n)
{
	assert(n >= 1);

	r[0] += b;

	bool carry = r[0] < b;
	for (size_t i = 1; carry && i != n; ++i)
		carry = ++r[i] == 0;

	return carry;
}

uint32_t generic_traits::muladd(uint32_t * r, uint32_t const * a, uint32_t b, size_t n)
{
	uint32_t carry = 0;
	for (size_t i = 0; i != n; ++i)
	{
		uint64_t c = (uint64_t)a * b + carry;

		r[i] += (uint32_t)c;
		carry = c >> 32;
	}

	return carry;
}
