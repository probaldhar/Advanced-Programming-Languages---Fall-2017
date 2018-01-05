compiler:	main.o emitter.o parser.o lexer.o symbol.o error.o 
	gcc -o compiler main.o emitter.o parser.o lexer.o symbol.o error.o

main.o:	main.c global.h
	gcc -c main.c

emitter.o:emitter.c global.h
	gcc -c emitter.c

parser.o:parser.c global.h
	gcc -c parser.c

lexer.o:lexer.c global.h
	gcc -c lexer.c

symbol.o:symbol.c global.h
	gcc -c symbol.c

error.o:error.c global.h
	gcc -c error.c

clean: 
	rm compiler *.o
