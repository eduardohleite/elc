#pragma once

#include <iostream>
#include <vector>

namespace ELang {
namespace Meta {

class Node {
public:
    virtual ~Node() {}
};

class Expression: public Node {
};

class Statement: public Node {
};

class Integer: public Expression {
public:
    long value;
    Integer(long value): value(value) { }
};

class Float: public Expression {
public:
    double value;
    Float(double value): value(value) { }
};

class ArithmeticExpression: public Expression {
public:
    int op;
    Expression& lhs;
    Expression& rhs;
    ArithmeticExpression(Expression& lhs, int op, Expression& rhs):
        lhs(lhs), op(op), rhs(rhs) { }
};

class ExpressionStatement: public Statement {
public:
    Expression& expression;
    ExpressionStatement(Expression& expression):
        expression(expression) {}
};

class Block: public Expression {
public:
    std::vector<Statement *> statements;
    Block() { }
};

} // namespace Meta
} // namespace ELang