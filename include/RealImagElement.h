#pragma once

#include "Element.h"
#include "Expression.h"

namespace rutherford
{

template<bool Real>
class RealImagElement : public Element<RealImagElement<Real>>
{
    friend class Element<RealImagElement<Real>>;

public:
    template<typename T>
    RealImagElement(T&& aChild) :
        myChild(std::forward<T>(aChild))
    {
    }
    
private:
    Expression myChild;

    void insert(std::ostream& aStream) const
    {
        if(Real)
            aStream << "Re{" << myChild << "}";
        else
            aStream << "Im{" << myChild << "}";
    }
};

}