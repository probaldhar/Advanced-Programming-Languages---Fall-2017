%{
#include "y.tab.h"
extern YYSTYPE yylval;
%}

number     [0-9]+|[0-9]+\.[0-9]+
%%
[ ]        { /* skip blank spaces */ }
{number}   { sscanf(yytext, "%lf", &yylval );
	     return NUMBER; }
\n|.       { return yytext[0]; }
