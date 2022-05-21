#pragma once

#include "traits.h"
#include "Element.h"

namespace rutherford
{

template<typename T>
class ConstantElement : public Element<ConstantElement<T>>
{
    friend class Element<ConstantElement<T>>;
    
    static_assert(is_numeric_v<T>, "ConstantElement type must be numeric");
public:
    ConstantElement(T aValue) :
        myValue(aValue)
    {
    }

private:
    T myValue;

    void insert(std::ostream& aStream) const
    {
        aStream << myValue;
    }
};

}