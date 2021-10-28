#pragma once

#include "Element.h"
#include "Expression.h"

namespace rutherford
{

template<bool Real>
class RealImagElement : public Element
{
public:
    template<typename T>
    RealImagElement(T&& child) :
        child(std::forward<T>(child))
    {
    }

    void insert(std::ostream& stream) const
    {
        if(Real)
            stream << "Re{" << child << "}";
        else
            stream << "Im{" << child << "}";
    }

private:
    Expression child;
};

}