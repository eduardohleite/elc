#include "vm.hpp"
#include "builtin.hpp"
#include "gen/parser.hpp"

using namespace ELang::Runtime;
using namespace ELang::Meta;
using namespace std;

Value Interpreter::eval_expression(const Expression& expression, const std::shared_ptr<Context>& context) {
    // check for expression types
    const auto expr_ptr = &expression;

    // int constant
    const auto int_expr = dynamic_cast<const Integer*>(expr_ptr);
    if (nullptr != int_expr) {
        return Value(int_expr->value);
    }

    // float constant
    const auto float_expr = dynamic_cast<const Float*>(expr_ptr);
    if (nullptr != float_expr) {
        return Value(float_expr->value);
    }

    // boolean constant
    const auto bool_expr = dynamic_cast<const Boolean*>(expr_ptr);
    if (nullptr != bool_expr) {
        return Value(bool_expr->value);
    }

    // string constant
    const auto string_expr = dynamic_cast<const String*>(expr_ptr);
    if (nullptr != string_expr) {
        return Value(std::make_shared<std::string>(string_expr->value));
    }

    // vector expression
    const auto vector_expr = dynamic_cast<const VectorExpression*>(expr_ptr);
    if (nullptr != vector_expr) {
        const auto vec = make_shared<vector<Value>>();
        for (auto it = vector_expr->arguments.cbegin(); it != vector_expr->arguments.cend(); ++it) {
            vec->push_back(eval_expression(**it, context));
        }

        return Value(vec);
    }

    // negated binary expression
    const auto negated_binary_expr = dynamic_cast<const NegatedBinaryExpression*>(expr_ptr);
    if (nullptr != negated_binary_expr) {
        const auto identifier = Identifier("__not__");
        const auto args = vector<Expression*>({&negated_binary_expr->expr});

        const auto function_call = FunctionCall(identifier, args);
        return call_function(&function_call, context);
    }

    // binary expression
    const auto binary_expr = dynamic_cast<const BinaryExpression*>(expr_ptr);
    if (nullptr != binary_expr) {
        auto identifier = Identifier();
        const auto args = vector<Expression*>({&binary_expr->lhs, &binary_expr->rhs});

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

        const auto function_call = FunctionCall(identifier, args);
        return call_function(&function_call, context);
    }

    // arithmetic expression
    const auto arithmetic_expr = dynamic_cast<const ArithmeticExpression*>(expr_ptr);
    if (nullptr != arithmetic_expr) {
        auto identifier = Identifier();
        const auto args = vector<Expression*>({&arithmetic_expr->lhs, &arithmetic_expr->rhs});

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

        const auto function_call = FunctionCall(identifier, args);
        return call_function(&function_call, context);
    }

    // comparison expression
    const auto comparison_expr = dynamic_cast<const ComparisonExpression*>(expr_ptr);
    if (nullptr != comparison_expr) {
        auto identifier = Identifier();
        const auto args = vector<Expression*>({&comparison_expr->lhs, &comparison_expr->rhs});

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

        const auto function_call = FunctionCall(identifier, args);
        return call_function(&function_call, context);
    }

    // range
    const auto range_expr = dynamic_cast<const RangeExpression*>(expr_ptr);
    if (nullptr != range_expr) {
        const auto args = vector<Expression*>({&range_expr->start, &range_expr->end});
        const auto function_call = FunctionCall(Identifier("range"), args);
        return call_function(&function_call, context);
    }

    // search
    const auto search_expr = dynamic_cast<const SearchExpression*>(expr_ptr);
    if (nullptr != search_expr) {
        const auto args = vector<Expression*>({&search_expr->collection, &search_expr->element});
        const auto function_call = FunctionCall(Identifier("__in__"), args);
        return call_function(&function_call, context);
    }

    // index
    const auto index_expr = dynamic_cast<const IndexExpression*>(expr_ptr);
    if (nullptr != index_expr) {
        const auto args = vector<Expression*>({&index_expr->identifier_expression, &index_expr->expression});
        const auto function_call = FunctionCall(Identifier("__at__"), args);
        return call_function(&function_call, context);
    }

    // function call
    const auto function_call_expr = dynamic_cast<const FunctionCall*>(expr_ptr);
    if (nullptr != function_call_expr) {
        return call_function(function_call_expr, context);
    }

    // identifier
    const auto identifier_expr = dynamic_cast<const Identifier*>(expr_ptr);
    if (nullptr != identifier_expr) {
        return context->read_variable(identifier_expr->name);
    }
}

