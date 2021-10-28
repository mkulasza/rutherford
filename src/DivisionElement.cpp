#include "DivisionElement.h"

namespace rutherford
{

void DivisionElement::insert(std::ostream& stream) const
{
    stream << numerator << " / " << denominator;
}

}