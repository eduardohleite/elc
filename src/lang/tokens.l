%{
#include <string>
#include "elang.hpp"
#include "parser.hpp"

#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() { }
%}

%%

[ \t\n] ;

[0-9]+ SAVE_TOKEN; return TINTEGER;

"(" return TOKEN(TLPAREN);
")" return TOKEN(TRPAREN);

"+" return TOKEN(TPLUS);
"-" return TOKEN(TMINUS);
"*" return TOKEN(TMUL);
"/" return TOKEN(TDIV);

. printf("Unknown token!n"); yyterminate();

%%