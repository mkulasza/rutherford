#include "Expression.h"
#include "VariableElement.h"
#include "MultiplicationElement.h"

namespace rutherford
{

class Expression::ViewerElement : public Element
{
public:
    ViewerElement(eptr_t other) :
        view(other)
    {
    }

    void insert(std::ostream& stream) const
    {
        if(isNotNull(view))
            (*view)->insert(stream);
    }

private:
    eptr_t view;

};

Expression::Expression() :
    root(std::make_shared<std::unique_ptr<const Element>>())
{
}

Expression::Expression(const Expression& other) :
    Expression()
{
    *root = std::make_unique<ViewerElement>(other.root);
}

Expression::Expression(Expression&& other) :
    Expression()
{
    *root = std::move(*(other.root));
}

Expression& Expression::operator=(const Expression& other)
{
    if(this != &other)
        *root = std::make_unique<ViewerElement>(other.root);
    return *this;
}

Expression& Expression::operator=(Expression&& other)
{
    if(this != &other)
        *root = std::move(*(other.root));
    return *this;
}

Expression Expression::operator-() const
{
    return Expression::create<MultiplicationElement>(-1, *this);
}

bool Expression::isNotNull(eptr_t root)
{
    return (*root) != nullptr;
}

std::ostream& operator<<(std::ostream& stream, const Expression& expression)
{
    if(Expression::isNotNull(expression.root))
        (*expression.root)->insert(stream);
    return stream;
}

Expression real_variable(const std::string& name)
{
    return Expression::create<VariableElement<false>>(name);
}

Expression complex_variable(const std::string& name)
{
    return Expression::create<VariableElement<true>>(name);
}

}