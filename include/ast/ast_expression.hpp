#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <vector>

class Expression;

typedef const Expression *ExpressionPtr;

class Expression
{
public:
    virtual ~Expression()
    {
    }

    // Prints a text representation of the expression to dst.
    virtual void print(std::ostream &dst) const
    {
        throw std::runtime_error("print() not implemented.");
    };

    // Compiles the expression, outputting assembly to dst.
    virtual void compile(Context &ctx, std::ostream &dst) const
    {
        throw std::runtime_error("Not implemented.");
    }
};

// Represents a list/vector of expressions.
class ExpressionList
    : public Expression
{
private:
    std::vector<ExpressionPtr> exprs;

public:
    ExpressionList(ExpressionPtr firstItem)
        : exprs({firstItem})
    {
    }

    ~ExpressionList()
    {
        for (auto expr : exprs)
        {
            delete expr;
        }
    }

    inline void push_back(ExpressionPtr item)
    {
        exprs.push_back(item);
    }

    virtual void print(std::ostream &dst) const override
    {
        for (auto expr : exprs)
        {
            if (expr == nullptr)
            {
                continue;
            }
            expr->print(dst);
        }
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        for (auto expr : exprs)
        {
            if (expr == nullptr)
            {
                continue;
            }
            expr->compile(ctx, dst);
        }
    }
};

#endif