void Context::locate_methods(std::vector<std::shared_ptr<ELang::Runtime::Method>>& results, const std::string& name) const {
    const auto fun = methods.find(name);

    if (fun != methods.end()) {
        auto found = fun->second;
        results.insert(results.end(), found.begin(), found.end());
    }

    if (nullptr != parent) {
        parent->locate_methods(results, name);
    }
}

Value Interpreter::call_function(const ELang::Meta::FunctionCall* expression, const std::shared_ptr<Context>& context) {
    auto methods = std::vector<std::shared_ptr<ELang::Runtime::Method>>();
    context->locate_methods(methods, expression->id.name);

    // parse expression arguments into values
    auto expression_values = vector<Value>();
    for (auto it = expression->arguments.cbegin(); it != expression->arguments.cend(); ++it) {
        expression_values.push_back(eval_expression(**it, context));
    }

    if (methods.size() == 0) {
        cerr << "Error: Unknown function `" << expression->id.name << "`" << endl;
        throw -1;
    }

    for (auto it = methods.cbegin(); it != methods.cend(); ++it) {       
        const auto ptr = *it;

        if (ptr->arguments.size() == expression_values.size()) {
            auto match = true;

            for (std::size_t i = 0; i < ptr->arguments.size(); ++i) {
                match &= (ptr->arguments[i].type == Type::Any || ptr->arguments[i].type == expression_values[i].type);
            }

            if (match) {
                const auto builtin = dynamic_pointer_cast<BuiltinMethod>(*it);
                if (nullptr != builtin) {
                    return builtin->callable(expression_values);
                }

                const auto custom = dynamic_pointer_cast<CustomMethod>(*it);
                if (nullptr != custom) {
                    // todo: function needs to return the last evaluated expression
                    const auto block_context = make_shared<Context>(context);

                    for (auto i = 0; i < ptr->arguments.size(); ++i) {
                        block_context->assign_variable(ptr->arguments[i].name, expression_values[i], true);
                    }
                    
                    return run(custom->block, block_context);
                }
            }
        }
    }

    cerr << "Error: Method not found" << endl;
    throw -1;
}

