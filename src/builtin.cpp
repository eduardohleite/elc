#include "builtin.hpp"
#include "vm.hpp"

#include <memory>
#include <algorithm>
#include <cctype>
#include <string>

using namespace ELang::Runtime;

Value ELang::Runtime::builtin_add(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

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
    else if (lhs.type == Type::String && rhs.type == Type::String) {
        return Value(std::make_shared<std::string>(*std::get<std::shared_ptr<std::string>>(lhs.value)
             + *std::get<std::shared_ptr<std::string>>(rhs.value)));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_sub(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

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
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_mul(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

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
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_div(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

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
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_not(const std::vector<Value>& params) {
    if (params.size() != 1) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1" << std::endl;
        throw -1;
    }

    const auto expr = params.at(0);

    if (expr.type == Type::Boolean) {
        return Value(!std::get<bool>(expr.value));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_and(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

    if (lhs.type == Type::Boolean && rhs.type == Type::Boolean) {
        return Value(std::get<bool>(lhs.value) && std::get<bool>(rhs.value));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_or(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

    if (lhs.type == Type::Boolean && rhs.type == Type::Boolean) {
        return Value(std::get<bool>(lhs.value) || std::get<bool>(rhs.value));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_eq(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

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
    else if (lhs.type == Type::String && rhs.type == Type::String) {
        return Value(*std::get<std::shared_ptr<std::string>>(lhs.value) == *std::get<std::shared_ptr<std::string>>(rhs.value));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_ne(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

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
    else if (lhs.type == Type::String && rhs.type == Type::String) {
        return Value(*std::get<std::shared_ptr<std::string>>(lhs.value) != *std::get<std::shared_ptr<std::string>>(rhs.value));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_gte(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

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
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_gt(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

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
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_lte(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

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
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_lt(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto lhs = params.at(0);
    const auto rhs = params.at(1);

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
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_zeros(const std::vector<Value>& params) {
    if (params.size() != 1) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1" << std::endl;
        throw -1;
    }

    const auto n = params.at(0);
    if (n.type == Type::Integer) {
        const auto vec = std::make_shared<std::vector<Value>>();
        const auto nval = std::get<long>(n.value);

        for (long i = 0; i < nval; ++i) {
            vec->push_back(Value(0l));
        }

        return Value(vec);
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_ones(const std::vector<Value>& params) {
    if (params.size() != 1) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1" << std::endl;
        throw -1;
    }

    auto n = params.at(0);
    if (n.type == Type::Integer) {
        const auto vec = std::make_shared<std::vector<Value>>();
        const auto nval = std::get<long>(n.value);

        for (long i = 0; i < nval; ++i) {
            vec->push_back(Value(1l));
        }

        return Value(vec);
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_length(const std::vector<Value>& params) {
    if (params.size() != 1) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1" << std::endl;
        throw -1;
    }

    const auto vec = params.at(0);

    if (vec.type == Type::Vector) {
        const auto vecval = std::get<std::shared_ptr<std::vector<Value>>>(vec.value);
        return Value(static_cast<long>(vecval->size()));
    }
    else if (vec.type == Type::String) {
        const auto strval = std::get<std::shared_ptr<std::string>>(vec.value);
        return Value(static_cast<long>(strval->length()));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_range(const std::vector<Value>& params) {
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
       std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1 or 2" << std::endl;
        throw -1;
    }

    if (max.type == Type::Integer && (! has_min || (has_min && min.type == Type::Integer))) {
        const auto vec = std::make_shared<std::vector<Value>>();
        const auto minval = has_min ? std::get<long>(min.value) - 1 : 0;
        const auto maxval = std::get<long>(max.value);

        for (long i = minval; i < maxval; ++i) {
            vec->push_back(Value(i+1));
        }

        return Value(vec);
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}



Value ELang::Runtime::builtin_push_bang(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto vec = params.at(0);
    const auto val = params.at(1);

    if (vec.type == Type::Vector) {
        const auto vecval = std::get<std::shared_ptr<std::vector<Value>>>(vec.value);
        
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
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_pop_bang(const std::vector<Value>& params) {
    if (params.size() != 1) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1" << std::endl;
        throw -1;
    }

    const auto vec = params.at(0);

    if (vec.type == Type::Vector) {
        const auto vecval = std::get<std::shared_ptr<std::vector<Value>>>(vec.value);
        const auto last_index = vecval->size();

        if (last_index > 0) {
            const auto grab = vecval->at(last_index - 1);
            vecval->pop_back();
            return Value(grab);
        }
        else {
            std::cerr << "Out of bounds." << std::endl;
            throw -1;
        }
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_at(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto vec = params.at(0);
    const auto index = params.at(1);

    if (vec.type == Type::Vector && index.type == Type::Integer) {
        const auto vecval = std::get<std::shared_ptr<std::vector<Value>>>(vec.value);
        const auto indexval = std::get<long>(index.value);

        //TODO: out of bounds
        return Value(vecval->at(indexval-1)); /* 1-based array */
    }
    else if (vec.type == Type::String && index.type == Type::Integer) {
        const auto strval = std::get<std::shared_ptr<std::string>>(vec.value);
        const auto indexval = std::get<long>(index.value);

        // TODO: out of bounds
        return Value(std::make_shared<std::string>(1, strval->at(indexval-1)));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_in(const std::vector<Value>& params) {
    if (params.size() != 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 2" << std::endl;
        throw -1;
    }

    const auto vec = params.at(0);
    const auto val = params.at(1);

    if (vec.type == Type::Vector) {
        const auto vecval = std::get<std::shared_ptr<std::vector<Value>>>(vec.value);

        return Value(std::find_if(vecval->begin(), vecval->end(),
            [val](const ELang::Runtime::Value v) { return  v.type == val.type && v.value == val.value; }) != vecval->end());
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_show(const std::vector<Value>& params) {
    if (params.size() != 1) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1" << std::endl;
        throw -1;
    }

    const auto val = params.at(0);

    switch (val.type) {
        case Type::Integer:
            std::cout << std::get<long>(val.value) << " (type: Integer)";
            break;
        case Type::Float:
            std::cout << std::get<double>(val.value) << " (type: Float)";
            break;
        case Type::Boolean:
            std::cout << (std::get<bool>(val.value) ? "true" : "false") << " (type: Boolean)";
            break;
        case Type::String:
            std::cout << "'" << *std::get<std::shared_ptr<std::string>>(val.value) << "' (type: String)";
            break;
        case Type::Void:
            std::cout << " (type: Void)" << std::endl;
            break;
        case Type::Vector:
            const auto vec = std::get<std::shared_ptr<std::vector<Value>>>(val.value);
            std::cout << "Vector with " << vec->size() << " elements:" << std::endl;
            for (std::size_t i = 0; i< vec->size(); ++i) {
                std::cout << i << ": ";
                const auto el = vec->at(i);

                switch (el.type) {
                    case Type::Integer:
                        std::cout << std::get<long>(el.value) << " (type: Integer)";
                        break;
                    case Type::Float:
                        std::cout << std::get<double>(el.value) << " (type: Float)";
                        break;
                    case Type::Boolean:
                        std::cout << (std::get<bool>(el.value) ? "true" : "false") << " (type: Boolean)";
                        break;
                    case Type::String:
                        std::cout << "'" << *std::get<std::shared_ptr<std::string>>(el.value) << "' (type: String)";
                        break;
                    case Type::Vector:
                        std::cout << "(type: Vector)";
                        break;
                    default:
                        break;
                }

                std::cout << std::endl;
            }
            break;
    }

    std::cout << std::endl;
    return Value();
}

Value ELang::Runtime::builtin_substr(const std::vector<Value>& params) {
    auto has_start = false;
    Value start, len;

    if (params.size() == 2) {
        len = params.at(1);
    }
    else if (params.size() == 3) {
        has_start = true;

        start = params.at(1);
        len = params.at(2);
    }
    else {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1 or 2" << std::endl;
        throw -1;
    }

    const auto str = params.at(0);

    if (str.type == Type::String && len.type == Type::Integer && (!has_start || start.type == Type::Integer)) {
        const auto full_str = std::get<std::shared_ptr<std::string>>(str.value);
        const auto start_val = has_start ? std::get<long>(start.value) - 1 : 0;

        return Value(std::make_shared<std::string>(full_str->substr(start_val, std::get<long>(len.value))));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_lower(const std::vector<Value>& params) {
    if (params.size() != 1) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1" << std::endl;
        throw -1;
    }

    const auto str = params.at(0);
    
    if (str.type == Type::String) {
        const auto strval = std::get<std::shared_ptr<std::string>>(str.value);
        std::string result;

        std::transform(strval->begin(), strval->end(), result.begin(),
            [](unsigned char c){ return std::tolower(c); });

        return Value(std::make_shared<std::string>(result));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_upper(const std::vector<Value>& params) {
    if (params.size() != 1) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1" << std::endl;
        throw -1;
    }

    const auto str = params.at(0);
    
    if (str.type == Type::String) {
        const auto strval = std::get<std::shared_ptr<std::string>>(str.value);
        std::string result;

        std::transform(strval->begin(), strval->end(), result.begin(),
            [](unsigned char c){ return std::toupper(c); });

        return Value(std::make_shared<std::string>(result));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_lower_bang(const std::vector<Value>& params) {
    if (params.size() != 1) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1" << std::endl;
        throw -1;
    }

    const auto str = params.at(0);
    
    if (str.type == Type::String) {
        const auto strval = std::get<std::shared_ptr<std::string>>(str.value);

        std::transform(strval->begin(), strval->end(), strval->begin(),
            [](unsigned char c){ return std::tolower(c); });

        return Value(std::make_shared<std::string>(*strval));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_upper_bang(const std::vector<Value>& params) {
    if (params.size() != 1) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1" << std::endl;
        throw -1;
    }

    const auto str = params.at(0);
    
    if (str.type == Type::String) {
        const auto strval = std::get<std::shared_ptr<std::string>>(str.value);

        std::transform(strval->begin(), strval->end(), strval->begin(),
            [](unsigned char c){ return std::toupper(c); });

        return Value(std::make_shared<std::string>(*strval));
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

Value ELang::Runtime::builtin_split(const std::vector<Value>& params) {
    const auto param_cnt = params.size();

    if (param_cnt < 1 || param_cnt > 2) {
        std::cerr << "Invalid parameter count. Found " << params.size() << ". Expected 1 or 2" << std::endl;
        throw -1;
    }

    const auto str = params.at(0);

    if (str.type == Type::String) {
        std::string separator = " ";
        const auto strval = std::get<std::shared_ptr<std::string>>(str.value);

        if (param_cnt == 2) {
            const auto sep = params.at(1);

            if (sep.type != Type::String) {
                std::cerr << "Invalid parameter types" << std::endl;
                throw -1;
            }

            separator = *std::get<std::shared_ptr<std::string>>(sep.value);
        }

        size_t pos = 0, prev_pos = 0;
        const auto result = std::make_shared<std::vector<Value>>();
        while ((pos = strval->find(separator, prev_pos)) != std::string::npos) {
            result->push_back(Value(std::make_shared<std::string>(strval->substr(prev_pos, pos - prev_pos))));
            prev_pos = pos + 1;
        }

        if (prev_pos < strval->length()) {
            result->push_back(Value(std::make_shared<std::string>(strval->substr(prev_pos, pos - prev_pos))));
        }

        return Value(result);
    }
    else {
        std::cerr << "Invalid parameter types" << std::endl;
        throw -1;
    }
}

// Value ELang::Runtime::builtin_join(const std::vector<Value>& params) {
//     if (params.size() != 2) {
//         // TODO: invalid parameter count
//     }

//     const auto vec = params.at(0);
//     const auto sep = params.at(1);

//     if (vec.type == Type::Vector && sep.type == Type::String) {
//         const auto sepval = std::get<std::shared_ptr<std::string>>(sep.value);
//         const auto vecval = std::get<std::shared_ptr<std::vector<Value>>>(vec.value);

//         // TODO
//     }
//     else {
//         // TODO: error - invalid parameter types
//     }
// }