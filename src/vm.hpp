#pragma once

#include "elang.hpp"
#include <variant>

namespace ELang {
namespace Runtime {

typedef std::variant<std::monostate, long> Variant;

enum class Type {
    Integer
};


class Value {
public:
    Value(long value): value(value), type(Type::Integer) { }

    Type type;
    Variant value;
};

class Interpreter {
public:
    Interpreter() { }
    ~Interpreter() { }

    void run(const ELang::Meta::Block *program) const;

protected:
    Value eval_expression(const ELang::Meta::Expression &expression) const;
};

}
}