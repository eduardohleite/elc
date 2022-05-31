#include "vm.hpp"
#include "builtin.hpp"
#include "gen/parser.hpp"

using namespace ELang::Runtime;
using namespace ELang::Meta;
using namespace std;

Value Interpreter::eval_expression(const Expression& expression) const {
    // check for expression types
    const auto expr_ptr = &expression;

    // int constant
    const auto int_expr = dynamic_cast<const Integer*>(expr_ptr);
    if (nullptr != int_expr) {
        return int_expr->value;
    }

    // float constant
    const auto float_expr = dynamic_cast<const Float*>(expr_ptr);
    if (nullptr != float_expr) {
        return float_expr->value;
    }

    // boolean constant
    const auto bool_expr = dynamic_cast<const Boolean*>(expr_ptr);
    if (nullptr != bool_expr) {
        return bool_expr->value;
    }

    // negated binary expression
    const auto negated_binary_expr = dynamic_cast<const NegatedBinaryExpression*>(expr_ptr);
    if (nullptr != negated_binary_expr) {
        auto identifier = Identifier("__not__");
        auto args = vector<Expression*>({&negated_binary_expr->expr});

        auto function_call = FunctionCall(identifier, args);
        return call_function(&function_call);
    }

    // binary expression
    const auto binary_expr = dynamic_cast<const BinaryExpression*>(expr_ptr);
    if (nullptr != binary_expr) {
        auto identifier = Identifier();
        auto args = vector<Expression*>({&binary_expr->lhs, &binary_expr->rhs});

        switch (binary_expr->op) {
            case TAND:
                identifier.name = "__and__";
                break;
            case TOR:
                identifier.name = "__or__";
                break;
            default:
                cerr << "Error: Invalid operator" << endl;
                throw -1; 
        }

        auto function_call = FunctionCall(identifier, args);
        return call_function(&function_call);
    }

    // arithmetic expression
    const auto arithmetic_expr = dynamic_cast<const ArithmeticExpression*>(expr_ptr);
    if (nullptr != arithmetic_expr) {
        auto identifier = Identifier();
        auto args = vector<Expression*>({&arithmetic_expr->lhs, &arithmetic_expr->rhs});

        switch (arithmetic_expr->op) {
            case TPLUS:
                identifier.name = "__add__";
                break;
            case TMINUS:
                identifier.name = "__sub__";
                break;
            case TMUL:
                identifier.name = "__mul__";
                break;
            case TDIV:
                identifier.name = "__div__";
                break;
            default:
                cerr << "Error: Invalid operator" << endl;
                throw -1; 
        }

        auto function_call = FunctionCall(identifier, args);
        return call_function(&function_call);
    }

    // comparison expression
    const auto comparison_expr = dynamic_cast<const ComparisonExpression*>(expr_ptr);
    if (nullptr != comparison_expr) {
        auto identifier = Identifier();
        auto args = vector<Expression*>({&comparison_expr->lhs, &comparison_expr->rhs});

        switch (comparison_expr->op) {
            case TEQ:
                identifier.name = "__eq__";
                break;
            case TNE:
                identifier.name = "__ne__";
                break;
            case TGTE:
                identifier.name = "__gte__";
                break;
            case TGT:
                identifier.name = "__gt__";
                break;
            case TLTE:
                identifier.name = "__lte__";
                break;
            case TLT:
                identifier.name = "__lt__";
                break;
            default:
                cerr << "Error: Invalid operator" << endl;
                throw -1; 
        }

        auto function_call = FunctionCall(identifier, args);
        return call_function(&function_call);
    }

    // function call
    const auto function_call_expr = dynamic_cast<const FunctionCall*>(expr_ptr);
    if (nullptr != function_call_expr) {
        return call_function(function_call_expr);
    }
}

Value Interpreter::call_function(const ELang::Meta::FunctionCall* expression) const {
    auto fun = execution_context.methods.find(expression->id.name);
    if (fun == execution_context.methods.end()) {
        cerr << "Error: Unknown function `" << expression->id.name << "`" << endl;
        throw -1;
    }

    auto methods = fun->second;

    // parse expression arguments into values
    auto expression_values = vector<Value>();
    for (auto it = expression->arguments.begin(); it != expression->arguments.end(); it++) {
        expression_values.push_back(eval_expression(**it));
    }

    for (auto it = methods.begin(); it != methods.end(); it++) {
        if (it->arguments.size() == expression_values.size()) {
            auto match = true;

            for (auto i = 0; i < it->arguments.size(); i++) {
                match &= (it->arguments[i].type == expression_values[i].type);
            }

            if (match) {
                return it->callable(expression_values);
            }
        }
    }

    cerr << "Error: Method not found" << endl;
    throw -1;
}

void Interpreter::run(const Block* program) const {
    for (auto it = program->statements.begin(); it != program->statements.end(); it++) {
        const auto statement = *it;

        // check for statement types
        const auto expression_statement = dynamic_cast<ExpressionStatement*>(statement);
        if (nullptr != expression_statement) {
            const auto res = eval_expression(expression_statement->expression);
            print_value(res);
        }
    }
}

