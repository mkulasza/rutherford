#pragma once

#include "Element.h"
#include "Expression.h"

namespace rutherford
{

class MultiplicationElement : public Element
{
public:
    template<typename L, typename R>
    MultiplicationElement(L&& left, R&& right) :
        left(std::forward<L>(left)),
        right(std::forward<R>(right))
    {
    }

    void insert(std::ostream& stream) const;

private:
    Expression left, right;
};

}