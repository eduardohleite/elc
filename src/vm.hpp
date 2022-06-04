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

typedef std::variant<std::monostate,
                     long,
                     double,
                     bool,
                     std::shared_ptr<std::vector<Value>>,
                     std::shared_ptr<std::string>> Variant;

enum class Type {
    Void,
    Any,
    Integer,
    Float,
    Boolean,
    Vector,
    String,
};


class Value {
public:
    Value(const long value): value(value), type(Type::Integer) { }
    Value(const double value): value(value), type(Type::Float) { }
    Value(const bool value): value(value), type(Type::Boolean) { }
    Value(const std::shared_ptr<std::vector<Value>>& value): value(value), type(Type::Vector) { }
    Value(const std::shared_ptr<std::string>& value): value(value), type(Type::String) { }

    Value(): type(Type::Void) { }

    Type type;
    Variant value;
};

class Argument {
public:
    Type type;
    std::string name;

    Argument(const std::string& name, const Type& type): name(name), type(type) { }
};

class Method {
public:
    std::string identifier;
    std::vector<Argument> arguments;

    Method(const std::string& identifier, const std::vector<Argument>& arguments):
        identifier(identifier), arguments(arguments) { }

    virtual ~Method() {}
};

class BuiltinMethod: public Method {
public:
    std::function<Value(std::vector<Value>&)> callable;

    BuiltinMethod(const std::string& identifier, const std::vector<Argument>& arguments, const std::function<Value(std::vector<Value>&)>& callable):
        Method(identifier, arguments), callable(callable) { }
};

class CustomMethod: public Method {
public:
    ELang::Meta::Block* block;

    CustomMethod(const std::string identifier, const std::vector<Argument> arguments, ELang::Meta::Block* block):
        Method(identifier, arguments), block(block) { }
};

class Context {
public:
    std::map<std::string, std::vector<std::shared_ptr<Method>>> methods;
    std::map<std::string, Value> variables;
    std::shared_ptr<Context> parent;

    Context(): parent(nullptr), methods(), variables() { }
    Context(std::shared_ptr<Context> parent) : parent(parent), methods(), variables() { }

    void register_method(const std::shared_ptr<Method>& method);
    void assign_variable(const std::string& name, const Value& value, bool force_local = false);
    inline Value read_variable(const std::string& name);
    void locate_methods(std::vector<std::shared_ptr<ELang::Runtime::Method>>& results, const std::string& name) const;
};

class Interpreter {
public:
    Interpreter();
    ~Interpreter() { }

    std::shared_ptr<Context> global_context;

    Value run(const ELang::Meta::Block* program, const std::shared_ptr<Context>& context);
    void register_builtins();

protected:
    Value eval_expression(const ELang::Meta::Expression& expression, const std::shared_ptr<Context>& context);
    Value call_function(const ELang::Meta::FunctionCall* expression, const std::shared_ptr<Context>& context);    
    inline void print_value(const Value& value) const;

private:
    inline Type get_type_from_identifier(const std::string& identifier) const;
};

} // namespace Runtime
} // namespace Runtime