Value Interpreter::run(const Block* program, const std::shared_ptr<Context>& context) {
    auto last_evaluated_value = Value();

    for (auto it = program->statements.cbegin(); it != program->statements.cend(); ++it) {
        const auto statement = *it;

        // check for statement types

        const auto if_statement = dynamic_cast<IfStatement*>(statement);
        if (nullptr != if_statement) {
            const auto condition = eval_expression(if_statement->condition, context);
            if (condition.type != Type::Boolean) {
                cerr << "Invalid type for conditional statement." << endl;
                throw -1;
            }

            auto condition_value = std::get<bool>(condition.value);
            if (condition_value) {
                last_evaluated_value = run(if_statement->then_block, context);
            }
            else {
                if (nullptr != if_statement->else_block) {
                    last_evaluated_value = run(if_statement->else_block, context);
                }
                else {
                    last_evaluated_value = Value();
                }
            }
            continue;
        }

        const auto while_loop = dynamic_cast<WhileLoop*>(statement);
        if (nullptr != while_loop) {
            auto condition = eval_expression(while_loop->condition, context);
            if (condition.type != Type::Boolean) {
                cerr << "Invalid type for conditional statement." << endl;
                throw -1; 
            }

            auto condition_value = std::get<bool>(condition.value);
            if (condition_value) {

                while (condition_value) {
                    last_evaluated_value = run(while_loop->block, context);

                    // reevaluate condition
                    condition = eval_expression(while_loop->condition, context);
                    condition_value = std::get<bool>(condition.value);
                }
            }
            continue;
        }

        const auto for_loop = dynamic_cast<ForLoop*>(statement);
        if (nullptr != for_loop) {
            const auto iterator = eval_expression(for_loop->iterator, context);
            if (iterator.type != Type::Vector) {
                cerr << "Invalid iterator." << endl;
                throw -1;
            }

            const auto iterator_value = std::get<shared_ptr<vector<Value>>>(iterator.value);
            for (auto it = iterator_value->cbegin(); it != iterator_value->cend(); ++it) {
                context->assign_variable(for_loop->id.name, *it);
                last_evaluated_value = run(for_loop->block, context);
            }
            continue;
        }

        const auto func_decl = dynamic_cast<Function*>(statement);
        if (nullptr != func_decl) {
            // todo: we need some kind of validation here
            auto args = std::vector<Argument>();
            for (auto it = func_decl->params.cbegin(); it != func_decl->params.cend(); ++it) {
                const auto param = *it;

                auto type = get_type_from_identifier(param->type.name);
                args.push_back(Argument(param->id.name, type));
            }

            context->register_method(shared_ptr<Method>(new CustomMethod(func_decl->id.name, args, func_decl->block)));

            last_evaluated_value = Value();
            continue;
        }
        
        const auto assignment = dynamic_cast<Assignment*>(statement);
        if (nullptr != assignment) {
            const auto value = eval_expression(assignment->expression, context);
            context->assign_variable(assignment->id.name, value);

            last_evaluated_value = Value();
            continue;
        }

        const auto expression_statement = dynamic_cast<ExpressionStatement*>(statement);
        if (nullptr != expression_statement) {
            const auto res = eval_expression(expression_statement->expression, context);

#ifdef DEBUG
            print_value(res);
#endif // DEBUG

            last_evaluated_value = res;
            continue;
        }
    }

    return last_evaluated_value;
}

Type Interpreter::get_type_from_identifier(const std::string& identifier) const {
    if (identifier == "Integer") {
        return Type::Integer;
    }
    else if (identifier == "Float") {
        return Type::Float;
    }
    else if (identifier == "Boolean") {
        return Type::Boolean;
    }
    else if (identifier == "Vector") {
        return Type::Vector;
    }
    else {
        cerr << "Invalid type: `" << identifier << "`" << endl;
        throw -1;
    }
}

void Interpreter::print_value(const Value& v) const {
    cout << "Evaluated: ";
    builtin_show({v});
}

