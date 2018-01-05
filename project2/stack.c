/*
 * This is an array implementation of a character stack.
 * All operations of stack is doing in this file. Fox example: stack push, stack pop
 */

#include <stdio.h>
#include <stdlib.h>  /* for dynamic allocation */
#include <string.h>
#include <ctype.h>
#include "global.h"

/************************ Function Definitions **********************/

/*  Initializing the stack with the stack Struct and putting "\0" to every element to it    */
/*  It also allocate memory to every element of the stackT                                  */
void StackInit(stackT *stackP, int maxSize)
{
    int i;

    /* Allocate a new array to hold the contents. */

    for ( i = 0; i < maxSize; i++ )
    {
        stackP->contents[i] = (char *)malloc(sizeof(char) * maxSize);
        strcpy(stackP->contents[i], "\0");

    }


    stackP->maxSize = maxSize;
    stackP->top = -1;  /* I.e., empty */
}

/*  Destroing the stack by freeing all the memory holding by the elements of the stack  */
/*  It also put maxSize to 0 and top to -1                                              */
void StackDestroy(stackT *stackP)
{

    int i;

    /* Allocate a new array to hold the contents. */

    for ( i = 0; i < stackP->maxSize; i++ )
    {
        /* Get rid of array. */
        free(stackP->contents[i]);

    }

    stackP->maxSize = 0;
    stackP->top = -1;  /* I.e., empty */
}

/*  Push new element to the stack to the next available position in the stack        */
/*  Before pushing the new element to the stack it checkes if the stack is full or not  */
void StackPush(stackT *stackP, char *element)
{
  if (StackIsFull(stackP)) {
    fprintf(stderr, "Can't push element on stack: stack is full.\n");
    exit(1);  /* Exit, returning error code. */
  }

  /* Put information in array; update top. */

  strcpy(stackP->contents[++stackP->top], element);
}

/*  Pop or delete the element which is in the top of the stack      */
/*  It also checkes if the stack is empty or not before poping it   */
/*  It returns the top element of the Stack                         */
char *StackPop(stackT *stackP)
{
  if (StackIsEmpty(stackP)) {
    fprintf(stderr, "Can't pop element from stack: stack is empty.\n");
    exit(1);  /* Exit, returning error code. */
  }

  return stackP->contents[stackP->top--];
}

/*  This function check if the stack is empty or not  */
int StackIsEmpty(stackT *stackP)
{
  return stackP->top < 0;
}

/*  This function check if the stack is Full or not  */
int StackIsFull(stackT *stackP)
{
  return stackP->top >= stackP->maxSize - 1;
}

// void display(stackT *stackP) {

//     printf("Display: \n");

//     while (!StackIsEmpty(stackP)) {
//         printf("%s ", StackPop(stackP));
//     }

// }


/*  Increment the next available register number depending on the value of the parameter regType    */
/*  registerCounter, labelCounter & IOCounter are global variables                                  */
void increaseLabelCounter( int regType ) {
    
    /**
        1 - registerCounter
        2 - labelCounter
        3 - IOCounter
    */

    if ( regType == 1 )
        registerCounter += 1;
    else if ( regType == 2 )
        labelCounter += 1;
    else 
        IOCounter += 1;

}

/*  get the next available register/Label depeding on the type of the registers     */
/*  This function uses increaseLabelCounter() to get the register NUMBER            */
char * getLabelRegister(char *reg) {

    /**
        1 - registerCounter
        2 - labelCounter
        3 - IOCounter
    */

    char *labelName, *labelNumber;
    int regType;

    labelName = (char *)malloc(sizeof(char) * MAXSIZE);
    labelNumber = (char *)malloc(sizeof(char) * MAXSIZE);

    strcpy(labelName, reg);

    if ( strcmp(reg, "r") == 0 ) {
        regType = 1;
        sprintf(labelNumber, "%d", registerCounter);
        strcat(labelName, labelNumber);
    }
    else if ( strcmp(reg, "L") == 0 ) {
        regType = 2;
        sprintf(labelNumber, "%d", labelCounter);
        strcat(labelName, labelNumber);
    }
    else {
        regType = 3;
        sprintf(labelNumber, "%d", IOCounter);
        strcat(labelName, labelNumber);
    }

    // Increase the register number counter
    increaseLabelCounter(regType);

    // Freeing the variable that holds the labelNumber
    free(labelNumber);

    return labelName;
}

/*  Check if a string is alnumeric or not by iterating to the full char array   */
int stringIsalnum ( char *s ) {

    int i = 0;
    while ( isalnum(s[i]) ){
        i++;
        return 1;
    }

    return 0;

}

