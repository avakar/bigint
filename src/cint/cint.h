#ifndef AVAKAR_BIGINT_CINT_CINT_H
#define AVAKAR_BIGINT_CINT_CINT_H

#include "compare.h"
#include "bitwise.h"
#include "shift.h"
#include "add.h"
#include "mul.h"
#include "fwd.h"

namespace avakar {
namespace _cint {

template <typename D, D d0, D... dn>
struct cint
{
	constexpr explicit operator bool() const
	{
		return !is_zero<cint<D, d0, dn...>>::value;
	}
};

template <typename A>
constexpr trim_t<A> operator+(A) { return {}; }

template <typename A>
constexpr neg_t<A> operator-(A) { return {}; }

template <typename A>
constexpr com_t<A> operator~(A) { return {}; }

template <typename A, typename B>
constexpr add_t<A, B> operator+(A, B) { return {}; }

template <typename A, typename B>
constexpr sub_t<A, B> operator-(A, B) { return {}; }

template <typename A, typename B>
constexpr mul_t<A, B> operator*(A, B) { return {}; }

template <typename A, typename B>
constexpr shift_left_t<A, B> operator<<(A, B) { return {}; }

template <typename A, typename B>
constexpr shift_right_t<A, B> operator>>(A, B) { return {}; }

template <typename A, typename B>
constexpr bitwise_and_t<A, B> operator&(A, B) { return {}; }

template <typename A, typename B>
constexpr bitwise_or_t<A, B> operator|(A, B) { return {}; }

template <typename A, typename B>
constexpr bitwise_xor_t<A, B> operator^(A, B) { return {}; }

template <typename D, D... an, D... bn>
constexpr bool operator==(cint<D, an...>, cint<D, bn...>) { return is_equal<cint<D, an...>, cint<D, bn...>>::value; }

template <typename D, D... an, D... bn>
constexpr bool operator!=(cint<D, an...>, cint<D, bn...>) { return !is_equal<cint<D, an...>, cint<D, bn...>>::value; }

template <typename D, D... an, D... bn>
constexpr bool operator<(cint<D, an...>, cint<D, bn...>) { return is_less<cint<D, an...>, cint<D, bn...>>::value; }

template <typename D, D... an, D... bn>
constexpr bool operator>(cint<D, an...>, cint<D, bn...>) { return is_less<cint<D, bn...>, cint<D, an...>>::value; }

template <typename D, D... an, D... bn>
constexpr bool operator<=(cint<D, an...>, cint<D, bn...>) { return !is_less<cint<D, bn...>, cint<D, an...>>::value; }

template <typename D, D... an, D... bn>
constexpr bool operator>=(cint<D, an...>, cint<D, bn...>) { return !is_less<cint<D, an...>, cint<D, bn...>>::value; }

}
}

#endif // AVAKAR_BIGINT_CINT_CINT_H
