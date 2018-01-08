/* This file contains the global values for reserved keywords, Identifier, Number, IF, WHILE etc. 	*/
/* also some default values for the return used in other files 										*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BSIZE 128
#define NONE -1
#define EOS '\0'
#define NUM 256
#define DIV 257
#define MOD 258
#define ID 259
#define DONE 260
#define BEGIN 400
#define IF 405
#define ENDIF 406
#define WHILE 410
#define ENDWHILE 411
#define END 401
#define NOT_FOUND 0
#define FOUND 1
#define COMPAR 425
#define PE 465
#define ME 462

#define EQ 500
#define CONS 501
#define INTTOKEN 502

int tokenval;
int lineno;





