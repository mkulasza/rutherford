#include "MultiplicationElement.h"

namespace rutherford
{

void MultiplicationElement::insert(std::ostream& aStream) const
{
    aStream << myLeft << " * " << myRight;
}

}