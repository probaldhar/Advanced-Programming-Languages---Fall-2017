%{
#include "y.tab.h"
extern YYSTYPE yylval;
%}

number     	[0-9]+|[0-9]+\.[0-9]+
id 			[A-Za-z]+[0-9]*|[A-Za-z]+[0-9]*\_[A-Za-z0-9]+
comment		\~[^\n]+
%%
[ \n\t]     { 	/* skip blank spaces */ }
{number}   	{ 	sscanf(yytext, "%lf", &yylval );
	     		return NUMBER; }
begin	   	{	return BEGINNING; }
if 		   	{ 	return IF; }
else 		{ 	return ELSE; }
endif		{ 	return ENDIF; }					
while 		{ 	return WHILE; }
endwhile	{ 	return ENDWHILE; }
end 		{ 	return END; }
">="		{ 	return GE; }
"<="		{ 	return LE; }
"=="		{ 	return EE; }
"+="		{ 	return PE; }
"-="		{ 	return ME; }
"!="		{ 	return NE; }
int			{ 	return INT; }
{comment}	{ 	 }
{id}        {
                yylval = *yytext - 'a';
                return ID;
            }
.         	{ 	return yytext[0]; }


