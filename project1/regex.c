#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	regex_t regex;
	int reti;
	char msgbuf[100];

/* Compile regular expression */
	reti = regcomp(&regex, "\b([[:alpha:]][[:alnum:]]*_?)*[^[:space:]_]\b", REG_EXTENDED);
	if( reti ){ 
		fprintf(stderr, "Could not compile regex\n"); exit(1); 
		}

/* Execute regular expression */
	reti = regexec(&regex, "qwe123123r_asd", 0, NULL, 0);
	if( !reti ){
		puts("Match");
	}
	else if( reti == REG_NOMATCH ){
		puts("No match");
	}
	else{
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		exit(1);
	}

/* Free compiled regular expression if you want to use the regex_t again */
	regfree(&regex);

	return 0;
}