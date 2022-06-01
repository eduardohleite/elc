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

class Boolean: public Expression {
public:
    bool value;

    Boolean(bool value): value(value) { }
};

class ArithmeticExpression: public Expression {
public:
    int op;
    Expression& lhs;
    Expression& rhs;

    ArithmeticExpression(Expression& lhs, int op, Expression& rhs):
        lhs(lhs), op(op), rhs(rhs) { }
};

class NegatedBinaryExpression: public Expression {
public:
    Expression& expr;

    NegatedBinaryExpression(Expression& expr): expr(expr) { }
};

class BinaryExpression: public Expression {
public:
    int op;
    Expression& lhs;
    Expression& rhs;

    BinaryExpression(Expression& lhs, int op, Expression& rhs):
        lhs(lhs), op(op), rhs(rhs) { }
};

class ComparisonExpression: public Expression {
public:
    int op;
    Expression& lhs;
    Expression& rhs;

    ComparisonExpression(Expression& lhs, int op, Expression& rhs):
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

class Identifier: public Expression {
public:
    std::string name;

    Identifier(): name() { }
    Identifier(const std::string& name): name(name) { }
};

class FunctionCall: public Expression {
public:
    const Identifier& id;
    std::vector<Expression*> arguments;

    FunctionCall(const Identifier& id, std::vector<Expression*>& arguments):
        id(id), arguments(arguments) { }
    FunctionCall(const Identifier& id): id(id) { }
};

class VectorExpression: public Expression {
public:
    std::vector<Expression*> arguments;

    VectorExpression(std::vector<Expression*>& arguments): arguments(arguments) { }
};

class RangeExpression: public Expression {
public:
    Expression& start;
    Expression& end;

    RangeExpression(Expression& start, Expression& end): start(start), end(end) { }
};

class SearchExpression: public Expression {
public:
    Expression& collection;
    Expression& element;

    SearchExpression(Expression& collection, Expression& element): collection(collection), element(element) { }
};

class Assignment: public Statement {
public:
    const Identifier& id;
    Expression& expression;

    Assignment(const Identifier& id, Expression& expression):
        id(id), expression(expression) { }
};

class IfStatement: public Statement {
public:
    Expression& condition;
    Block* then_block;
    Block* else_block;

    IfStatement(Expression& condition, Block* then_block):
        condition(condition), then_block(then_block) { }
    IfStatement(Expression& condition, Block* then_block, Block* else_block):
        condition(condition), then_block(then_block), else_block(else_block) { }
};

} // namespace Meta
} // namespace ELang