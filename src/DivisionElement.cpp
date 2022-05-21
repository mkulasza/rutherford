#include "DivisionElement.h"

namespace rutherford
{

void DivisionElement::insert(std::ostream& aStream) const
{
    aStream << myNumerator << " / " << myDenominator;
}

}