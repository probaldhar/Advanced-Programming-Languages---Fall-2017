/* This file emits the opeartors and prints them in the screen              */

#include "global.h"

/* emit() function receives t and tval which is token and tokenval          */ 
/* depending on the token and tokenval something would print in the screen  */
emit(int t, int tval)
{
    switch(t) {
      case '+': case '-': case '*': case '/': case '=': case '<': case '>':
        printf("%c\n",t); break;
    case DIV:
        printf("DIV\n"); break;
    case MOD:
        printf("MOD\n"); break;
    case NUM:
        printf("%d\n", tval); break;
    case ID:
        printf("%s\n",getLexeme()); break;
    case IF:
        printf("IF\n"); break;
    case WHILE:
        printf("WHILE\n"); break;
    case GEQ:
        printf("GEQ\n"); break;
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
