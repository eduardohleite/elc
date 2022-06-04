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

    Integer(const long value): value(value) { }
};

class Float: public Expression {
public:
    double value;

    Float(const double value): value(value) { }
};

class Boolean: public Expression {
public:
    bool value;

    Boolean(const bool value): value(value) { }
};

class String: public Expression {
public:
    const std::string value;

    inline std::string parse_string(const std::string& input) {
        if (input.length() > 2) {
            const auto x = input.substr(1, input.length() - 2);
            return x;
        }
        else {
            return input;
        }
    }

    String(const std::string& v): value(parse_string(v)) { }
};

class ArithmeticExpression: public Expression {
public:
    const int op;
    Expression& lhs;
    Expression& rhs;

    ArithmeticExpression(Expression& lhs, const int op, Expression& rhs):
        lhs(lhs), op(op), rhs(rhs) { }
};

class NegatedBinaryExpression: public Expression {
public:
    Expression& expr;

    NegatedBinaryExpression(Expression& expr): expr(expr) { }
};

class BinaryExpression: public Expression {
public:
    const int op;
    Expression& lhs;
    Expression& rhs;

    BinaryExpression(Expression& lhs, const int op, Expression& rhs):
        lhs(lhs), op(op), rhs(rhs) { }
};

class ComparisonExpression: public Expression {
public:
    const int op;
    Expression& lhs;
    Expression& rhs;

    ComparisonExpression(Expression& lhs, const int op, Expression& rhs):
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
    std::vector<Statement*> statements;

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

    FunctionCall(const Identifier& id, const std::vector<Expression*>& arguments):
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

class IndexExpression: public Expression {
public:
    Expression& identifier_expression;
    Expression& expression;

    IndexExpression(Expression& identifier_expression, Expression& expression):
        identifier_expression(identifier_expression), expression(expression) { }
};

class TypedIdentifier: public Expression {
public:
    const Identifier& type;
    const Identifier& id;

    TypedIdentifier(const Identifier& type, const Identifier& id):
        type(type), id(id) { }
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

class ForLoop: public Statement {
public:
    const Identifier& id;
    Expression& iterator;
    Block* block;

    ForLoop(const Identifier& id, Expression& iterator, Block* block):
        id(id), iterator(iterator), block(block) { }
};

class WhileLoop: public Statement {
public:
    Expression& condition;
    Block* block;

    WhileLoop(Expression& condition, Block* block):
        condition(condition), block(block) { }
};

class Function: public Statement {
public:
    const Identifier& id;
    std::vector<TypedIdentifier*> params;
    Block* block;

    Function(const Identifier& id, std::vector<TypedIdentifier*>& params, Block* block):
        id(id), params(params), block(block) { }
};

} // namespace Meta
} // namespace ELang