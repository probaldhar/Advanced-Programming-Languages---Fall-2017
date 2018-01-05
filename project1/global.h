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
#define WHILE 410
#define END 401
#define NOT_FOUND 0

int tokenval;
int lineno;



