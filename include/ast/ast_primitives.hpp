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

    virtual void compile(std::ostream &dst) const override
    {
        throw std::runtime_error("Variable: compile is not implemented");
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

    virtual void compile(std::ostream &dst) const override
    {
        throw std::runtime_error("Number: compile is not implemented");
    }
};

#endif
