#include "vm.hpp"
#include "operators.hpp"

using namespace ELang::Runtime;

Value PlusOperator::eval(Value lhs, Value rhs) const {
    return Value(std::get<long>(lhs.value) + std::get<long>(rhs.value));
}

Value MinusOperator::eval(Value lhs, Value rhs) const {
    return Value(std::get<long>(lhs.value) - std::get<long>(rhs.value));
}

Value MultiplyOperator::eval(Value lhs, Value rhs) const {
    return Value(std::get<long>(lhs.value) * std::get<long>(rhs.value));
}

Value DivideOperator::eval(Value lhs, Value rhs) const {
    return Value(std::get<long>(lhs.value) / std::get<long>(rhs.value));
}