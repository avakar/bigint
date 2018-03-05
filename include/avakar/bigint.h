#ifndef AVAKAR_BIGINT_H
#define AVAKAR_BIGINT_H

#include "../../src/bigint/bigint.h"
#include "../../src/cint/strtoc.h"
#include "../../src/cint/operators.h"
#include "../../src/traits.h"

namespace avakar {

template <typename Traits, typename Alloc = std::allocator<typename Traits::digit_type>>
using basic_bigint = _bigint::bigint<Traits, Alloc>;

using bigint = basic_bigint<_bigint::bigint_traits>;

template <char... cn>
_cint::parse_literal_t<typename _bigint::bigint_traits::digit_type, cn...> operator""_z() { return {}; }

}

#endif // AVAKAR_BIGINT_H
