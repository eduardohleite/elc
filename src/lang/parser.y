%{
#include "../elang.hpp"

ELang::Meta::Block *main_block;

extern int yylex();
void yyerror(const char *s) { printf("ERROR: %s", s); }
%}

%union {
    ELang::Meta::Node* node;
    ELang::Meta::Block* block;
    ELang::Meta::Expression* expression;
    ELang::Meta::Statement* statement;
    ELang::Meta::Identifier* identifier;
    std::vector<ELang::Meta::Expression*> *expressions;
    std::string* string;
    int token;
}

%token <string> TIDENTIFIER TINTEGER TFLOAT
%token <string> TTRUE TFALSE
%token <token> TLPAREN TRPAREN TCOMMA
%token <token> TPLUS TMINUS TMUL TDIV
%token <token> TAND TOR TXOR TNOT

%type <identifier> identifier
%type <expression> number boolean expression
%type <expressions> arguments
%type <block> program statements
%type <statement> statement
%type <token> arithmetic binary

%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

program    : statements { main_block = $1; }
           ;

statements : statement { $$ = new ELang::Meta::Block(); $$->statements.push_back($<statement>1); }
           | statements statement { $1->statements.push_back($<statement>2); }
           ;

statement  : expression { $$ = new ELang::Meta::ExpressionStatement(*$1); }
           ;

identifier : TIDENTIFIER { $$ = new ELang::Meta::Identifier(*$1); delete $1; }
           ;

number     : TINTEGER { $$ = new ELang::Meta::Integer(atol($1->c_str())); delete $1; }
           | TFLOAT { $$ = new ELang::Meta::Float(atof($1->c_str())); delete $1; }
           ;

boolean    : TTRUE { $$ = new ELang::Meta::Boolean(true); delete $1; }
           | TFALSE { $$ = new ELang::Meta::Boolean(false); delete $1; }
           ;

expression : identifier TLPAREN arguments TRPAREN { $$ = new ELang::Meta::FunctionCall(*$1, *$3); delete $3; }
           | number
           | boolean
           | expression arithmetic expression { $$ = new ELang::Meta::ArithmeticExpression(*$1, $2, *$3); }
           | TNOT expression { $$ = new ELang::Meta::NegatedBinaryExpression(*$2); }
           | expression binary expression { $$ = new ELang::Meta::BinaryExpression(*$1, $2, *$3); }
           | TLPAREN expression TRPAREN { $$ = $2; }
           ;

arguments  : { $$ = new std::vector<ELang::Meta::Expression*>(); }
           | expression { $$ = new std::vector<ELang::Meta::Expression*>(); $$->push_back($1); }
           | arguments TCOMMA expression { $1->push_back($3); }
           ;

arithmetic : TPLUS
           | TMINUS
           | TMUL
           | TDIV
           ;

binary     : TAND
           | TOR
           | TXOR
           ;

%%