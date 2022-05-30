#include "vm.hpp"
#include "operators.hpp"
#include "gen/parser.hpp"

using namespace ELang::Runtime;
using namespace ELang::Meta;
using namespace std;


long Interpreter::eval_expression(const Expression &expression) const {
    // check for expression types
    auto expr_ptr = &expression;

    auto arithmetic_expr = dynamic_cast<const ArithmeticExpression *>(expr_ptr);
    if (nullptr != arithmetic_expr) {
        auto lhs_value = eval_expression(arithmetic_expr->lhs);
        auto rhs_value = eval_expression(arithmetic_expr->rhs);

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

    auto int_expr = dynamic_cast<const Integer *>(expr_ptr);
    if (nullptr != int_expr) {
        return int_expr->value;
    }
}


void Interpreter::run(const Block *program) const {
    for (auto it = program->statements.begin(); it != program->statements.end(); it++) {
        auto statement = *it;

        // check for statement types
        auto expression_statement = dynamic_cast<ExpressionStatement *>(statement);
        if (nullptr != expression_statement) {
            auto res = eval_expression(expression_statement->expression);
            cout << "Evaluated: " << res << endl;
        }
    }
}
