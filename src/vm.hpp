#pragma once

#include "elang.hpp"
#include <variant>
#include <map>
#include <string>
#include <functional>
#include <memory>
#include <vector>

namespace ELang {
namespace Runtime {

class Value; // forward declaration

typedef std::variant<std::monostate, long, double, bool, std::shared_ptr<std::vector<Value>>> Variant;

enum class Type {
    Integer,
    Float,
    Boolean,
    List
};


class Value {
public:
    Value(long value): value(value), type(Type::Integer) { }
    Value(double value): value(value), type(Type::Float) { }
    Value(bool value): value(value), type(Type::Boolean) { }
    Value(std::shared_ptr<std::vector<Value>> value): value(value), type(Type::List) { }

    Value() { }

    Type type;
    Variant value;
};

class Argument {
public:
    Type type;
    std::string name;

    Argument(std::string name, Type type): name(name), type(type) { }
};

class Method {
public:
    std::string identifier;
    std::vector<Argument> arguments;
    std::function<Value(std::vector<Value>&)> callable;

    Method(std::string identifier, std::vector<Argument> arguments, std::function<Value(std::vector<Value>&)> callable):
        identifier(identifier), arguments(arguments), callable(callable) { }
};

class Context {
public:
    std::map<std::string, std::vector<Method>> methods;
    std::map<std::string, Value> variables;

    Context(): methods(), variables() { }
    void register_method(const Method method);
    void assign_variable(const std::string name, Value value);
    Value read_variable(const std::string name);
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