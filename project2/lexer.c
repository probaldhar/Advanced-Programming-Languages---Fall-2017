/* This file checks for each character in the input and categorize them and return values on the basis on them  */
/* it also have function to open a file                                                                         */

#include "global.h"
#include <stdlib.h>

char lexbuf[BSIZE];
char consBuf[BSIZE];

int lineno = 1;
int tokenval =  NONE;
int tempTok;

int lookupFlag;

char *newFileName;

FILE * fp;

/* openFile() function opens the file to be read for parsing    */
/* this function don't receive any parameter and return nothing */
void openFile(char *fileName) {

    newFileName = (char *)malloc(sizeof(char) * MAXSIZE);

    fp = fopen (fileName, "r");

    if (fp != NULL){
        // printf("OPEN\n");

        // extracting the filename without extension
        strtok(fileName, ".");
        strcpy(newFileName, fileName);
        strcat(newFileName, ".dat");    // adding .dat to extension of the new file

        // printf("newFileName: %s\n", newFileName);

        fpWrite = fopen(newFileName, "w");

        if (fp != NULL) {
            // printf("open write file\n");
        } else {
            printf("WRITE FILE NOT OPEN\n");
            exit(-1);
        }

    }
    else {
        printf("FILE NOT OPEN\n");
        exit(-1);
    }

}

/* closes the opened file */
void closeFile() {
    fclose(fp);
    fclose(fpWrite);
}

/* lexan() function checks each character in the input from the file        */
/* it defines if the lexeme is NUM, blank space or any valid token type     */
/* this function also lookup & insert any valid token in the symbol table   */
int lexan()
{
    int t;
    while (1)  {
        // t = getchar();
        // printf("%c\n", t);
        t = fgetc(fp);
        if (t == ' ' || t == '\t')
          ;
        else if (t == '\n')
          lineno++;
        else if (isdigit(t)) {

          // ungetc(t, stdin);
          ungetc(t, fp);
          fscanf(fp, "%d", &tokenval);
          return NUM;
        }
        else if ( t == '>' || t == '<' || t == '=' || t == '+' || t == '-' || t == '!' ) {

            tempTok = t;
            // t = getchar();
            t = fgetc(fp);
            if ( t == '=' ) {

                // Return Different VALUE for each different comparison operator
                if ( tempTok == '>' )
                    return GE;
                else if ( tempTok == '<' )
                    return LE;
                else if ( tempTok == '=' )
                    return EE;
                else if ( tempTok == '+' )
                    return PE;
                else if ( tempTok == '-' )
                    return NE;
                else if ( tempTok == '!' )
                    return NE;

            } else {
                // ungetc(t, stdin);
                ungetc(t, fp);
                return tempTok;
            }
        }

        else if ( t == '~' ) {
           while ( t != '\n' )
               // t = getchar();
               t = fgetc(fp);

           lineno++;
           // printf("commented line\n");
        }
        else if ( isalpha(t) ) {
            int p, b = 0;
            while ( isalnum(t) || t == '_' ) {
                lexbuf[b] = t;

                if ( t == '_' ) {
                    // t = getchar();
                    t = fgetc(fp);
                    if ( t == '_')      // e__7 - invalid identifier
                        error("wrong identifier name");
                    else 
                        ungetc(t,fp);
                }

                // t = getchar();
                t = fgetc(fp);
                b++;
                if(b >= BSIZE)
                  error("compiler error");
            }

            // these are invalid identifier "abc_"
            if ( lexbuf[b-1] == '_' )
                error("wrong identifier name");

            lexbuf[b] = EOS;

            if ( t != EOF )
                // ungetc(t, stdin);
                ungetc(t, fp);
          
            p = lookup(lexbuf);

            if ( p == NOT_FOUND ) {

                // p = insert (lexbuf, ID);

                lookupFlag = 0;

                tokenval = p;
                // p = lookup(lexbuf);

                tokenval = NOT_FOUND;

            } else {
                tokenval = p;
                lookupFlag = 1;

                tokenval = FOUND;

            }

            return getTokenType();
        }

        else if (t == EOF)
            return DONE;

        else {
            tokenval = NONE;
            return t;
        }

    }
}
