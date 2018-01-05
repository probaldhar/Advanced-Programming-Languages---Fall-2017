#include "global.h"

emit(int t, int tval)
{
      switch(t) {
        case '+': case '-': case '*': case '/':
          printf("%c\n",t); break;
      case DIV:
          printf("DIV\n"); break;
      case MOD:
          printf("MOD\n"); break;
      case NUM:
          printf("%d\n", tval); break;
      case ID:
          printf("%s\n",symtable[tval].lexptr); break;
      default:
        error("token %d, tokenval %d\n", t, tval);
    }
}