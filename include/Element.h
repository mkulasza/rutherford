#pragma once

#include <ostream>
#include "fwd.h"

namespace rutherford
{

template<typename T>
class Element
{
public:
    virtual ~Element()
    {
    }

private:
    void insert(std::ostream& aStream) const
    {
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& aStream, const Element<T>* anElement)
{
    static_cast<T*>(anElement)->insert(aStream);
}

}