%option noyywrap
%{
#include <cstdlib>
#include <string>
#include <BigInt.h>
#include "y.tab.h"
%}
%%
[_[:alpha:]][_[:alnum:]]*     yylval.s = new std::string(yytext);  return tVAR;
[[:digit:]]+                  { 
                                auto val = std::make_shared<BigNum2::BigInt>(yytext); 
                                yylval.i = val.get(); 
                                allocated_numbers.push_back(val); 
                                return tINT;
                              }
[-+*/%=^\n,!]                 return *yytext;
.                             ; /* ignore all the rest */
%%

