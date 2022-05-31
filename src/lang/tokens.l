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

"true"  SAVE_TOKEN; return TTRUE;
"false" SAVE_TOKEN; return TFALSE;

"and" return TOKEN(TAND);
"or"  return TOKEN(TOR);
"xor" return TOKEN(TXOR);
"not" return TOKEN(TNOT);

[a-zA-Z_][a-zA-Z0-9_]* SAVE_TOKEN; return TIDENTIFIER;

[0-9]+\.[0-9]* SAVE_TOKEN; return TFLOAT;
[0-9]+         SAVE_TOKEN; return TINTEGER;

"(" return TOKEN(TLPAREN);
")" return TOKEN(TRPAREN);
"," return TOKEN(TCOMMA);

"+" return TOKEN(TPLUS);
"-" return TOKEN(TMINUS);
"*" return TOKEN(TMUL);
"/" return TOKEN(TDIV);

. printf("Invalid token."); yyterminate();

%%