# pragma once

#include <vector>

namespace ELang {
namespace Runtime {

class Value;

// arithmetic operators
Value builtin_add(const std::vector<Value>& params);
Value builtin_sub(const std::vector<Value>& params);
Value builtin_mul(const std::vector<Value>& params);
Value builtin_div(const std::vector<Value>& params);

// binary operators
Value builtin_not(const std::vector<Value>& params);
Value builtin_and(const std::vector<Value>& params);
Value builtin_or(const std::vector<Value>& params);

// comparison operators
Value builtin_eq(const std::vector<Value>& params);
Value builtin_ne(const std::vector<Value>& params);
Value builtin_gte(const std::vector<Value>& params);
Value builtin_gt(const std::vector<Value>& params);
Value builtin_lte(const std::vector<Value>& params);
Value builtin_lt(const std::vector<Value>& params);

// vectors
Value builtin_zeros(const std::vector<Value>& params);
Value builtin_ones(const std::vector<Value>& params);
Value builtin_length(const std::vector<Value>& params);
Value builtin_range(const std::vector<Value>& params);
Value builtin_push_bang(const std::vector<Value>& params);
Value builtin_pop_bang(const std::vector<Value>& params);
Value builtin_popat_bang(const std::vector<Value>& params);
Value builtin_at(const std::vector<Value>& params);
Value builtin_in(const std::vector<Value>& params);

// pretty print
Value builtin_show(const std::vector<Value>& params);

// strings
Value builtin_substr(const std::vector<Value>& params);
Value builtin_lower(const std::vector<Value>& params);
Value builtin_upper(const std::vector<Value>& params);
Value builtin_lower_bang(const std::vector<Value>& params);
Value builtin_upper_bang(const std::vector<Value>& params);

} // namespace Runtime
} // namespace ELang