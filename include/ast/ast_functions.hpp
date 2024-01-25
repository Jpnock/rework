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
    Function(std::string _name, std::vector<ExpressionPtr> _args)
        : name(_name), args(_args), body(nullptr)
    {
    }

    virtual ~Function()
    {
        // delete args;
    }

    std::string getName() const
    {
        return name;
    }

    std::vector<ExpressionPtr> getArgs() const
    {
        return args;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << name << "( ";
        for (auto &&arg : args)
        {
            arg->print(dst);
        }
        dst << " )";

        dst << "{" << std::endl;
        if (body != nullptr)
        {
            body->print(dst);
            dst << std::endl;
        }
        dst << "}" << std::endl;
    }

    virtual void compile(std::ostream &dst) const override
    {
        throw std::runtime_error("Function: compile is not implemented.");
    }
};

#endif
