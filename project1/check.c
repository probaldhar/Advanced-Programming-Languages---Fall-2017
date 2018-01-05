#include <stdio.h>

#define BSIZE 128
#define NONE -1
#define EOS '\0'
#define NUM 256
#define DIV 257
#define MOD 258
#define ID 259
#define IF 900
#define WHILE 600
#define DONE 260
#define BEGIN 400
#define END 401
#define NOT_FOUND 0

int main(int argc, char *argv[]) {
	typedef struct{
		char lexemeT[999];
		int tokenType;
		struct entry *next;
	}entry;
	
	
	entry keywords[] = {
		"begin", BEGIN, NULL,
		"end", END, NULL,
		"if", IF, NULL,
		"while", WHILE, NULL,
		"div", DIV, NULL,
		"mod", MOD, NULL,
		0 , 0, NULL
	};
	
	entry *p;
		for(p = keywords; p->tokenType; p++){
//			insert(p->lexptr, p->token);
		printf("%s %d\n", p->lexemeT, p->tokenType);
		}
}