/* This is the main file for the project 1, it opens the file to read and 			*/
/* calls init() which add some lexeme in the symbol table 							*/
/* and then it calls the parse() function to parse the program written in the file 	*/
/* it also includes global.h for the default values used in other files 			*/

#include <stdio.h>
#include "global.h"

/*	Main function of the compiler program	*/
main(int argc, char **argv)
{

	// check for file name in the second argument of the command line
	if ( argc < 2 ) {
		printf("Usage: ./compiler <fileName>\n");
		exit(-1);
	}

	// Loop variable
	int i;

	// Register counter
	registerCounter = 1;
	labelCounter = 1;
	IOCounter = 1;

	// Temp array counter
	tempElementCounter = 0;

	// Initialize stack
	StackInit(&stack, MAXSIZE);

	for ( i = 0; i < MAXSIZE; i++ )
    {
        temp[i] = (char *)malloc(sizeof(char) * MAXSIZE);
    }

    // Opening the file to read and a file to write
	openFile(argv[1]);

	// initialize the symbol table
	init();

	strcpy(storeOutputFileName ,argv[1]);

	// just printing the filename in the Command Line
	strtok(storeOutputFileName, ".");
	strcat(storeOutputFileName, ".dat");

	// start parsing the code from file
	parse();
	// printf("Sucessfully compiled.\n");

	// Closing both files
	closeFile();

	printf("Code generated in %s file\n", storeOutputFileName);

	// printToCheck();

	// Destroy the stack
	StackDestroy(&stack);

	exit(0);
}
