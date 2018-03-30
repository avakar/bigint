#ifndef AVAKAR_BIGINT_CINT_STRTOC_H
#define AVAKAR_BIGINT_CINT_STRTOC_H

#include "mul.h"
#include "add.h"

namespace avakar {
namespace _cint {

template <char... cn>
struct parse_literal;

template <char... cn>
using parse_literal_t = typename parse_literal<cn...>::type;


template <digit_t b, typename A, char... cn>
struct _strtoc;

template <digit_t b, typename A, char c0, char... cn>
struct _strtoc<b, A, c0, cn...>
{
	static constexpr digit_t _value =
		'0' <= c0 && c0 <= '9' ? c0 - '0' :
		'A' <= c0 && c0 <= 'F' ? c0 - 'A' + 10 :
		c0 - 'a' + 10;

	using _next = add_t<
		mul_t<A, cint<b>>,
		cint<_value>
		>;

	using type = typename _strtoc<b, _next, cn...>::type;
};

template <digit_t b, typename A>
struct _strtoc<b, A>
{
	using type = A;
};

template <digit_t b, typename A, char... cn>
struct _strtoc<b, A, '\'', cn...>
	: _strtoc<b, A, cn...>
{
};

template <char... cn>
struct parse_literal
	: _strtoc<10, cint<0>, cn...>
{
};

template <char... cn>
struct parse_literal<'0', 'x', cn...>
	: _strtoc<16, cint<0>, cn...>
{
};

template <char... cn>
struct parse_literal<'0', 'X', cn...>
	: _strtoc<16, cint<0>, cn...>
{
};

template <char... cn>
struct parse_literal<'0', 'b', cn...>
	: _strtoc<2, cint<0>, cn...>
{
};

template <char... cn>
struct parse_literal<'0', 'B', cn...>
	: _strtoc<2, cint<0>, cn...>
{
};

template <char... cn>
struct parse_literal<'0', cn...>
	: _strtoc<8, cint<0>, cn...>
{
};

}
}

#endif //AVAKAR_BIGINT_CINT_STRTOC_H
