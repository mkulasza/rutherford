/*
 * The combination of the Element and Expression classes is key to order-independent Expressions.
 *
 * The Expression class uses copy and move operations to make code feel natural when working with its instances.
 * (1) Copy is a "view" operation. When y = x is invoked, y views x. Changes to x are propogated to y, but changes to y don't affect x. This requirement
 *      ensures implicitly chained copies do not introduce undesired changes earlier up the chain. For example, y = x and z = y implicitly creates z = x.
 *      Changes to z should not affect x, even if some logic determines that changes to z can affect y. It protects Expression ownership.
 * (2) Move steals logic but also needs to propogate those changes to downstream views. This requirement ensures operations are order independent. The
 *      operation y = 3*sin(x) should not produce a view of a multiplication element. It should own the multiplication element logic. However, if z = y
 *      was executed before this operation, when z is evaluated now it should produce 3*sin(x).
 * 
 * A double pointer system was used in the Expression class to implement the above logic. The outer pointer is a std::shared_ptr instance. This instance
 * is created upon construction of the Expression and never changes for the life of the instance. This is critical to the second requirement listed above.
 * Items viewing the Expression will automatically pick up on changes since this address does not change. A shared pointer must be used to satisfy the
 * first requirement. When a copy is created of an Expression, the copy receives its own unique std::shared_ptr memory space which it fills with a
 * ViewerElement. The ViewerElement instance is given a copy of the original Expression's shared pointer. This way if the copy is later reassigned, the
 * ViewerElement disappears but the original Expression is left unchanged. The inner pointer is a std::unique_ptr instance. A second pointer is required
 * for the polymorphic properties of the Element class. A unique pointer is sufficient here because the outer shared pointer is the only object requiring
 * ownership of it.
 *
 * All of this indirection could have performance implications. However, the Expression subsystem is meant for construction, not run time performance. A
 * different subsystem will be built to collapse Expression instances into a more suitable form for evaluation.
 */
#pragma once

#include <memory>
#include "traits.h"
#include "Element.h"
#include "ConstantElement.h"

namespace rutherford
{

template<typename L, typename R, expression_enable_t<L, R> = 0> Expression operator+(L&& left, R&& right);
template<typename L, typename R, expression_enable_t<L, R> = 0> Expression operator-(L&& left, R&& right);
template<typename L, typename R, expression_enable_t<L, R> = 0> Expression operator*(L&& left, R&& right);
template<typename L, typename R, expression_enable_t<L, R> = 0> Expression operator/(L&& left, R&& right);
template<typename E, expression_enable_t<E> = 0> Expression real(E&& expression);
template<typename E, expression_enable_t<E> = 0> Expression imag(E&& expression);

Expression real_variable(const std::string& name);
Expression complex_variable(const std::string& name);

class Expression
{
public:
    Expression();
    Expression(const Expression& other);
    Expression(Expression&& other);

    template<typename T, enable_if_numeric_t<T> = 0>
    Expression(T value) :
        Expression()
    {
        *root = std::make_unique<ConstantElement<T>>(value);
    }

    Expression& operator=(const Expression& other);
    Expression& operator=(Expression&& other);

    Expression operator-() const;

    template<typename T> Expression& operator+=(T&& other);
    template<typename T> Expression& operator-=(T&& other);

    friend std::ostream& operator<<(std::ostream& stream, const Expression& expression);

    friend Expression real_variable(const std::string& name);
    friend Expression complex_variable(const std::string& name);

    template<typename L, typename R, expression_enable_t<L, R>> friend Expression operator+(L&& left, R&& right);
    template<typename L, typename R, expression_enable_t<L, R>> friend Expression operator-(L&& left, R&& right);
    template<typename L, typename R, expression_enable_t<L, R>> friend Expression operator*(L&& left, R&& right);
    template<typename L, typename R, expression_enable_t<L, R>> friend Expression operator/(L&& left, R&& right);

    template<typename E, expression_enable_t<E>> friend Expression real(E&& expression);
    template<typename E, expression_enable_t<E>> friend Expression imag(E&& expression);

private:
    typedef std::shared_ptr<std::unique_ptr<const Element>> eptr_t;
    class ViewerElement;

    eptr_t root;

    template<typename T, typename... Args>
    static Expression create(Args&&... args)
    {
        auto expression = Expression();
        *(expression.root) = std::make_unique<T>(std::forward<Args>(args)...);
        return expression;
    }

    static bool isNotNull(eptr_t element);
};

}