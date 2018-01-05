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
#define ELSE 407
#define WHILE 410
#define ENDWHILE 411
#define END 401
#define NOT_FOUND 0
#define FOUND 1
#define COMPAR 425

/****
	Global Constants for comparison operators
****/
#define EE 550
#define LE 551
#define GE 552
#define NE 553
#define PE 554
#define ME 555

#define EQ 500
#define CONS 501
#define INTTOKEN 502

#define READ 510
#define WRITE 511

// value of the token
int tokenval;

// keeping track of the line number 
int lineno;

// Flag to check redeclaration
int lookupFlag;

// lexbuf to store the lexeme in case of ID
char lexbuf[BSIZE];

// Temp string to store the code to generate code properly
char * codeString, *codeStringTemp, *localCodeString, *localCodeStringWhile, storeOutputFileName[BSIZE];

////////////// STACK CONSTANTS, struct and FUNCTIONS ///////////////////

// MAXSIZE for the stack
#define MAXSIZE 1000

// File pointer to write file
FILE * fpWrite;

/**
 *	Register and label counter number.
	1 - registerCounter
	2 - labelCounter
    3 - IOCounter
*/

int registerCounter;
int labelCounter;
int IOCounter;

// Counter to keep track of the global *temp[]
int tempElementCounter;

/*
 * Type: stackT
 * --------------
 * This is the type for a stack, i.e., it is a type that
 * holds the information necessary to keep track of a stack.
 * It has a pointer `contents' to a dynamically-allocated
 * array (used to hold the contents of the stack), an integer
 * `maxSize' that holds the size of this array (i.e., the
 * maximum number of things that can be held in the stack),
 * and another integer `top,' which stores the array index of
 * the element at the top of the stack.
 */

typedef struct {
  char *contents[MAXSIZE];
  int maxSize;
  int top;
} stackT;

// Temp string of array to store the postfix expressions.
char *temp[MAXSIZE];

// string to store the converted string that we got from NUM
char tempStr[MAXSIZE];

/* A stack to hold set of strings. */
stackT stack;

/*
 * 
 * A new stack variable is initialized.  The initialized
 * stack is made empty.  MaxSize is used to determine the
 * maximum number of strings that can be held in the
 * stack.
 */

void StackInit(stackT *stackP, int maxSize);

/* 
 * This function frees all memory associated with the stack.
 * The `stack' variable may not be used again unless
 * StackInit(&stack, maxSize) is first called on the stack.
 */

void StackDestroy(stackT *stackP);

/*
 * 
 * These are the fundamental stack operations that add an element to
 * the top of the stack and remove an element from the top of the stack.
 * A call to StackPop on an empty stack or to StackPush on a full stack
 * is an error.  Make use of StackIsEmpty()/StackIsFull() (see below)
 * to avoid these errors.
 */

void StackPush(stackT *stackP, char *element);
char *StackPop(stackT *stackP);

/*
 * 
 * These return a true value if the stack is empty
 * or full (respectively).
 */

int StackIsEmpty(stackT *stackP);
int StackIsFull(stackT *stackP);

void display(stackT *stackP);

char * getLabelRegister(char *reg);

void increaseLabelCounter();

int stringIsalnum ( char *s );

char *exprCodeGen ();

// This is the function I'm getting warning
void insertIntoTemp( char *aString );

void insertIntoTempAsChar( char aChar );

// void printToCheck();

void emptyTemp ();


