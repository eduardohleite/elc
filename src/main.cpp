#include <iostream>
#include "elang.hpp"
#include "vm.hpp"

using namespace ELang::Meta;
using namespace ELang::Runtime;
using namespace std;

extern Block* main_block;
extern int yyparse();

int main(int argc, char **argv) {
    cout << "E Language Compiler v0.1p0" << endl << endl;

    yyparse();

    Interpreter runtime;
    runtime.register_builtins();

    runtime.run(main_block);

    return 0;
}