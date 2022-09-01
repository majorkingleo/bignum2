
%code requires {
#include <BigInt.h>
#include <list>
#include <memory>

extern std::list<std::shared_ptr<BigNum2::BigInt>> allocated_numbers;
}

%{
#include <iostream>
#include <string>
#include <map>
#include "lex.yy.h"
#include "y.tab.h"

using namespace BigNum2;

std::list<std::shared_ptr<BigNum2::BigInt>> allocated_numbers;
static std::map<std::string, BigNum2::BigInt> vars;

inline void yyerror(const char *s) { 
    std::cout << s << std::endl; 
    allocated_numbers.clear(); 
}

%}



%union { BigNum2::BigInt *i; std::string *s; }

%token tBATATA
%token<i> tINT
%token<s> tVAR
%type<i> expr

/* %destructor { std::cout << "here\n"; delete $$; } <i> */

%right '='
%left '+' '-'
%left '*' '/' '%'
%right tBATATA

%%

list: stmt
    | list stmt
    ;

stmt: expr ','
    | expr '\n'          { std::cout << *$1 << std::endl; allocated_numbers.clear(); }
    ;

expr: tINT                          { *$$ = *$1; }
    | tVAR                          { *$$ = vars[*$1];  delete $1; }
    | tVAR '=' expr                 { *$$ = vars[*$1];  vars[*$1] = *$3; delete $1; }
    | expr '+' expr                 { *$$ = *$1 + *$3; }
    | expr '-' expr                 { *$$ = *$1 - *$3; }
    | expr '*' expr                 { *$$ = *$1 * *$3; }
    | expr '!'                      { *$$ = faculty(*$1); }
    /* | expr '/' expr              { $$ = $1 / $3; } */
    /* | expr '%' expr              { $$ = $1 % $3; } */
    | '+' expr  %prec tBATATA       { *$$ =  *$2; }
    | '-' expr  %prec tBATATA       { *$$ = -(*$2); }
    | '(' expr ')'                  { $$ =  $2; }
    ;

%%
extern int yylex();
