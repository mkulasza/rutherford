#pragma once

#include <ostream>
#include "fwd.h"

namespace rutherford
{

class Element
{
public:
    virtual ~Element();

    virtual void insert(std::ostream& stream) const = 0;
};

}