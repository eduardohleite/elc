#pragma once

#include "elang.hpp"
#include <variant>

namespace ELang {
namespace Runtime {

typedef std::variant<std::monostate, long, double> Variant;

enum class Type {
    Integer,
    Float
};


class Value {
public:
    Value(long value): value(value), type(Type::Integer) { }
    Value(double value): value(value), type(Type::Float) { }

    Type type;
    Variant value;
};

class Interpreter {
public:
    Interpreter() { }
    ~Interpreter() { }

    void run(const ELang::Meta::Block* program) const;

protected:
    Value eval_expression(const ELang::Meta::Expression& expression) const;
    void print_value(const Value& value) const;
};

}
}