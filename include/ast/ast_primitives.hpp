#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <iostream>
#include <string>

class Identifier
    : public Expression
{
private:
    std::string id;

public:
    Identifier(const std::string &_id)
        : id(_id)
    {
    }

    const std::string getId() const
    {
        return id;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << id;
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        // TODO-B : Run bin/eval_expr with a variable binding to make sure you understand how this works.
        // If the binding does not exist, this will throw an error
        // return bindings.at(id);
    }
};

class Variable
    : public Expression
{
private:
    std::string id;

public:
    Variable(const std::string &_id)
        : id(_id)
    {
    }

    const std::string getId() const
    {
        return id;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << id;
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        // TODO-B : Run bin/eval_expr with a variable binding to make sure you understand how this works.
        // If the binding does not exist, this will throw an error
        // return bindings.at(id);
    }
};

class Declaration
    : public Expression
{
private:
    std::string id;

public:
    Declaration(const std::string &_id)
        : id(_id)
    {
    }

    const std::string getId() const
    {
        return id;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << id;
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        // TODO-B : Run bin/eval_expr with a variable binding to make sure you understand how this works.
        // If the binding does not exist, this will throw an error
        // return bindings.at(id);
    }
};

class Number
    : public Expression
{
private:
    long double value;

public:
    Number(long double _value)
        : value(_value)
    {
    }

    double getValue() const
    {
        return value;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << value;
    }

    virtual void compile(Context &ctx, std::ostream &dst) const override
    {
        std::cerr << "Assuming all numbers are integers" << std::endl;
        dst << "li a0, " << int(value) << std::endl;
    }
};

#endif
