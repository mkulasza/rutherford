#include "MultiplicationElement.h"

namespace rutherford
{

void MultiplicationElement::insert(std::ostream& stream) const
{
    stream << left << " * " << right;
}

}