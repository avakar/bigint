#ifndef AVAKAR_BIGINT_H
#define AVAKAR_BIGINT_H

#include "../../src/bigint/bigint.h"
#include "../../src/traits.h"

namespace avakar {

template <typename Traits, typename Alloc = std::allocator<typename Traits::digit_type>>
using basic_bigint = _bigint::bigint<Traits, Alloc>;

using bigint = basic_bigint<_bigint::bigint_traits>;

}

#endif // AVAKAR_BIGINT_H
