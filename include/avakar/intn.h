#ifndef AVAKAR_INTN_h
#define AVAKAR_INTN_h

#include "../../src/intn/intn.h"
#include "../../src/traits.h"
#include <cstddef>

namespace avakar {

template <size_t w>
using intn_t = _intn::intn<w, true, _bigint::bigint_traits>;

template <size_t w>
using uintn_t = _intn::intn<w, false, _bigint::bigint_traits>;

using int128_t = intn_t<128>;
using int256_t = intn_t<256>;
using int512_t = intn_t<512>;

using uint128_t = uintn_t<128>;
using uint256_t = uintn_t<256>;
using uint512_t = uintn_t<512>;

}

#endif // AVAKAR_INTN_h
