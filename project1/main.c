#include <stdio.h>
#include "global.h"

main()
{
  init();
  printf("\n\nEnter arithmetic expressions terminated\n");
  printf("with semicolons (;).\n");
  printf("Press <ctrl> c to quit\n\n->"); 
  parse();
  exit(0);
}
