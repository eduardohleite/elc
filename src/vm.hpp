#pragma once

#include "elang.hpp"
#include <variant>
#include <map>
#include <string>
#include <functional>

using namespace std;

namespace ELang {
namespace Runtime {

typedef variant<monostate, long, double, bool> Variant;

enum class Type {
    Integer,
    Float,
    Boolean
};


class Value {
public:
    Value(long value): value(value), type(Type::Integer) { }
    Value(double value): value(value), type(Type::Float) { }
    Value(bool value): value(value), type(Type::Boolean) { }
    Value() { }

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
    map<string, Value> variables;

    Context(): methods(), variables() { }
    void register_method(const Method method);
    void assign_variable(const string name, Value value);
    Value read_variable(const string name);
};

class Interpreter {
public:
    Interpreter() { }
    ~Interpreter() { }

    Context execution_context;

    void run(const ELang::Meta::Block* program);
    void register_builtins();

protected:
    Value eval_expression(const ELang::Meta::Expression& expression);
    Value call_function(const ELang::Meta::FunctionCall* expression);
    void print_value(const Value& value) const;
};

} // namespace Runtime
} // namespace Runtime