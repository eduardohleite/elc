#pragma once

#include "elang.hpp"
#include <variant>
#include <map>
#include <string>
#include <functional>

using namespace std;

namespace ELang {
namespace Runtime {

typedef variant<monostate, long, double> Variant;

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

class Argument {
public:
    Type type;
    string name;

    Argument(string name, Type type): name(name), type(type) { }
};

class Method {
public:
    string identifier;
    vector<Argument> arguments;
    function<Value(vector<Value>&)> callable;

    Method(string identifier, vector<Argument> arguments, function<Value(vector<Value>&)> callable):
        identifier(identifier), arguments(arguments), callable(callable) { }
};

class Context {
public:
    map<string, vector<Method>> methods;

    Context(): methods() { }
    void register_method(Method method);
};

class Interpreter {
public:
    Interpreter() { }
    ~Interpreter() { }

    Context execution_context;

    void run(const ELang::Meta::Block* program) const;
    void register_builtins();

protected:
    Value eval_expression(const ELang::Meta::Expression& expression) const;
    Value call_function(const ELang::Meta::FunctionCall* expression) const;
    void print_value(const Value& value) const;
};

} // namespace Runtime
} // namespace Runtime