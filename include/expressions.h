/*
 * Implementation file for Expression operators.
 * These appear here to avoid circular imports of any operators that have Expression instances as member variables.
 */
#pragma once

#include "Expression.h"
#include "AdditionElement.h"
#include "MultiplicationElement.h"
#include "DivisionElement.h"
#include "RealImagElement.h"

namespace rutherford
{

template<typename T>
Expression& Expression::operator+=(T&& other)
{
    // std::move(*this) strange but ok. Overloaded move constructor gives *root to a temporary Expression instance.
    // Root is immediately reassigned to the AdditionElement
    *root = std::make_unique<AdditionElement<true>>(std::move(*this), std::forward<T>(other));
    return *this;
}

template<typename T>
Expression& Expression::operator-=(T&& other)
{
    *root = std::make_unique<AdditionElement<false>>(std::move(*this), std::forward<T>(other));
    return *this;
}

template<typename L, typename R, expression_enable_t<L, R>>
Expression operator+(L&& left, R&& right)
{
    return Expression::create<AdditionElement<true>>(std::forward<L>(left), std::forward<R>(right));
}

template<typename L, typename R, expression_enable_t<L, R>>
Expression operator-(L&& left, R&& right)
{
    return Expression::create<AdditionElement<false>>(std::forward<L>(left), std::forward<R>(right));
}

template<typename L, typename R, expression_enable_t<L, R>>
Expression operator*(L&& left, R&& right)
{
    return Expression::create<MultiplicationElement>(std::forward<L>(left), std::forward<R>(right));
}

template<typename L, typename R, expression_enable_t<L, R>>
Expression operator/(L&& left, R&& right)
{
    return Expression::create<DivisionElement>(std::forward<L>(left), std::forward<R>(right));
}

template<typename E, expression_enable_t<E>>
Expression real(E&& expression)
{
    return Expression::create<RealImagElement<true>>(std::forward<E>(expression));
}

template<typename E, expression_enable_t<E>>
Expression imag(E&& expression)
{
    return Expression::create<RealImagElement<false>>(std::forward<E>(expression));
}

}