#pragma once

#include <type_traits>
#include "fwd.h"

namespace rutherford
{

template<typename T>
struct _is_complex : public std::false_type
{
};

template<typename T>
struct _is_complex<std::complex<T> > : public std::true_type
{
};

template<typename T>
struct is_complex : public _is_complex<std::remove_cvref_t<T> >
{
};

template<typename T>
inline constexpr bool is_complex_v = is_complex<T>::value;

template<typename T>
struct is_numeric : std::disjunction<std::is_arithmetic<T>, is_complex<T> >
{
};

template<typename T>
inline constexpr bool is_numeric_v = is_numeric<T>::value;

template<typename T>
using enable_if_numeric_t = typename std::enable_if<is_numeric_v<T>, int>::type;

template<typename T>
struct is_expression : std::is_same<std::remove_cvref_t<T>, Expression>
{
};

template<typename T>
inline constexpr bool is_expression_v = is_expression<T>::value;

template<typename T>
using enable_if_expression_t = typename std::enable_if<is_expression_v<T>, int>::type;

template<typename... T>
inline constexpr bool valid_for_expression_v = std::conjunction_v<std::conjunction<std::disjunction<is_expression<T>, is_numeric<T> >...>, std::disjunction<is_expression<T>...> >;

template<typename... T>
using expression_enable_t = typename std::enable_if<valid_for_expression_v<T...>, int>::type;

}