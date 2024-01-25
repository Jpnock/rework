#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>

class Operator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;

protected:
    Operator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left), right(_right)
    {
    }

public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const = 0;

    ExpressionPtr getLeft() const
    {
        return left;
    }

    ExpressionPtr getRight() const
    {
        return right;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        left->print(dst);
        dst << " ";
        dst << getOpcode();
        dst << " ";
        right->print(dst);
        dst << " )";
    }
};

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "+";
    }

public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        std::cerr << "AddOperator: compile is not implemented" << std::endl;
    }
};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "-";
    }

public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        std::cerr << "SubOperator: compile is not implemented" << std::endl;
    }
};

class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "*";
    }

public:
    MulOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        std::cerr << "MulOperator: compile is not implemented" << std::endl;
    }
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "/";
    }

public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        std::cerr << "DivOperator: compile is not implemented" << std::endl;
    }
};

class ExpOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "^";
    }

public:
    ExpOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        std::cerr << "ExpOperator: compile is not implemented" << std::endl;
    }
};

#endif
