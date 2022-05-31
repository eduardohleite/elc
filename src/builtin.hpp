# pragma once

#include <vector>

namespace ELang {
namespace Runtime {

class Value;

Value builtin_add(std::vector<Value> params);
Value builtin_sub(std::vector<Value> params);
Value builtin_mul(std::vector<Value> params);
Value builtin_div(std::vector<Value> params);

} // namespace Runtime
} // namespace ELang