%{
#include <ctype.h>
#include <stdio.h>
#define YYSTYPE double
#include "lex.yy.c"
%}
%token NUMBER BEGINNING IF ELSE ENDIF WHILE ENDWHILE END ID GE LE EE PE ME NE INT COMMENT
%left '+' '-'
%left '*' '/'

%%
program		: BEGINNING stmt END { printf("Successfully compiled.\n"); }

stmt    	: stmt selector
	 	 	| stmt iterator
	 	 	| stmt assignment
	 	 	| stmt declaration
	 	 	| error 	 {  yyerror("error\n");
		   	    			yyerrok; exit(1); }
	 	 	|   /* e*/
	 	 	;

expr     	: expr '*' expr   { $$ = $1 * $3; }
	 	 	| expr '/' expr   { $$ = $1 / $3; }
         	| expr '+' expr   { $$ = $1 + $3; }
         	| expr '-' expr   { $$ = $1 - $3; }
         	| '(' expr ')'    { $$ = $2; }
	 	 	| NUMBER 
	 	 	| ID
	 	 	;

selector 	: IF '(' condStmt ')' stmt ENDIF
			| IF '(' condStmt ')' stmt ELSE stmt ENDIF
		 	;

iterator	: WHILE '(' condStmt ')' stmt ENDWHILE
			;

assignment	: ID '=' expr ';'
			;

condStmt	: ID GE expr 
			| ID LE expr
			| ID EE expr
			| ID PE expr
			| ID ME expr
			| ID NE expr
			| ID '>' expr
			| ID '<' expr
			;

declaration : INT ID ';'
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
