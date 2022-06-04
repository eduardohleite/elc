# pragma once

#include <vector>

namespace ELang {
namespace Runtime {

class Value;

// arithmetic operators
Value builtin_add(std::vector<Value> params);
Value builtin_sub(std::vector<Value> params);
Value builtin_mul(std::vector<Value> params);
Value builtin_div(std::vector<Value> params);

// binary operators
Value builtin_not(std::vector<Value> params);
Value builtin_and(std::vector<Value> params);
Value builtin_or(std::vector<Value> params);

// comparison operators
Value builtin_eq(std::vector<Value> params);
Value builtin_ne(std::vector<Value> params);
Value builtin_gte(std::vector<Value> params);
Value builtin_gt(std::vector<Value> params);
Value builtin_lte(std::vector<Value> params);
Value builtin_lt(std::vector<Value> params);

// vectors
Value builtin_zeros(std::vector<Value> params);
Value builtin_ones(std::vector<Value> params);
Value builtin_length(std::vector<Value> params);
Value builtin_range(std::vector<Value> params);
Value builtin_push_bang(std::vector<Value> params);
Value builtin_pop_bang(std::vector<Value> params);
Value builtin_popat_bang(std::vector<Value> params);
Value builtin_at(std::vector<Value> params);
Value builtin_in(std::vector<Value> params);

// pretty print
Value builtin_show(std::vector<Value> params);

} // namespace Runtime
} // namespace ELang