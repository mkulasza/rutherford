#pragma once

#include "Element.h"
#include "Expression.h"

namespace rutherford
{

class DivisionElement : public Element<DivisionElement>
{
    friend class Element<DivisionElement>;

public:
    template<typename N, typename D>
    DivisionElement(N&& aNumerator, D&& aDenominator) :
        myNumerator(std::forward<N>(aNumerator)),
        myDenominator(std::forward<D>(aDenominator))
    {
    }

private:
    Expression myNumerator, myDenominator;

    void insert(std::ostream& aStream) const;
};

}