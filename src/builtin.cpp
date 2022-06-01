#include "builtin.hpp"
#include "vm.hpp"

#include <memory>
#include <algorithm>

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

Value ELang::Runtime::builtin_and(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

    if (lhs.type == Type::Boolean && rhs.type == Type::Boolean) {
        return Value(std::get<bool>(lhs.value) && std::get<bool>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}

Value ELang::Runtime::builtin_or(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

    if (lhs.type == Type::Boolean && rhs.type == Type::Boolean) {
        return Value(std::get<bool>(lhs.value) || std::get<bool>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}

Value ELang::Runtime::builtin_eq(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

    if (lhs.type == Type::Integer && rhs.type == Type::Integer) {
        return Value(std::get<long>(lhs.value) == std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Integer && rhs.type == Type::Float) {
        return Value(std::get<long>(lhs.value) == std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Integer) {
        return Value(std::get<double>(lhs.value) == std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Float) {
        return Value(std::get<double>(lhs.value) == std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Boolean && rhs.type == Type::Boolean) {
        return Value(std::get<bool>(lhs.value) == std::get<bool>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}

Value ELang::Runtime::builtin_ne(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

    if (lhs.type == Type::Integer && rhs.type == Type::Integer) {
        return Value(std::get<long>(lhs.value) != std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Integer && rhs.type == Type::Float) {
        return Value(std::get<long>(lhs.value) != std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Integer) {
        return Value(std::get<double>(lhs.value) != std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Float) {
        return Value(std::get<double>(lhs.value) != std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Boolean && rhs.type == Type::Boolean) {
        return Value(std::get<bool>(lhs.value) != std::get<bool>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}

Value ELang::Runtime::builtin_gte(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

    if (lhs.type == Type::Integer && rhs.type == Type::Integer) {
        return Value(std::get<long>(lhs.value) >= std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Integer && rhs.type == Type::Float) {
        return Value(std::get<long>(lhs.value) >= std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Integer) {
        return Value(std::get<double>(lhs.value) >= std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Float) {
        return Value(std::get<double>(lhs.value) >= std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Boolean && rhs.type == Type::Boolean) {
        return Value(std::get<bool>(lhs.value) >= std::get<bool>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}

Value ELang::Runtime::builtin_gt(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

    if (lhs.type == Type::Integer && rhs.type == Type::Integer) {
        return Value(std::get<long>(lhs.value) > std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Integer && rhs.type == Type::Float) {
        return Value(std::get<long>(lhs.value) > std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Integer) {
        return Value(std::get<double>(lhs.value) > std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Float) {
        return Value(std::get<double>(lhs.value) > std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Boolean && rhs.type == Type::Boolean) {
        return Value(std::get<bool>(lhs.value) > std::get<bool>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}

Value ELang::Runtime::builtin_lte(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

    if (lhs.type == Type::Integer && rhs.type == Type::Integer) {
        return Value(std::get<long>(lhs.value) <= std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Integer && rhs.type == Type::Float) {
        return Value(std::get<long>(lhs.value) <= std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Integer) {
        return Value(std::get<double>(lhs.value) <= std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Float) {
        return Value(std::get<double>(lhs.value) <= std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Boolean && rhs.type == Type::Boolean) {
        return Value(std::get<bool>(lhs.value) <= std::get<bool>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}

Value ELang::Runtime::builtin_lt(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid operand count
    }

    auto lhs = params.at(0);
    auto rhs = params.at(1);

    if (lhs.type == Type::Integer && rhs.type == Type::Integer) {
        return Value(std::get<long>(lhs.value) < std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Integer && rhs.type == Type::Float) {
        return Value(std::get<long>(lhs.value) < std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Integer) {
        return Value(std::get<double>(lhs.value) < std::get<long>(rhs.value));
    }
    else if (lhs.type == Type::Float && rhs.type == Type::Float) {
        return Value(std::get<double>(lhs.value) < std::get<double>(rhs.value));
    }
    else if (lhs.type == Type::Boolean && rhs.type == Type::Boolean) {
        return Value(std::get<bool>(lhs.value) < std::get<bool>(rhs.value));
    }
    else {
        // TODO: error - invalid operand types
    }
}

Value ELang::Runtime::builtin_zeros(std::vector<Value> params) {
    if (params.size() != 1) {
        // TODO: invalid parameter count
    }

    auto n = params.at(0);
    if (n.type == Type::Integer) {
        auto vec = std::make_shared<std::vector<Value>>();
        auto nval = std::get<long>(n.value);

        for (auto i = 0; i < nval; i++) {
            vec->push_back(Value(0l));
        }

        return Value(vec);
    }
    else {
        // TODO: error - invalid parameter types
    }
}

Value ELang::Runtime::builtin_ones(std::vector<Value> params) {
    if (params.size() != 1) {
        // TODO: invalid parameter count
    }

    auto n = params.at(0);
    if (n.type == Type::Integer) {
        auto vec = std::make_shared<std::vector<Value>>();
        auto nval = std::get<long>(n.value);

        for (auto i = 0; i < nval; i++) {
            vec->push_back(Value(1l));
        }

        return Value(vec);
    }
    else {
        // TODO: error - invalid parameter types
    }
}

Value ELang::Runtime::builtin_length(std::vector<Value> params) {
    if (params.size() != 1) {
        // TODO: invalid parameter count
    }

    auto vec = params.at(0);

    if (vec.type == Type::Vector) {
        auto vecval = std::get<std::shared_ptr<std::vector<Value>>>(vec.value);
        return Value(static_cast<long>(vecval->size()));
    }
    else {
        // TODO: error - invalid parameter types
    }
}

Value ELang::Runtime::builtin_range(std::vector<Value> params) {
    auto has_min = false;
    Value min, max;

    if (params.size() == 1) {
        max = params.at(0);
    }
    else if (params.size() == 2) {
        has_min = true;

        min = params.at(0);
        max = params.at(1);
    }
    else {
        // TODO: invalid parameter count
    }

    if (max.type == Type::Integer && (! has_min || (has_min && min.type == Type::Integer))) {
        auto vec = std::make_shared<std::vector<Value>>();
        auto minval = has_min ? std::get<long>(min.value) - 1 : 0;
        auto maxval = std::get<long>(max.value);

        for (auto i = minval; i < maxval; i++) {
            vec->push_back(Value(i+1));
        }

        return Value(vec);
    }
    else {
        // TODO: error - invalid parameter types
    }
}



Value ELang::Runtime::builtin_push_bang(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid parameter count
    }

    auto vec = params.at(0);
    auto val = params.at(1);

    if (vec.type == Type::Vector) {
        auto vecval = std::get<std::shared_ptr<std::vector<Value>>>(vec.value);
        
        switch(val.type) {
            case Type::Integer:
                vecval->push_back(std::get<long>(val.value));
                break;
            case Type::Boolean:
                vecval->push_back(std::get<bool>(val.value));
                break;
            case Type::Float:
                vecval->push_back(std::get<double>(val.value));
                break;
            case Type::Vector:
                vecval->push_back(std::get<std::shared_ptr<std::vector<Value>>>(val.value));
                break;
            default:
                // TODO: error
                break;
        }

        return Value(vec);
    }
    else {
        // TODO: error - invalid parameter types
    }
}

Value ELang::Runtime::builtin_pop_bang(std::vector<Value> params) {
    if (params.size() != 1) {
        // TODO: invalid parameter count
    }

    auto vec = params.at(0);

    if (vec.type == Type::Vector) {
        auto vecval = std::get<std::shared_ptr<std::vector<Value>>>(vec.value);
        auto last_index = vecval->size();

        if (last_index > 0) {
            auto grab = vecval->at(last_index - 1);
            vecval->pop_back();
            return Value(grab);
        }
        else {
            // TODO: error
        }
    }
    else {
        // TODO: error - invalid parameter types
    }
}

Value ELang::Runtime::builtin_at(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid parameter count
    }

    auto vec = params.at(0);
    auto index = params.at(1);

    if (vec.type == Type::Vector && index.type == Type::Integer) {
        auto vecval = std::get<std::shared_ptr<std::vector<Value>>>(vec.value);
        auto indexval = std::get<long>(index.value);

        //TODO: out of bounds
        return Value(vecval->at(indexval-1)); /* 1-based array */
    }
    else {
        // TODO: error - invalid parameter types
    }
}

Value ELang::Runtime::builtin_in(std::vector<Value> params) {
    if (params.size() != 2) {
        // TODO: invalid parameter count
    }

    const auto vec = params.at(0);
    const auto val = params.at(1);

    if (vec.type == Type::Vector) {
        auto vecval = std::get<std::shared_ptr<std::vector<Value>>>(vec.value);

        return Value(std::find_if(vecval->begin(), vecval->end(),
            [val](const ELang::Runtime::Value v) { return  v.type == val.type && v.value == val.value; }) != vecval->end());
    }
    else {
        // TODO: error - invalid parameter types
    }
}

