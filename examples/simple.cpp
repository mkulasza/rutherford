/*
 * Example illustrating order independent Expression operations.
 *
 * The circuit objects can be constructed and initialized in any order. In this case, the code is structured to first instantiate all of the circuit objects.
 * Next connectivity info is setup. Finally, the circuit objects are initialized with model parameters. A branch with impedance 1 + 10j is connected between
 * a free node and a voltage source (to ground).
 * 
 * While this is a pretty contrived example - objects can be instantiated with model information, connectivity setup could be the last operation, etc. - 
 * but it illustrates that order of operations is irrelevant as long as:
 * (a) objects are created before they are used, which is required of any C++ code and
 * (b) all setup tasks are completed before Expressions are evaluated, which basically means Expressions can't predict the future.
 * 
 * This is one of the main motivations behind this library. Without such flexibility, at some point you need to construct a dependency tree to figure out who
 * needs to be constructed first. Or your code needs to know ahead of time which objects need to be constructed first. Implementing such requirements is not
 * difficult if restrict yourself to a rigid component structure. However, there are many unique components in a general purpose simulator and it is almost
 * impossible to predict what needs future components will have.
 * 
 * What the flexibility shown below offers is freedom from any concerns regarding order of operations. An ordering does not need to be baked into the code
 * and dependency trees are not required.
 */
#include <iostream>
#include "expressions.h"

using namespace rutherford;
using namespace std::complex_literals;

class Node
{
public:
    void initialize(const std::string& name)
    {
        v = complex_variable("v(" + name + ")");
    }

    void initialize(complex_t voltage)
    {
        v = voltage;
    }

    Expression getVoltage() const
    {
        return v;
    }

private:
    Expression v;
};

class Branch
{
public:
    void initialize(complex_t z)
    {
        i = (vi - vj)/z;
    }

    void setFromVoltage(const Expression& v)
    {
        vi = v;
    }

    void setToVoltage(const Expression& v)
    {
        vj = v;
    }

    Expression getCurrent() const
    {
        return i;
    }

private:
    Expression vi, vj, i;
};

int main()
{
    auto b1 = Branch();
    auto n1 = Node();
    auto n2 = Node();

    b1.setFromVoltage(n1.getVoltage());
    b1.setToVoltage(n2.getVoltage());

    b1.initialize(1. + 10i);
    n1.initialize("1");
    n2.initialize(1.);

    std::cout << b1.getCurrent() << std::endl;

    return 0;
}