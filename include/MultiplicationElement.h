#pragma once

#include "Element.h"
#include "Expression.h"

namespace rutherford
{

class MultiplicationElement : public Element<MultiplicationElement>
{
    friend class Element<MultiplicationElement>;

public:
    template<typename L, typename R>
    MultiplicationElement(L&& aLeft, R&& aRight) :
        myLeft(std::forward<L>(aLeft)),
        myRight(std::forward<R>(aRight))
    {
    }

private:
    Expression myLeft, myRight;

    void insert(std::ostream& aStream) const;
};

}