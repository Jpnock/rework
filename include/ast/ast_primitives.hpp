#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

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
        std::cerr << "Variable: compile is not implemented" << std::endl;
    }
};

class Number
    : public Expression
{
private:
    double value;

public:
    Number(double _value)
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
        std::cerr << "Number: compile is not implemented" << std::endl;
    }
};

#endif
