#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>
#include <vector>

class Function
    : public Expression
{
private:
    std::string name;
    std::vector<ExpressionPtr> args;
    ExpressionPtr body;

public:
    Function(std::string _name, std::vector<ExpressionPtr> _args, Expression *_body)
        : name(_name), args(_args), body(_body)
    {
    }

    virtual ~Function()
    {
        for (auto expr : args)
        {
            delete expr;
        }
        delete body;
    }

    std::string
    getName() const
    {
        return name;
    }

    std::vector<ExpressionPtr> getArgs() const
    {
        return args;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << name << "(";
        for (auto &&arg : args)
        {
            arg->print(dst);
        }
        dst << ")";

        dst << "{" << std::endl;
        if (body != nullptr)
        {
            body->print(dst);
            dst << std::endl;
        }
        dst << "}" << std::endl;
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        std::cerr << "Function: compile is not implemented." << std::endl;
    }
};

#endif
