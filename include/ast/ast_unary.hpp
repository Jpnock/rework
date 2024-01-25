#ifndef ast_unary_hpp
#define ast_unary_hpp

#include <string>
#include <iostream>

class Unary
    : public Expression
{
private:
    ExpressionPtr expr;

protected:
    Unary(const ExpressionPtr _expr)
        : expr(_expr)
    {
    }

public:
    virtual ~Unary()
    {
        delete expr;
    }

    virtual const char *getOpcode() const = 0;

    ExpressionPtr getExpr() const
    {
        return expr;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << getOpcode();
        dst << " ";
        expr->print(dst);
        dst << " )";
    }
};

class NegOperator
    : public Unary
{
public:
    NegOperator(const ExpressionPtr _expr)
        : Unary(_expr)
    {
    }

    virtual const char *getOpcode() const override
    {
        return "-";
    }

    virtual void compile(std::ostream &dst) const override
    {
        throw std::runtime_error("NegOperator: compile is not implemented");
    }
};

#endif
