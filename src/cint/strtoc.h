#ifndef AVAKAR_BIGINT_CINT_STRTOC_H
#define AVAKAR_BIGINT_CINT_STRTOC_H

#include "mul.h"
#include "add.h"

namespace avakar {
namespace _cint {

template <typename D, char... cn>
struct parse_literal;

template <typename D, char... cn>
using parse_literal_t = typename parse_literal<D, cn...>::type;


template <typename D, D b, typename A, char... cn>
struct _strtoc;

template <typename D, D b, typename A, char c0, char... cn>
struct _strtoc<D, b, A, c0, cn...>
{
	static constexpr D _value =
		'0' <= c0 && c0 <= '9' ? c0 - '0' :
		'A' <= c0 && c0 <= 'F' ? c0 - 'A' + 10 :
		c0 - 'a' + 10;

	using _next = add_t<
		mul_t<A, cint<D, b>>,
		cint<D, _value>
		>;

	using type = typename _strtoc<D, b, _next, cn...>::type;
};

template <typename D, D b, typename A>
struct _strtoc<D, b, A>
{
	using type = A;
};

template <typename D, D b, typename A, char... cn>
struct _strtoc<D, b, A, '\'', cn...>
	: _strtoc<D, b, A, cn...>
{
};

template <typename D, char... cn>
struct parse_literal
	: _strtoc<D, 10, cint<D, 0>, cn...>
{
};

template <typename D, char... cn>
struct parse_literal<D, '0', 'x', cn...>
	: _strtoc<D, 16, cint<D, 0>, cn...>
{
};

template <typename D, char... cn>
struct parse_literal<D, '0', 'X', cn...>
	: _strtoc<D, 16, cint<D, 0>, cn...>
{
};

template <typename D, char... cn>
struct parse_literal<D, '0', 'b', cn...>
	: _strtoc<D, 2, cint<D, 0>, cn...>
{
};

template <typename D, char... cn>
struct parse_literal<D, '0', 'B', cn...>
	: _strtoc<D, 2, cint<D, 0>, cn...>
{
};

template <typename D, char... cn>
struct parse_literal<D, '0', cn...>
	: _strtoc<D, 8, cint<D, 0>, cn...>
{
};

}
}

#endif //AVAKAR_BIGINT_CINT_STRTOC_H
