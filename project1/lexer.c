/* This file checks for each character in the input and categorize them and return values on the basis on them  */
/* it also have function to open a file                                                                         */

#include "global.h"
#include <stdlib.h>

char lexbuf[BSIZE];
char consBuf[BSIZE];

int lineno = 1;
int tokenval =  NONE;
int tempTok;

FILE * fp;

/* openFile() function opens the file to be read for parsing    */
/* this function don't receive any parameter and return nothing */
void openFile(char *fileName) {

    fp = fopen (fileName, "r");

    if (fp != NULL){
        // printf("OPEN\n");
    }
    else {
        printf("FILE NOT OPEN\n");
        exit(-1);
    }

}

/* closes the opened file */
void closeFile() {
    fclose(fp);
}

/* lexan() function checks each character in the input from the file        */
/* it defines if the lexeme is NUM, blank space or any valid token type     */
/* this function also lookup & insert any valid token in the symbol table   */
int lexan()
{
    int t;
    while (1)  {
        // t = getchar();
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
                return COMPAR;
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
            p = insert (lexbuf, ID);

            tokenval = p;
            p = lookup(lexbuf);

          } else {
            tokenval = p;
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
