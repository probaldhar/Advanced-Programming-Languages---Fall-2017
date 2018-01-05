compiler:	main.o emitter.o parser.o lexer.o symbol.o error.o stack.o
	gcc -Wall -o compiler main.o emitter.o parser.o lexer.o symbol.o error.o stack.o

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

stack.o: stack.c global.h
	gcc -c stack.c

clean: 
	rm compiler *.o *.dat
