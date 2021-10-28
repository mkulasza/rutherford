#pragma once

#include "traits.h"
#include "Element.h"

namespace rutherford
{

template<typename T>
class ConstantElement : public Element
{
    static_assert(is_numeric_v<T>, "ConstantElement type must be numeric");
public:
    ConstantElement(T value) :
        value(value)
    {
    }

    void insert(std::ostream& stream) const
    {
        stream << value;
    }

private:
    T value;
};

}