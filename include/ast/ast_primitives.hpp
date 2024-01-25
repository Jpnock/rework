#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

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
