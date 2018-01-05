/* Parser that component that breaks data into smaller elements for easy translation    */
/* it takes lexeme from lexer.c and check if it's a valid token or not                  */
#include "global.h"

// lookahead stores the next lexeme from the lexer()
int lookahead;

/* parse() function takes the lookahead and check what function I should call   */
/* depending on the lookahead it calles for the matches specific keywords       */
/* parse() normally calls expr() to check the statements & expression           */
parse()
{

    // get the lexeme from the lexan() which is defined in lexer.c
    lookahead = lexan();

    // match "begin" at first
    match(BEGIN);

    // check the lookahead until we get "end"
    while ( lookahead != END ) { 

        // if the lookahead is integer declearation
        if ( lookahead == INTTOKEN ) {
            expr();
            match(';');
        } else if ( lookahead == IF ) {
            match(IF);
            match('(');
            expr();
            match(')');
            match(';');
            while ( lookahead != ENDIF ) {
                expr();
                match(';');
            }
            match(ENDIF);
            match(';');

        } else if ( lookahead == WHILE ) {

            match(WHILE);
            match('(');
            expr();
            match(')');
            match(';');

            while ( lookahead != ENDWHILE ) {
                expr();
                match(';');
            }
            match(ENDWHILE);
            match(';');

        } else {
            expr();
            match(';');
        }
 
    }
  
  match(END);

}

/* expr() function checks the statement and search if it's contain any operator */
/* before checking for operator expr() is calling term()                        */
/* the grammar for it should be <expr> ::= <term>{[+|-]<term>}*                 */
/* so a expr may have one or more term                                          */
expr()
{

    int t;
    term();

    while(1) {
        switch(lookahead) {

            case '+': case '-': case '=': case '>': case '<':
                t = lookahead;

            match(lookahead);

            term(); 
            //emit(t, NONE);
            continue;

            case COMPAR:
                term(); 
                //emit(COMPAR,NONE);
                continue;

            default:
                return;
        }
    } 
}

/* term() function checks for any factor in the statement and calls factor()    */
/* the grammar for the term would be <term> ::= <factor>{[*|/]<factor>}*        */
/* so it checks for one or more factors in the statement                        */
term()
{

    int t;
    factor();

    while(1) {
        switch(lookahead) {

          case '*': case '/': case DIV: case MOD:
            t = lookahead;

            match(lookahead);

            factor(); 
            //emit(t, NONE);
            continue;
          default:
            return;
        }
    }

}

/* factor() function checks for any variable, number, any comparison operator, interger decelaration etc in a factor    */
/* the grammar for any factor would be <factor> ::= <variable> | <number> |  (<expr>)                                   */
/* so it's either a variable, number, ID, COMPAR etc.                                                                   */
factor()
{

    switch(lookahead) {
        case '(':	

            match('(');

            expr(); 

            match(')');

            break;
        case NUM:
            //emit(NUM, tokenval); 

            match(NUM);

            break;
        case ID:
            //emit(ID, tokenval); 

            match(ID);

            break;
        case GEQ:
            //emit(GEQ, tokenval); 

            match(GEQ);

            term(); 
            break;

        case COMPAR:

            //emit(COMPAR, NONE);

            match(COMPAR);

            term(); 

            break; 

        case EQ: 
            //emit(EQ, NONE);

            match(EQ);

            term(); 
            break;

        case INTTOKEN:
            //emit(INTTOKEN, NONE);

            match(INTTOKEN);

            factor();

            break;

        case IF: 
            match(IF);
            expr();
            break;

        case WHILE:
            match(WHILE);
            expr();
            break;

      default:
        error("syntax error factor");
    }

}

/* match() function match the lexeme with the expected lookahead        */
/* when it matches it calls lexan() and store the lexeme in lookahead   */
/* otherwise it calls for error() which exits the program               */
int match(int t)
{
  	if ( lookahead == t ) {
    	lookahead = lexan();
  	}
  	else {
	    error("syntax error match");
  	}
}
