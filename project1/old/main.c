#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

main()
{
  init();
  printf("\n\nEnter arithmetic expressions terminated\n");
  printf("with semicolons (;).\n");
  printf("Press <ctrl> D to quit\n\n->"); 
  parse();
  exit(0);
}
