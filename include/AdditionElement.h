#pragma once

#include "Element.h"
#include "Expression.h"

namespace rutherford
{

template<bool Add>
class AdditionElement : public Element
{
public:
    template<typename L, typename R>
    AdditionElement(L&& left, R&& right) :
        left(std::forward<L>(left)),
        right(std::forward<R>(right))
    {
    }

    void insert(std::ostream& stream) const
    {
        stream << "(" << left;
        if(Add)
            stream << " + ";
        else
            stream << " - ";
        stream << right << ")";
    }

private:
    Expression left, right;
};

}