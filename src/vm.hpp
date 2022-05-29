#pragma once

#include "elang.hpp"

namespace ELang {
namespace Runtime {

class Interpreter {
public:
    Interpreter() { }
    ~Interpreter() { }

    void run(ELang::Meta::Block *program);
};

}
}