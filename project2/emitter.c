/* This file emits the opeartors and prints them in the screen              */

#include <string.h>
#include "global.h"

/* emit() function receives t and tval which is token and tokenval          */ 
/* depending on the token and tokenval something would print in the screen  */
emit(int t, int tval)
{
    switch(t) {
        case '+': case '-': case '*': case '=': case '/': case '<': case '>':
            // printf("%c\n",t);
            insertIntoTempAsChar(t);
            break;
        case LE:
            // printf("<=\n",t); 
            insertIntoTemp("<=");
            break;
        case GE:
            // printf(">=\n",t);
            insertIntoTemp(">=");
            break;
        case PE:
            // printf("+=\n",t); 
            insertIntoTemp("+=");
            break;
        case ME:
            // printf("-=\n",t); 
            insertIntoTemp("-=");
            break;
        case EE:
            // printf("==\n",t); 
            insertIntoTemp("==");
            break;
        case NE:
            // printf("!=\n",t); 
            insertIntoTemp("!=");
            break;
        case DIV:
            printf("DIV\n"); break;
        case MOD:
            printf("MOD\n"); break;
        case NUM:
            sprintf(tempStr, "%d", tval);
            insertIntoTemp(tempStr);
            break;
        case ID:
            // printf("ID %s\n", getLexeme());
            insertIntoTemp(getLexeme());
            break;
        case IF:
            printf("IF\n"); break;
        case WHILE:
            printf("WHILE\n"); break;
        case COMPAR:
            printf("COMPAR\n"); break;
        case EQ: 
            printf("EQ\n", t); break;
        case CONS: 
            printf("CONS\n", t); break;
        case INTTOKEN: 
            printf("INT\n", t); break;
        default:
          error("token %d, tokenval %d\n", t, tval);
    }
}
