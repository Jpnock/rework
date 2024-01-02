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
        std::cerr << "Function: evaluate is not fully implemented." << std::endl;

        dst << "# Function: evaluate is not fully implemented" << std::endl;
        dst << ".text" << std::endl;
        dst << ".globl " << name << std::endl;
        dst << std::endl;

        dst << name << ":" << std::endl;

        if (body != nullptr)
        {
            body->compile(ctx, dst);
        }

        // Implicit return at the end of the function, in case it was not
        // specified in the body.
        dst << "li a0, 0" << std::endl;
        dst << "ret" << std::endl;
    }
};

class Return
    : public Expression
{
private:
    ExpressionPtr returnExpr;

public:
    Return()
        : returnExpr(nullptr)
    {
    }

    Return(ExpressionPtr _returnExpr)
        : returnExpr(_returnExpr)
    {
    }

    virtual ~Return()
    {
        delete returnExpr;
    }

    ExpressionPtr getReturnExpression() const
    {
        return returnExpr;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << "return";
        if (returnExpr == nullptr)
        {
            dst << ";" << std::endl;
            return;
        }

        dst << " ";
        returnExpr->print(dst);
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        if (returnExpr != nullptr)
        {
            returnExpr->compile(ctx, dst);
        }
        dst << "ret" << std::endl;
    }
};

#endif
