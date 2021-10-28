#pragma once

#include "Element.h"

namespace rutherford
{

template<bool Complex>
class VariableElement : public Element
{
public:
    VariableElement(const std::string& name) :
        name(name)
    {            
    }
    
    void insert(std::ostream& stream) const
    {
        stream << name;
    }

private:
    std::string name;
};

}