void Interpreter::register_builtins() {
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__add__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) }, builtin_add)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__add__", { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) }, builtin_add)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__add__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) }, builtin_add)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__add__", { Argument("lhs", Type::Float), Argument("rhs", Type::Float) }, builtin_add)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__sub__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) }, builtin_sub)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__sub__", { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) }, builtin_sub)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__sub__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) }, builtin_sub)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__sub__", { Argument("lhs", Type::Float), Argument("rhs", Type::Float) }, builtin_sub)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__mul__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) }, builtin_mul)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__mul__", { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) }, builtin_mul)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__mul__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) }, builtin_mul)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__mul__", { Argument("lhs", Type::Float), Argument("rhs", Type::Float) }, builtin_mul)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__div__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) }, builtin_div)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__div__", { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) }, builtin_div)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__div__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) }, builtin_div)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__div__", { Argument("lhs", Type::Float), Argument("rhs", Type::Float) }, builtin_div)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__not__", { Argument("expr", Type::Boolean) }, builtin_not)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__and__", { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) }, builtin_and)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__or__", { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) }, builtin_or)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__eq__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) }, builtin_eq)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__eq__", { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) }, builtin_eq)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__eq__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) }, builtin_eq)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__eq__", { Argument("lhs", Type::Float), Argument("rhs", Type::Float) }, builtin_eq)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__eq__", { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) }, builtin_eq)));
    
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__ne__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) }, builtin_ne)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__ne__", { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) }, builtin_ne)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__ne__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) }, builtin_ne)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__ne__", { Argument("lhs", Type::Float), Argument("rhs", Type::Float) }, builtin_ne)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__ne__", { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) }, builtin_ne)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__gte__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) }, builtin_gte)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__gte__", { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) }, builtin_gte)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__gte__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) }, builtin_gte)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__gte__", { Argument("lhs", Type::Float), Argument("rhs", Type::Float) }, builtin_gte)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__gte__", { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) }, builtin_gte)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__gt__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) }, builtin_gt)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__gt__", { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) }, builtin_gt)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__gt__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) }, builtin_gt)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__gt__", { Argument("lhs", Type::Float), Argument("rhs", Type::Float) }, builtin_gt)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__gt__", { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) }, builtin_gt)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__lte__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) }, builtin_lte)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__lte__", { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) }, builtin_lte)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__lte__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) }, builtin_lte)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__lte__", { Argument("lhs", Type::Float), Argument("rhs", Type::Float) }, builtin_lte)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__lte__", { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) }, builtin_lte)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__lt__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Integer) }, builtin_lt)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__lt__", { Argument("lhs", Type::Float), Argument("rhs", Type::Integer) }, builtin_lt)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__lt__", { Argument("lhs", Type::Integer), Argument("rhs", Type::Float) }, builtin_lt)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__lt__", { Argument("lhs", Type::Float), Argument("rhs", Type::Float) }, builtin_lt)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__lt__", { Argument("lhs", Type::Boolean), Argument("rhs", Type::Boolean) }, builtin_lt)));

    // vector functions
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("zeros", { Argument("n", Type::Integer) }, builtin_zeros)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("ones", { Argument("n", Type::Integer) }, builtin_ones)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("length", { Argument("vec", Type::Vector) }, builtin_length)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("range", { Argument("max", Type::Integer) }, builtin_range)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("range", { Argument("min", Type::Integer), Argument("max", Type::Integer) }, builtin_range)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("push!", { Argument("vec", Type::Vector), Argument("value", Type::Any) }, builtin_push_bang)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("pop!", { Argument("vec", Type::Vector) }, builtin_pop_bang)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__at__", { Argument("vec", Type::Vector), Argument("index", Type::Integer) }, builtin_at)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__in__", { Argument("vec", Type::Vector), Argument("value", Type::Any) }, builtin_in)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("show", { Argument("value", Type::Any) }, builtin_show)));

    // string functions
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__add__", { Argument("lhs", Type::String), Argument("rhs", Type::String) }, builtin_add)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__eq__", { Argument("lhs", Type::String), Argument("rhs", Type::String) }, builtin_eq)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__ne__", { Argument("lhs", Type::String), Argument("rhs", Type::String) }, builtin_ne)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("__at__", { Argument("str", Type::String), Argument("index", Type::Integer) }, builtin_at)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("length", { Argument("vec", Type::String) }, builtin_length)));

    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("substr", { Argument("str", Type::String), Argument("length", Type::Integer) }, builtin_substr)));
    global_context->register_method(shared_ptr<Method>(new BuiltinMethod("substr", { Argument("str", Type::String), Argument("start", Type::Integer), Argument("length", Type::Integer) }, builtin_substr)));
}

Interpreter::Interpreter() {
    global_context = std::make_shared<Context>();
}

void Context::register_method(const std::shared_ptr<Method>& method) {
    const auto it = methods.find(method->identifier);
    if (it == methods.end()) {
        methods[method->identifier] = vector<std::shared_ptr<Method>>();
    }

    // TODO: collisions. what if we already have a method with the same arguments?
    methods[method->identifier].push_back(method);
}

void Context::assign_variable(const string& name, const Value& value, bool force_local) {
    // TODO: context disambiguation. i.e. local/global keywords
    auto search_context = this;
    auto variable_exists = false;

    if (force_local) {
        variables[name] = value;
        return;
    }

    while (nullptr != search_context && !variable_exists) {
        const auto it = search_context->variables.find(name);
        if (it == search_context->variables.end()) {
            search_context = search_context->parent.get();
        }
        else {
            variable_exists = true;
            search_context->variables[name] = value;
        }
    }

    if (!variable_exists) {
        variables[name] = value;
    }
}

Value Context::read_variable(const string& name) {
    const auto it = variables.find(name);
    if (it == variables.end()) {
        if (nullptr != parent) {
            return parent->read_variable(name);
        }
        else {
            cerr << "Calling variable `" << name << "` before assignment." << endl;
            throw -1;
        }
    }

    return variables[name];
}
