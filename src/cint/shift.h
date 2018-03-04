#ifndef AVAKAR_BIGINT_CINT_SHIFT_H
#define AVAKAR_BIGINT_CINT_SHIFT_H

#include "digits.h"
#include "add.h"
#include "compare.h"
#include "traits.h"
#include "trim.h"
#include "prepend.h"
#include "cint.h"
#include <type_traits>

namespace avakar {
namespace _cint {

template <typename A, typename S, typename = void>
struct shift_left;

template <typename A, typename S>
using shift_left_t = trim_t<typename shift_left<A, S>::type>;

template <typename A, typename S>
using shift_right_t = shift_left_t<A, neg_t<S>>;


template <typename A, typename A::digit s, typename A::digit c>
struct _shl
{
	using _dig = typename A::digit;
	static constexpr auto _w = digits<_dig>::width;
	static_assert(0 < s && s < _w, "XXX");

	using type = prepend_t<
		typename _shl<tail_t<A>, s, (A::head >> (_w - s))>::type,
		_dig(A::head << s) | c
	>;
};

template <typename D, D d0, D s, D c>
struct _shl<cint<D, d0>, s, c>
{
	static constexpr D _d1 = sext(d0);
	static constexpr D _w = digits<D>::width;
	static_assert(0 < s && s < _w, "XXX");

	using type = cint<D, D(d0 << s) | c, D(_d1 << s) | (d0 >> (_w - s))>;
};

template <typename A, typename A::digit s>
struct _shr
{
	static constexpr auto _w = digits<D>::width;
	static_assert(0 < s && s < _w, "XXX");

	using _r = _shr<tail_t<A>, s>;

	using type = prepend_t<
		typename _r::type,
		(A::head >> s) | _r::cout
	>;
};

template <typename D, D d0, D s>
struct _shr<cint<D, d0>, s>
{
	static constexpr D _d1 = sext(d0);
	static constexpr D _w = digits<D>::width;
	static_assert(0 < s && s < _w, "XXX");

	using type = cint<D, (d0 >> s) | _d1 << (_w - s)>;
	static constexpr D cout = D(d0 << (_w - s));
};

template <typename A, typename S>
struct shift_left<A, S, typename std::enable_if<!is_less<S, typename A::digit_width>::value>::type>
{
	using type = typename shift_left<
		prepend_t<A, 0>,
		sub_t<S, typename A::digit_width>
		>::type;
};

template <typename A, typename S>
struct shift_left<A, S, typename std::enable_if<is_positive<S>::value && is_less<S, typename A::digit_width>::value>::type>
	: _shl<A, S::head, 0>
{
};

template <typename A, typename S>
struct shift_left<A, S, typename std::enable_if<is_zero<S>::value>::type>
{
	using type = A;
};

template <typename A, typename S>
struct shift_left<A, S, typename std::enable_if<is_less<neg_t<typename A::digit_width>, S>::value && is_negative<S>::value>::type>
	: _shr<A, neg_t<S>::head>
{
};

template <typename D, D d0, D d1, D... dn, typename S>
struct shift_left<cint<D, d0, d1, dn...>, S, typename std::enable_if<!is_less<neg_t<cwidth_t<D>>, S>::value>::type>
{
	using type = typename shift_left<
		cint<D, d1, dn...>,
		add_t<S, cwidth_t<D>>
	>::type;
};

template <typename D, D d0, typename S>
struct shift_left<cint<D, d0>, S, typename std::enable_if<!is_less<neg_t<cwidth_t<D>>, S>::value>::type>
{
	using type = cint<D, sext(d0)>;
};

}
}

#endif // AVAKAR_BIGINT_CINT_SHIFT_H
