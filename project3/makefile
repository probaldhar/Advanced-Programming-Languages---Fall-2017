compiler: lex.yy.c y.tab.c
	gcc  y.tab.c -o compiler

y.tab.c y.tab.h : preced.y
		yacc -d preced.y

lex.yy.c : lex.l
	lex lex.l

clean: 
	rm y.tab.c y.tab.h lex.yy.c compiler
