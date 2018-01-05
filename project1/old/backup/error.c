/* This file generate an error message and exit the program */
#include "global.h"

/* This function print error message with the line number in the display and exit the program */
error(char * m)
{
  fprintf(stderr, "line %d: %s\n", lineno, m);
  exit(1);
}
