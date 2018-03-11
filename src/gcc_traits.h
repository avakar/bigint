#ifndef AVAKAR_BIGINT_GCC_TRAITS_H
#define AVAKAR_BIGINT_GCC_TRAITS_H

#include <stdint.h>
#include <stdlib.h>

namespace avakar {
namespace _bigint {

struct gcc_traits
{
	using digit_type = uint32_t;

	static uint32_t sext(uint32_t d);
	static bool is_negative(uint32_t d);
	static uint32_t addn(uint32_t * dest, uint32_t const * src, size_t len);
	static uint32_t subn(uint32_t * dest, uint32_t const * src, size_t len);
	static uint32_t adds(uint32_t * dest, uint32_t src, size_t dest_len);
	static uint32_t mul(uint32_t * dest, uint32_t const * a, size_t a_len, uint32_t b);
};

}
}

#endif // AVAKAR_BIGINT_GCC_TRAITS_H
