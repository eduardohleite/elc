%{
#include "../elang.hpp"

ELang::Meta::Block *main_block;

extern int yylex();
void yyerror(const char *s) { printf("ERROR: %s", s); }
%}

%union {
    ELang::Meta::Node *node;
    ELang::Meta::Block *block;
    ELang::Meta::Expression *expression;
    ELang::Meta::Statement *statement;
    //std::vector<ELang::Meta::Expression*> *expression_vec;
    std::string *string;
    int token;
}

%token <string> TINTEGER
//%token <token> TLPAREN TRPAREN
%token <token> TPLUS TMINUS TMUL TDIV

%type <expression> numeric expression
%type <block> program statements
%type <statement> statement
%type <token> arithmetic

%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

program : statements { main_block = $1; }
        ;

statements : statement { $$ = new ELang::Meta::Block(); $$->statements.push_back($<statement>1); }
           | statements statement { $1->statements.push_back($<statement>2); }
           ;

statement : expression { $$ = new ELang::Meta::ExpressionStatement(*$1); }
          ;

numeric : TINTEGER { $$ = new ELang::Meta::Integer(atol($1->c_str())); delete $1; }
        ;

expression: numeric
          | expression arithmetic expression { $$ = new ELang::Meta::ArithmeticOperator(*$1, $2, *$3); }
          ;

arithmetic: TPLUS
          | TMINUS
          | TMUL
          | TDIV
          ;

%%