void Interpreter::print_value(const Value& v) const {
    cout << "Evaluated: ";

    switch (v.type) {
        case Type::Integer:
            cout << std::get<long>(v.value) << " (type: Integer)";
            break;
        case Type::Float:
            cout << std::get<double>(v.value) << " (type: Float)";
            break;
        case Type::Boolean:
            cout << (std::get<bool>(v.value) ? "true" : "false") << " (type: Boolean)";
            break;
    }

    cout << endl;
}

void Interpreter::register_builtins() {
    execution_context.register_method(
        Method("__add__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) },
              builtin_add)
    );
    execution_context.register_method(
        Method("__add__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) },
              builtin_add)
    );
    execution_context.register_method(
        Method("__add__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) },
              builtin_add)
    );
    execution_context.register_method(
        Method("__add__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Float) },
              builtin_add)
    );

    execution_context.register_method(
        Method("__sub__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) },
              builtin_sub)
    );
    execution_context.register_method(
        Method("__sub__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) },
              builtin_sub)
    );
    execution_context.register_method(
        Method("__sub__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) },
              builtin_sub)
    );
    execution_context.register_method(
        Method("__sub__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Float) },
              builtin_sub)
    );

    execution_context.register_method(
        Method("__mul__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) },
              builtin_mul)
    );
    execution_context.register_method(
        Method("__mul__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) },
              builtin_mul)
    );
    execution_context.register_method(
        Method("__mul__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) },
              builtin_mul)
    );
    execution_context.register_method(
        Method("__mul__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Float) },
              builtin_mul)
    );

    execution_context.register_method(
        Method("__div__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) },
              builtin_div)
    );
    execution_context.register_method(
        Method("__div__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) },
              builtin_div)
    );
    execution_context.register_method(
        Method("__div__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) },
              builtin_div)
    );
    execution_context.register_method(
        Method("__div__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Float) },
              builtin_div)
    );

    execution_context.register_method(
        Method("__not__",
              { Argument("expr", Type::Boolean) },
              builtin_not)
    );
    execution_context.register_method(
        Method("__and__",
              { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) },
              builtin_and)
    );
    execution_context.register_method(
        Method("__or__",
              { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) },
              builtin_or)
    );

    execution_context.register_method(
        Method("__eq__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) },
              builtin_eq)
    );
    execution_context.register_method(
        Method("__eq__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) },
              builtin_eq)
    );
    execution_context.register_method(
        Method("__eq__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) },
              builtin_eq)
    );
    execution_context.register_method(
        Method("__eq__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Float) },
              builtin_eq)
    );
    execution_context.register_method(
        Method("__eq__",
              { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) },
              builtin_eq)
    );

    execution_context.register_method(
        Method("__ne__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) },
              builtin_ne)
    );
    execution_context.register_method(
        Method("__ne__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) },
              builtin_ne)
    );
    execution_context.register_method(
        Method("__ne__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) },
              builtin_ne)
    );
    execution_context.register_method(
        Method("__ne__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Float) },
              builtin_ne)
    );
    execution_context.register_method(
        Method("__ne__",
              { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) },
              builtin_ne)
    );

    execution_context.register_method(
        Method("__gte__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) },
              builtin_gte)
    );
    execution_context.register_method(
        Method("__gte__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) },
              builtin_gte)
    );
    execution_context.register_method(
        Method("__gte__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) },
              builtin_gte)
    );
    execution_context.register_method(
        Method("__gte__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Float) },
              builtin_gte)
    );
    execution_context.register_method(
        Method("__gte__",
              { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) },
              builtin_gte)
    );

    execution_context.register_method(
        Method("__gt__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) },
              builtin_gt)
    );
    execution_context.register_method(
        Method("__gt__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) },
              builtin_gt)
    );
    execution_context.register_method(
        Method("__gt__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) },
              builtin_gt)
    );
    execution_context.register_method(
        Method("__gt__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Float) },
              builtin_gt)
    );
    execution_context.register_method(
        Method("__gt__",
              { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) },
              builtin_gt)
    );

    execution_context.register_method(
        Method("__lte__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) },
              builtin_lte)
    );
    execution_context.register_method(
        Method("__lte__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) },
              builtin_lte)
    );
    execution_context.register_method(
        Method("__lte__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) },
              builtin_lte)
    );
    execution_context.register_method(
        Method("__lte__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Float) },
              builtin_lte)
    );
    execution_context.register_method(
        Method("__lte__",
              { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) },
              builtin_lte)
    );

    execution_context.register_method(
        Method("__lt__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) },
              builtin_lt)
    );
    execution_context.register_method(
        Method("__lt__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) },
              builtin_lt)
    );
    execution_context.register_method(
        Method("__lt__",
              { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) },
              builtin_lt)
    );
    execution_context.register_method(
        Method("__lt__",
              { Argument("lhs", Type::Float), Argument("rhs", Type::Float) },
              builtin_lt)
    );
    execution_context.register_method(
        Method("__lt__",
              { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) },
              builtin_lt)
    );
}

void Context::register_method(const Method method) {
    auto it = methods.find(method.identifier);
    if (it == methods.end()) {
        methods[method.identifier] = vector<Method>();
    }

    methods[method.identifier].push_back(method);
}
