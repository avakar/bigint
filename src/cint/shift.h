#ifndef AVAKAR_BIGINT_CINT_SHIFT_H
#define AVAKAR_BIGINT_CINT_SHIFT_H

#include "digits.h"
#include "add.h"
#include "compare.h"
#include "trim.h"
#include "prepend.h"
#include <type_traits>

namespace avakar {
namespace _cint {

template <typename A, typename S, typename = void>
struct _shift_left;

template <typename A, typename S>
using shift_left_t = trim_t<typename _shift_left<A, S, typename std::enable_if<is_cint<A>::value && is_cint<S>::value>::type>::type>;

template <typename A, typename S>
using shift_right_t = shift_left_t<A, neg_t<S>>;


template <typename A, digit_t s, digit_t c>
struct _shl
{
	static_assert(0 < s && s < digit_width, "XXX");

	using type = prepend_t<
		typename _shl<tail_t<A>, s, (head<A>::value >> (digit_width - s))>::type,
		digit_t(head<A>::value << s) | c
	>;
};

template <digit_t d0, digit_t s, digit_t c>
struct _shl<cint<d0>, s, c>
{
	static constexpr digit_t _d1 = sext(d0);
	static_assert(0 < s && s < digit_width, "XXX");

	using type = cint<digit_t(d0 << s) | c, digit_t(_d1 << s) | (d0 >> (digit_width - s))>;
};

template <typename A, digit_t s>
struct _shr
{
	static_assert(0 < s && s < digit_width, "XXX");

	using _r = _shr<tail_t<A>, s>;

	using type = prepend_t<
		typename _r::type,
		(head<A>::value >> s) | _r::cout
	>;
	static constexpr digit_t cout = digit_t(head<A>::value << (digit_width - s));
};

template <digit_t d0, digit_t s>
struct _shr<cint<d0>, s>
{
	static_assert(0 < s && s < digit_width, "XXX");

	using type = cint<(d0 >> s) | sext(d0) << (digit_width - s)>;
	static constexpr digit_t cout = digit_t(d0 << (digit_width - s));
};

template <typename A, typename S>
struct _shift_left<A, S, typename std::enable_if<!is_less<S, digit_width_t>::value>::type>
{
	using type = typename _shift_left<
		prepend_t<A, 0>,
		sub_t<S, digit_width_t>
		>::type;
};

template <typename A, typename S>
struct _shift_left<A, S, typename std::enable_if<is_positive<S>::value && is_less<S, digit_width_t>::value>::type>
	: _shl<A, head<S>::value, 0>
{
};

template <typename A, typename S>
struct _shift_left<A, S, typename std::enable_if<is_zero<S>::value>::type>
{
	using type = A;
};

template <typename A, typename S>
struct _shift_left<A, S, typename std::enable_if<is_less<neg_t<digit_width_t>, S>::value && is_negative<S>::value>::type>
	: _shr<A, head<neg_t<S>>::value>
{
};

template <digit_t d0, digit_t d1, digit_t... dn, typename S>
struct _shift_left<cint<d0, d1, dn...>, S, typename std::enable_if<!is_less<neg_t<digit_width_t>, S>::value>::type>
{
	using type = typename _shift_left<
		cint<d1, dn...>,
		add_t<S, digit_width_t>
	>::type;
};

template <digit_t d0, typename S>
struct _shift_left<cint<d0>, S, typename std::enable_if<!is_less<neg_t<digit_width_t>, S>::value>::type>
{
	using type = cint<sext(d0)>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_SHIFT_H
