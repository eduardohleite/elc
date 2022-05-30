namespace ELang {
namespace Runtime {

class Operator {

};

class ArithmeticOperator: public Operator {
};


class PlusOperator: public ArithmeticOperator {
public:
    long eval(long lhs, long rhs) const { return lhs + rhs; }
};

class MinusOperator: public ArithmeticOperator {
public:
    long eval(long lhs, long rhs) const { return lhs - rhs; }
};

class MultiplyOperator: public ArithmeticOperator {
public:
    long eval(long lhs, long rhs) const { return lhs * rhs; }
};

class DivideOperator: public ArithmeticOperator {
public:
    long eval(long lhs, long rhs) const { return lhs / rhs; }
};

}
}