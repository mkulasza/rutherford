#pragma once

#include "Element.h"
#include "Expression.h"

namespace rutherford
{

class DivisionElement : public Element
{
public:
    template<typename N, typename D>
    DivisionElement(N&& numerator, D&& denominator) :
        numerator(std::forward<N>(numerator)),
        denominator(std::forward<D>(denominator))
    {
    }

    void insert(std::ostream& stream) const;

private:
    Expression numerator, denominator;
};

}