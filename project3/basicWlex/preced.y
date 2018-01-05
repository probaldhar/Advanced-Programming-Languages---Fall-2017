%{
#include <ctype.h>
#include <stdio.h>
#define YYSTYPE double
#include "lex.yy.c"
%}
%token NUMBER
%left '+' '-'
%left '*' '/'

%%
lines    : lines expr '\n'   {printf("%g\n", $2);}
	 | error '\n' {yyerror("error\n");
		       yyerrok;}
	 |   /* e*/
	 ;
expr     : expr '*' expr   { $$ = $1 * $3; }
	 | expr '/' expr   { $$ = $1 / $3; }
         | expr '+' expr   { $$ = $1 + $3; }
         | expr '-' expr   { $$ = $1 - $3; }
         | '(' expr ')'    { $$ = $2; }
	 | NUMBER 
	 ;
%%

main()
{
  return yyparse();
}
int yywrap()
{
return 1;
}

yyerror(char * s)
{
  printf("error is %s\n", s);
}
