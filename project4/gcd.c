#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    // check for file name in the second argument of the command line
    if ( argc < 3 ) {
        printf("Usage: ./gcd <number1> <number2>\n");
        exit(-1);
    }

    // getting the two numbers from commandline argument
    int i = atoi(argv[1]);
    int j = atoi(argv[2]);

    while ( i != j ) {

        if ( i > j )
            i = i -j;
        else
            j = j - i;

    }

    printf("%d\n", i);

    return 1;

}