#pragma once

#include "elang.hpp"

namespace ELang {
namespace Runtime {

class Interpreter {
public:
    Interpreter() { }
    ~Interpreter() { }

    void run(const ELang::Meta::Block *program) const;

protected:
    long eval_expression(const ELang::Meta::Expression &expression) const;
};

}
}