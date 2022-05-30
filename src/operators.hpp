#pragma once

namespace ELang {
namespace Runtime {

class Value;

class Operator {
};

class ArithmeticOperator: public Operator {
    virtual Value eval(Value lhs, Value rhs) const { }
};


class PlusOperator: public ArithmeticOperator {
public:
    virtual Value eval(Value lhs, Value rhs) const override;
};

class MinusOperator: public ArithmeticOperator {
public:
    virtual Value eval(Value lhs, Value rhs) const override;
};

class MultiplyOperator: public ArithmeticOperator {
public:
    virtual Value eval(Value lhs, Value rhs) const override;
};

class DivideOperator: public ArithmeticOperator {
public:
    virtual Value eval(Value lhs, Value rhs) const override;
};

}
}