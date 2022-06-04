#pragma once

#include "elang.hpp"
#include <variant>
#include <map>
#include <string>
#include <functional>
#include <memory>
#include <vector>

#define DEBUG


namespace ELang {
namespace Runtime {

class Value; // forward declaration

typedef std::variant<std::monostate, long, double, bool, std::shared_ptr<std::vector<Value>>> Variant;

enum class Type {
    Void,
    Any,
    Integer,
    Float,
    Boolean,
    Vector
};


class Value {
public:
    Value(long value): value(value), type(Type::Integer) { }
    Value(double value): value(value), type(Type::Float) { }
    Value(bool value): value(value), type(Type::Boolean) { }
    Value(std::shared_ptr<std::vector<Value>> value): value(value), type(Type::Vector) { }

    Value(): type(Type::Void) { }

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

    Method(std::string identifier, std::vector<Argument> arguments):
        identifier(identifier), arguments(arguments) { }

    virtual ~Method() {}
};

class BuiltinMethod: public Method {
public:
    std::function<Value(std::vector<Value>&)> callable;

    BuiltinMethod(std::string identifier, std::vector<Argument> arguments, std::function<Value(std::vector<Value>&)> callable):
        Method(identifier, arguments), callable(callable) { }
};

class CustomMethod: public Method {
public:
    ELang::Meta::Block* block;

    CustomMethod(std::string identifier, std::vector<Argument> arguments, ELang::Meta::Block* block):
        Method(identifier, arguments), block(block) { }
};

class Context {
public:
    std::map<std::string, std::vector<std::shared_ptr<Method>>> methods;
    std::map<std::string, Value> variables;
    std::shared_ptr<Context> parent;

    Context(): parent(nullptr), methods(), variables() { }
    Context(std::shared_ptr<Context> parent) : parent(parent), methods(), variables() { }

    void register_method(const std::shared_ptr<Method> method);
    void assign_variable(const std::string name, Value value);
    Value read_variable(const std::string name);
    void locate_methods(std::vector<std::shared_ptr<ELang::Runtime::Method>>& results, const std::string& name) const;
};

class Interpreter {
public:
    Interpreter();
    ~Interpreter() { }

    std::shared_ptr<Context> global_context;

    Value run(const ELang::Meta::Block* program, std::shared_ptr<Context> context);
    void register_builtins();

protected:
    Value eval_expression(const ELang::Meta::Expression& expression, std::shared_ptr<Context> context);
    Value call_function(const ELang::Meta::FunctionCall* expression, std::shared_ptr<Context> context);    
    void print_value(const Value& value) const;

private:
    Type get_type_from_identifier(const std::string& identifier) const;
};

} // namespace Runtime
} // namespace Runtime