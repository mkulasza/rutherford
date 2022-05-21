#pragma once

#include "Element.h"

namespace rutherford
{

template<bool Complex>
class VariableElement : public Element<VariableElement<Complex>>
{
    friend class Element<VariableElement<Complex>>;

public:
    VariableElement(const std::string& aName) :
        myName(aName)
    {            
    }
    
    void insert(std::ostream& aStream) const
    {
        aStream << myName;
    }

private:
    std::string myName;
};

}