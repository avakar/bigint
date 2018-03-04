#ifndef AVAKAR_CINT_H
#define AVAKAR_CINT_H

#include "../../src/cint/cint.h"
#include "../../src/cint/operators.h"
#include "../../src/cint/strtoc.h"
#include "../../src/traits.h"

namespace avakar {

using _digit = typename _bigint::bigint_traits::digit_type;

template <typename D, D d0, D... dn>
using basic_cint = _cint::cint<D, d0, dn...>;

template <_digit d0, _digit... dn>
using cint = basic_cint<_digit, d0, dn...>;

namespace literals {

template <char... cn>
_cint::parse_literal_t<_digit, cn...> operator""_z() { return {}; }

}

}

#endif // AVAKAR_CINT_H
