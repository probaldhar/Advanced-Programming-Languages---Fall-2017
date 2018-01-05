final:	main.o emitter.o parser.o lexer.o symbol.o init.o 
	gcc -o final main.o init.o emitter.o parser.o lexer.o symbol.o

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

init.o:	init.c global.h
	gcc -c init.c

clean: 
	rm *.o final
