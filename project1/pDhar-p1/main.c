/* This is the main file for the project 1, it opens the file to read and 			*/
/* calls init() which add some lexeme in the symbol table 							*/
/* and then it calls the parse() function to parse the program written in the file 	*/
/* it also includes global.h for the default values used in other files 			*/

#include <stdio.h>
#include "global.h"

main(int argc, char **argv)
{

	if ( argc < 2 ) {
		printf("Usage: ./compiler <fileName>\n");
		exit(-1);
	}

	openFile(argv[1]);
	init();
	// printf("\n\nEnter arithmetic expressions terminated\n");
	// printf("with semicolons (;).\n");
	// printf("Press <ctrl> c to quit\n\n->"); 
	parse();
	printf("Sucessfully compiled.\n");
	closeFile();
	exit(0);
}