/*  generates the code for a single expression by checking to the global *temp[] and then   */
/*  using the algorithm provided by Dr. Coffey using stack push and Pop                     */
char *exprCodeGen () {

    char firstReg[MAXSIZE], secondReg[MAXSIZE],  againStack[MAXSIZE];    /* String entered by user. */
    char *firstOprChar, *secOprChar, *tempReg;  /* Pointer used to traverse the string. */
    int flagA = 0, flagB = 0;

    tempReg = (char *)malloc(sizeof(char) * MAXSIZE);
    codeString = (char *)malloc(sizeof(char) * MAXSIZE);

    // Using flag if in the temp we're never going to the else part
    // For example dealing with the statements like this || a = 10; ||
    int i = 0, flag = 0;
    while ( strcmp(temp[i], "\0") != 0) {
        
        // string is either ID or NUMBER - so push to array
        if ( stringIsalnum(temp[i] ) ) {

            StackPush(&stack, temp[i]);

        } else {

            flag = 1;

            // poping the first element from the stack
            firstOprChar = StackPop(&stack);

            // poping the second element from the stack
            secOprChar = StackPop(&stack);

            // checking if the element is a register or not
            if ( firstOprChar[0] == '~' ) {
                flagA = 1;
                strcpy(firstReg, strtok(firstOprChar, "~"));
            }
            else 
                strcpy(firstReg, getLabelRegister("r"));

            if ( secOprChar[0] == '~' ) {
                flagB = 1;
                strcpy(secondReg, strtok(secOprChar, "~"));
            }
            else
                strcpy(secondReg, getLabelRegister("r"));

            // If both of the operands are the registers in the stack
            if ( flagA && flagB ) {
            
                // printf("%s := %s %s %s\n", secondReg, secondReg, temp[i], firstReg);

                // pushing the full code to the global string codeString
                strcat(codeString, "   ");
                strcat(codeString, secondReg);
                strcat(codeString, " := ");
                strcat(codeString, secondReg);
                strcat(codeString, " ");
                strcat(codeString, temp[i]);
                strcat(codeString, " ");
                strcat(codeString, firstReg);
            
            } else if ( !flagA && !flagB ) {

                // printf("%s := %s\n", firstReg, secOprChar);

                // pushing the full code to the global string codeString
                strcat(codeString, "   ");
                strcat(codeString, firstReg);
                strcat(codeString, " := ");
                strcat(codeString, secOprChar);

                // printf("%s := %s\n", secondReg, firstOprChar);

                // pushing the full code to the global string codeString
                strcat(codeString, "\n");
                strcat(codeString, "   ");
                strcat(codeString, secondReg);
                strcat(codeString, " := ");
                strcat(codeString, firstOprChar);

                // printf("%s := %s %s %s\n", firstReg, firstReg, temp[i], secondReg);

                // pushing the full code to the global string codeString
                strcat(codeString, "\n");
                strcat(codeString, "   ");
                strcat(codeString, firstReg);
                strcat(codeString, " := ");
                strcat(codeString, firstReg);
                strcat(codeString, " ");
                strcat(codeString, temp[i]);
                strcat(codeString, " ");
                strcat(codeString, secondReg);

                if ( strcmp(temp[i+1], "\0") != 0 )
                    strcat(codeString, "\n");

                snprintf(againStack, sizeof(againStack), "%s%s", "~", firstReg);

                StackPush(&stack, againStack);

            } else {

                // first operator in array: register - No ID or NUMBER
                if ( !flagA ) {
                    // printf("%s := %s\n", firstReg, firstOprChar);

                    // pushing the full code to the global string codeString
                    strcat(codeString, "   ");
                    strcat(codeString, firstReg);
                    strcat(codeString, " := ");
                    strcat(codeString, firstOprChar);
                } 

                // second operator in array: register - No ID or NUMBER
                if ( !flagB ) {
                    // printf("%s := %s\n", secondReg, secOprChar);

                    // pushing the full code to the global string codeString
                    strcat(codeString, "   ");
                    strcat(codeString, secondReg);
                    strcat(codeString, " := ");
                    strcat(codeString, secOprChar);
                } 

                // printf("%s := %s %s %s\n", firstReg, firstReg, temp[i], secondReg);

                // pushing the full code to the global string codeString
                strcat(codeString, "\n");
                strcat(codeString, "   ");
                strcat(codeString, firstReg);
                strcat(codeString, " := ");
                strcat(codeString, secondReg);
                strcat(codeString, " ");
                strcat(codeString, temp[i]);
                strcat(codeString, " ");
                strcat(codeString, firstReg);
                strcat(codeString, "\n");

            }

        }

        i++;

    }

    // restarting the register counter
    registerCounter = 1;

    // if expr is something like this ||| a = 10 |||
    if ( flag == 0 ) {
        tempReg = getLabelRegister("r");

        // pushing the full code to the global string codeString
        strcat(codeString, "   ");
        strcat(codeString, tempReg);
        strcat(codeString, " := ");
        strcat(codeString, temp[i-1]);

        return tempReg;
    }

    // get rid of the previous expression, we don't need those - aready generated code and stored that in the codeString
    emptyTemp();

    // returning the first register
    strcpy(tempReg, firstReg);

    return tempReg;

}

/*  Insert the current lexeme to the global *temp[] and increase the element counter for that array     */
/*  This function only used in emitter.c                                                                */
void insertIntoTemp( char *aString ) {
    strcpy(temp[tempElementCounter], aString);
    tempElementCounter++;
}

/*  Insert the current lexeme to the global *temp[] only when the lexeme is a character not a string     */
/*  This function only used in emitter.c                                                                 */
void insertIntoTempAsChar( char aChar ) {
    char charArray[10];
    charArray[0] = aChar;
    charArray[1] = '\0';
    strcpy(temp[tempElementCounter], charArray);
    tempElementCounter++;
}

/*  get rid of the previous expression lexemes that are stored in the global *temp[]    */
/* by putting "\0" to the elements                                                      */
void emptyTemp () {

    int i;
    for ( i = 0; i < MAXSIZE; i++ )
    {
        strcpy(temp[i], "\0");
    }
    tempElementCounter = 0;
}



