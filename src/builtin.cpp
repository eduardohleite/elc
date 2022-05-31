#include "builtin.hpp"
#include "vm.hpp"

using namespace ELang::Runtime;

Value ELang::Runtime::builtin_add(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

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

Value ELang::Runtime::builtin_sub(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

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

Value ELang::Runtime::builtin_mul(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

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

Value ELang::Runtime::builtin_div(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

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

Value ELang::Runtime::builtin_not(std::vector<Value> params) {
    if (params.size() != 1) {
        // TODO: invalid operand count
    }

    auto expr = params.at(0);

    if (expr.type == Type::Boolean) {
        return Value(!std::get<bool>(expr.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}