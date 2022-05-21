#pragma once

#include "Element.h"
#include "Expression.h"

namespace rutherford
{

template<bool Add>
class AdditionElement : public Element<AdditionElement<Add>>
{
    friend class Element<AdditionElement<Add>>;
    
public:
    template<typename L, typename R>
    AdditionElement(L&& aLeft, R&& aRight) :
        myLeft(std::forward<L>(aLeft)),
        myRight(std::forward<R>(aRight))
    {
    }

private:
    Expression myLeft, myRight;

    void insert(std::ostream& aStream) const
    {
        aStream << "(" << myLeft;
        if(Add)
            aStream << " + ";
        else
            aStream << " - ";
        aStream << myRight << ")";
    }
};

}