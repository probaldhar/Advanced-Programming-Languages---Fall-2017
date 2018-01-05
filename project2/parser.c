/* Parser that component that breaks data into smaller elements for easy translation    */
/* it takes lexeme from lexer.c and check if it's a valid token or not                  */
#include "global.h"

// lookahead stores the next lexeme from the lexer()
int lookahead;


int labelCounter = 1;

int intTokenFlag;

char * tempReg, *storeIfPart, *storeTempReg, *storeIDName;

char * storeLabelIf, *storeSecondLabelIf, *storeThirdLabelIf;

/* parse() function takes the lookahead and check what function I should call   */
/* depending on the lookahead it calles for the matches specific keywords       */
/* parse() normally calls expr() to check the statements & expression           */
parse()
{

    // get the lexeme from the lexan() which is defined in lexer.c
    lookahead = lexan();

    // match "begin" at first
    match(BEGIN);
    fprintf(fpWrite, "main:\n");

    // check the lookahead until we get "end"
    while ( lookahead != END ) { 

        statement();
 
    }
  
  match(END);
  fprintf(fpWrite, "goto exit\n");

}

/* statement() function check the next lexeme and match that with the current lookahead         */
/* it tries to match the lookahead with interger declaration, selector, iterator or expression  */
statement() {

    // if the lookahead is integer declearation
    if ( lookahead == INTTOKEN ) {
       // expr();
        match(INTTOKEN);
	    checkReDec();
        intTokenFlag = 1;
	    match(ID);
        fprintf(fpWrite, "   .word %s\n", getLexeme());
        match(';');
    } else if ( lookahead == IF ) {
        
        selector();

    } else if ( lookahead == WHILE ) {

        iterator();

    } else if ( lookahead == READ ){

        match(READ);
        match('(');
        match(ID);
        fprintf(fpWrite, "   %s := &input\n", getLabelRegister("a"));
        fprintf(fpWrite, "   call readint\n");
        fprintf(fpWrite, "   %s := rv\n", getLexeme());
        match(')');
        match(';');

    } else if ( lookahead == WRITE ){

        match(WRITE);
        match('(');
        match(ID);
        fprintf(fpWrite, "   %s := &output\n", getLabelRegister("a"));
        fprintf(fpWrite, "   call writeint\n");
        fprintf(fpWrite, "   %s := rv\n", getLexeme());
        match(')');
        match(';');
        
    } else if ( lookahead == ID ) {

        storeIDName = (char *)malloc(sizeof(char) * MAXSIZE);

        strcpy(storeIDName, getLexeme());

        match(ID);
        match('=');
        expr();
        // tempReg = (char *)malloc(sizeof(char) * MAXSIZE);
        tempReg = exprCodeGen();

        fprintf(fpWrite, "%s\n", codeString);

        fprintf(fpWrite, "   %s := %s\n", storeIDName, tempReg);

    } else {
        expr();
        // match(';');
    }

}

/* this function expect any IF..ENDIF selector statement. It matches with the grammar   */
/* and stops the program to be execute if it's don't match with the grammar             */
selector() {

    int ifElsePart = 0;

    localCodeString = (char *)malloc(sizeof(char) * MAXSIZE);
    storeIfPart = (char *)malloc(sizeof(char) * MAXSIZE);

    char *storeLabelIf = getLabelRegister("L");
    char *storeSecondLabelIf = getLabelRegister("L");

    match(IF);
    match('(');
    expr();
    match(')');

    tempReg = exprCodeGen();

    fprintf(fpWrite, "%s\n", codeString);

    fprintf(fpWrite, "   if !%s goto %s\n", tempReg, storeLabelIf);

    while ( lookahead != ENDIF ) {

        if ( lookahead != ELSE ) {
            // Need to check the order of the code
            statement();
        } else {

            // Flag if there's a "else" part in the if else ladder
            ifElsePart = 1;

            fprintf(fpWrite, "   goto %s\n", storeSecondLabelIf);
            fprintf(fpWrite, "%s: \n", storeLabelIf);

            match(ELSE);
            statement();
        }

    }

    if ( ifElsePart ) {
        fprintf(fpWrite, "%s: \n", storeSecondLabelIf);
    } else
        fprintf(fpWrite, "%s: \n", storeLabelIf);

    match(ENDIF);

    fprintf(fpWrite, "\n");
}

/* this function executes when the lexeme is for iterator, for this program it only WHILE...ENDWHILE    */
/* it matches with the grammar and stops if the program has any invalid grammar or lexeme               */
iterator() {

    localCodeStringWhile = (char *)malloc(sizeof(char) * MAXSIZE);
    storeTempReg = (char *)malloc(sizeof(char) * MAXSIZE);

    match(WHILE);

    char *storeLabel = getLabelRegister("L");
    char *storeSecondLabel = getLabelRegister("L");
    // char *storeThirdLabel = getLabelRegister("L");

    fprintf(fpWrite, "   goto %s:\n", storeLabel);
    fprintf(fpWrite, "%s:\n", storeSecondLabel);

    match('(');
    // conditional statement
    expr(); // expr in attribute grammar
    match(')');

    // storing the operator
    tempReg = exprCodeGen();

    strcpy(storeTempReg, tempReg);

    strcpy(localCodeStringWhile, codeString);

    while ( lookahead != ENDWHILE ) {
        statement();    // stmt 2 in attribute grammar
        // printing stmt2.code
    }
    match(ENDWHILE);

    fprintf(fpWrite, "%s:\n", storeLabel);
    // printing expr code
    fprintf(fpWrite, "%s\n", localCodeStringWhile);
    fprintf(fpWrite, "   if %s goto %s\n", storeTempReg, storeSecondLabel);

    // fprintf(fpWrite, "%s: \n", storeThirdLabel);
    fprintf(fpWrite, "\n");

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

            case '+': case '-': case '>': case '<':
                t = lookahead;

            match(lookahead);

            term(); 
            emit(t, NONE);
            continue;

            case COMPAR:
                term(); 
                emit(COMPAR,NONE);
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

          case '*': case '/': case '=': case DIV: case MOD: case GE: case LE: case EE: case PE: case ME: case NE:
            t = lookahead;

            match(lookahead);

            factor(); 
            emit(t, NONE);
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
            emit(NUM, tokenval); 
            match(NUM);
            break;

        case ID:
            emit(ID, tokenval); 
            match(ID);
            break;

        case COMPAR:
            emit(COMPAR, NONE);
            match(COMPAR);
            term(); 
            break; 

        case '=':
            match('=');
            emit('=', NONE);
            expr();
            break;

        case ';':
            match(';');
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
	int lookupSymTable;

	if ( t == ID ) {

		// Check for delearation
        if ( tokenval == NOT_FOUND ) {

            if ( intTokenFlag != 1 )
                error("use of variable before declared.");
            else 
                insert (lexbuf, ID);
        } else {
            
        }

        intTokenFlag = 0;

		lookahead = lexan();	

	} else if ( lookahead == t ) {
    		lookahead = lexan();
  	}
  	else {
	    error("syntax error match");
  	}
}

/* Check the ID for redelearation with the flag getting from lexer */ 
int checkReDec() {

	if (lookupFlag)
		error("redeleared");
	
	return 1;

}





