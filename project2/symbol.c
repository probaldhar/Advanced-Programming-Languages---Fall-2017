/* This file deals with symbol table, it has a entry structure                      */
/* functions: lookup(), insert(), hashFunction(), getLexeme(), getTokenType() etc   */
/* these functions to use when we need to insert any lexeme in the symbol table     */
/* and also to lookup any tokens from the symbol table                              */
#include "global.h"

#define STRMAX 999
#define SYMMAX 999

/* This is the structure used to handle symbol table using externally chained hash table    */
/* lexemeT     - array contains the token itself                                            */
/* tokenType   - value of the token                                                         */
/* entry *next - pointer to the next record of the symbol table                             */
struct entry {
    char lexemeT[STRMAX];
    int tokenType;
    struct entry *next;
};

// SYMBOL table
struct entry *symtable[SYMMAX];

// pointer to the current entry of the symbol table, possibly in the external chain
struct entry *current;

int lastchar = -1;
int lastentry = 0;

// reserved keywords at the beginning
struct entry keywords[] = {
   "begin", BEGIN, NULL,
   "end", END, NULL,
   "if", IF, NULL,
   "else", ELSE, NULL,
   "endif", ENDIF, NULL,
   "while", WHILE, NULL,
   "endwhile", ENDWHILE, NULL,
   "div", DIV, NULL,
   "mod", MOD, NULL,
   "int", INTTOKEN, NULL,
   "read", READ, NULL,
   "write", WRITE, NULL,
   0 , 0
};

/* init() function assigns NULL to every record of the symbol table */
/* and insert the keywords in the symbol table                      */
init()
{
    int i;
    for ( i = 0; i < SYMMAX; i++ )
        symtable[i] = NULL;

    struct entry *p;
    for(p = keywords; p->tokenType; p++){
        insert(p->lexemeT, p->tokenType);
  }
}

/* lookup() function search any tokens in the symbol table              */
/* it accepts a string as lexeme and search through the symbol table    */
/* it returns FOUND or NOT_FOUND depending on the search of the lexeme  */
int lookup(char s[])
{

    int hashIndex = hashFunction(s);
    struct entry *currentEntry;
    currentEntry = symtable[hashIndex];
    if (!currentEntry) {
        return NOT_FOUND;
    }

    while (currentEntry != NULL) {
        if ( !strcmp(currentEntry->lexemeT, s) ) {
            
            // returning the position
            current = currentEntry;
            return FOUND;
        }
        currentEntry = currentEntry->next;
    }

    // Default
    return NOT_FOUND;
}

/* HASH FUNCTION - summing up all character's ascii value   */
/* it receives the lexeme as parameter                      */
/* it returns the hash value for the string                 */
int hashFunction ( char lexemeP[] ) {
    int i, stringAsciiSum = 0;

    for ( i = 0; i < strlen(lexemeP); i++ )
        stringAsciiSum += (int)lexemeP[i];

    return stringAsciiSum % SYMMAX;
}


/* Function to create a node for the entry sturcture to insert the node in the symbol table */
/* it receives token and tokenval as parameter                                              */
/* this function returns the full node of type *entry                                       */
struct entry * createEntry (char *name, int token ) {
    struct entry *newEntry;
    newEntry = (struct entry *) malloc(sizeof(struct entry));
    newEntry->tokenType = token;
    strcpy(newEntry->lexemeT, name);
    newEntry->next = NULL;
    return newEntry;
}


/* insert() function insert the lexeme in the symbol table using the hash value for that string */
/* it receives token and tokenType as parameter                                                 */
/* it returns the hashIndex for the string                                                      */
int insert ( char s[], int tok )
{
    int len,i;
    len = strlen(s);
    
    if ( lastentry + 1 >= SYMMAX )
        error("symbol table full");

    if ( lastchar + len + 1 >= STRMAX )
        error("lexeme array full");  

    lastentry = lastentry + 1;

    lastchar = lastchar + len + 1;

    int hashIndex = hashFunction(s);
    struct entry *newEntry = createEntry(s, tok);

    symtable[hashIndex] = newEntry;

    // IF it's not NULL - newEntry's next will be the has chained link list
    newEntry->next = symtable[hashIndex]->next;

    // Symtable's next will be the newEntry
    symtable[hashIndex]->next = newEntry;

    current = newEntry;
    return hashIndex;

}

/* This function returns the current entry lexeme that points           */
/* to the recent inserted or lookedup lexeme in the symbol table        */
/* this pointer is set up in the insert() and in lookup()               */
char * getLexeme()
{
    return current->lexemeT;
}

/* tokenType() function returns the tokenType of the recent token that has been */
/* inserted or lookedup in the symbol table                                     */
/* current pointer is being set in the insert() and lookup() functions          */
int getTokenType()
{
    return current->tokenType;
}






