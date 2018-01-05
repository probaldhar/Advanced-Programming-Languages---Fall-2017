
#include "global.h"

int lookahead;

parse()
{
  lookahead = lexan();
  match(BEGIN);

  while(lookahead != END){ 
   	//match(ID); match('='); 
  	
	if ( match(IF)) { 
		//printf("if");
    		expr();
  		match(';');
 	} 
	else if (match(WHILE)){
		//printf("while1");
    		expr(); 
   		match(';');
  	}
	else {
		//printf("else\n");
		//match(ID); // printf("1\n"); 
		//if (!match('=') ) 
		//	error("syntax error");
	 	expr(); // printf("3\n");
		match(';');
	}
	
	// printf("outside of if else");
 
  }
  match(END);
}

expr()
{

	//printf("expr\n");

  int t;
  term();
  while(1) {
    switch(lookahead) {

	//printf("look: %d\n", lookahead);
	
      case '+': case '-': case '=':
        t = lookahead;
        match(lookahead); term(); emit(t, NONE);
        continue;
      default:
        return;
    }
  } 
}

term()
{

	//printf("term\n");	

  int t;
  factor();
  while(1) {
    switch(lookahead) {

	//printf("look in term: %d", lookahead);

      case '*': case '/': case DIV: case MOD:
        t = lookahead;
        match(lookahead); factor(); emit(t, NONE);
        continue;
      default:
        return;
    }
  }

}


factor()
{

	//printf("factor\n");

    switch(lookahead) {
      case '(':	//printf("parenStart");
        match('('); expr(); match(')'); break;
      case NUM:
        emit(NUM, tokenval); match(NUM); break;
      case ID:
        emit(ID, tokenval); match(ID); break;

      default:
        error("syntax error factor");
    }
  
}

int match(int t)
{

	//printf("match\n");
	//printf("t = %d\n", t);

  	if(lookahead == t) {
    		lookahead = lexan();
		//printf("lookahead = %d\n", lookahead);
	 	return 1;
  	}
  	else {
	    	//error("syntax error match");
		//printf("error %d\n", t);
		return 0;
  	}
}
