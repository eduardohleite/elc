#include "vm.hpp"
#include "operators.hpp"

using namespace ELang::Runtime;

Value PlusOperator::eval(Value lhs, Value rhs) const {
    if (lhs.type == Type::Integer && rhs.type == Type::Integer) {
        return Value(std::get<long>(lhs.value) + std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Integer && rhs.type == Type::Float) {
        return Value(std::get<long>(lhs.value) + std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Integer) {
        return Value(std::get<double>(lhs.value) + std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Float) {
        return Value(std::get<double>(lhs.value) + std::get<double>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}

Value MinusOperator::eval(Value lhs, Value rhs) const {
    if (lhs.type == Type::Integer && rhs.type == Type::Integer) {
        return Value(std::get<long>(lhs.value) - std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Integer && rhs.type == Type::Float) {
        return Value(std::get<long>(lhs.value) - std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Integer) {
        return Value(std::get<double>(lhs.value) - std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Float) {
        return Value(std::get<double>(lhs.value) - std::get<double>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}

Value MultiplyOperator::eval(Value lhs, Value rhs) const {
    if (lhs.type == Type::Integer && rhs.type == Type::Integer) {
        return Value(std::get<long>(lhs.value) * std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Integer && rhs.type == Type::Float) {
        return Value(std::get<long>(lhs.value) * std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Integer) {
        return Value(std::get<double>(lhs.value) * std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Float) {
        return Value(std::get<double>(lhs.value) * std::get<double>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}

Value DivideOperator::eval(Value lhs, Value rhs) const {
    if (lhs.type == Type::Integer && rhs.type == Type::Integer) {
        return Value(std::get<long>(lhs.value) / std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Integer && rhs.type == Type::Float) {
        return Value(std::get<long>(lhs.value) / std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Integer) {
        return Value(std::get<double>(lhs.value) / std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Float) {
        return Value(std::get<double>(lhs.value) / std::get<double>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}