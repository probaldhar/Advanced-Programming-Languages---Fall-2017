/* This file generate an error message and exit the program */
#include "global.h"

/* This function print error message with the line number in the display and exit the program */
error(char * m)
{

	// Removing the output File from folder
	if ( remove(storeOutputFileName) != 0 ) {
		fprintf(stderr, "output file cannot be removed.\n");
		exit(-1);
	}

  	fprintf(stderr, "line %d: %s\n", lineno, m);
  	exit(1);
}
