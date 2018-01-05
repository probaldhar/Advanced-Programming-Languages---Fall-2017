#include "global.h"

char lexbuf[BSIZE];

int lineno = 1;
int tokenval =  NONE;

int lexan()
{
  int t;
  while(1)  {
    t = getchar();
    if (t == ' ' || t == '\t')
      ;
    else if (t == '\n')
      lineno++;
    else if (isdigit(t)) {
      ungetc(t, stdin);
      scanf("%d", &tokenval);
      return NUM;
    }
    else if (t=='~'){
	while(t!='~')
		t = getchar();
    }
    else if (isalpha(t)) {
      int p, b = 0;
      while (isalnum(t)) {
        lexbuf[b] = t;
        t = getchar();
        b++;
        if(b >= BSIZE)
          error("compiler error");
      }  
      lexbuf[b] = EOS;
      if(t != EOF)
        ungetc(t, stdin);
      p = lookup(lexbuf);
      if(p==NOT_FOUND)
        p = insert(lexbuf, ID);
      tokenval = p;

	//printf("tokenval = %d\n", tokenval);

      return getTokenType(p);
    }

    else if (t == EOF)
      return DONE;

    else {
      tokenval = NONE;
      return t;
    }

  }
}
