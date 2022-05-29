#include <iostream>
#include "elang.hpp"

using namespace ELang::Meta;

extern Block* main_block;
extern int yyparse();

using namespace std;

int main(int argc, char **argv)
{
    cout << "E Language Compiler v0.1p0" << endl << endl;

    yyparse();

    cout << main_block << endl;
    return 0;
}