#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>

class Expression;

typedef const Expression *ExpressionPtr;

class Expression
{
public:
    virtual ~Expression()
    {
    }

    // Prints a text representation of the expression to dst.
    virtual void print(std::ostream &dst) const = 0;

    // Compiles the expression, outputting assembly to dst.
    virtual void compile(Context &ctx, std::ostream &dst) const
    {
        throw std::runtime_error("Not implemented.");
    }
};

#endif
