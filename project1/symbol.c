
#include "global.h"

#define STRMAX 999
#define SYMMAX 999

struct entry {
	char *lexptr;
	int token;
};


struct entry symtable[SYMMAX];

char lexemes[STRMAX];

int lastchar = -1;
int lastentry = 0;

struct entry keywords[] = {
   "begin", BEGIN,
   "end", END,
   "if", IF,
   "while", WHILE,
   "div", DIV,
   "mod", MOD,
   0 , 0
};

init()
{
  struct entry *p;
  for(p = keywords; p->token; p++){
    insert(p->lexptr, p->token);
	//printf("%s %d\n", p->lexptr, p->token);
  }
}


int lookup(char s[])
{
   int p;
   for(p = lastentry; p > 0; p--)
    if(! strcmp(symtable[p].lexptr, s) )
       return p;
       
   return NOT_FOUND;
}

int insert(char s[], int tok)
{
  int len,i;
  len = strlen(s);
  if(lastentry + 1 >= SYMMAX)
     error("symbol table full");
  if (lastchar + len + 1 >= STRMAX)
     error("lexeme array full");  
  lastentry = lastentry + 1;
  symtable[lastentry].token = tok;
  symtable[lastentry].lexptr = &lexemes[lastchar + 1];
  lastchar = lastchar + len + 1;
  strcpy(symtable[lastentry].lexptr, s);

	//for ( i = 0; i < lastentry; i++ )
		//printf("%s %d\n", symtable[i].lexptr, symtable[i].token);

  return lastentry;
}

char * getLexeme(int pos)
{
  return symtable[pos].lexptr;
}

int getTokenType(int pos)
{
  return symtable[pos].token;
}
