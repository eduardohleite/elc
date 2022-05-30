#include "vm.hpp"
#include "operators.hpp"
#include "gen/parser.hpp"

using namespace ELang::Runtime;
using namespace ELang::Meta;
using namespace std;

Value Interpreter::eval_expression(const Expression& expression) const {
    // check for expression types
    const auto expr_ptr = &expression;

    const auto arithmetic_expr = dynamic_cast<const ArithmeticExpression*>(expr_ptr);
    if (nullptr != arithmetic_expr) {
        const auto lhs_value = eval_expression(arithmetic_expr->lhs);
        const auto rhs_value = eval_expression(arithmetic_expr->rhs);

        switch (arithmetic_expr->op) {
            case TPLUS:
                return PlusOperator().eval(lhs_value, rhs_value);
            case TMINUS:
                return MinusOperator().eval(lhs_value, rhs_value);
            case TMUL:
                return MultiplyOperator().eval(lhs_value, rhs_value);
            case TDIV:
                return DivideOperator().eval(lhs_value, rhs_value);
            default:
                cout << "Error: Invalid operator" << endl; // TODO error reporting
                throw -1; 
        }
    }

    const auto int_expr = dynamic_cast<const Integer*>(expr_ptr);
    if (nullptr != int_expr) {
        return int_expr->value;
    }

    const auto float_expr = dynamic_cast<const Float*>(expr_ptr);
    if (nullptr != float_expr) {
        return float_expr->value;
    }
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
    }

    cout << endl;
}
