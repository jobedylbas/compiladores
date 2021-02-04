#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isRunning(void);
int getLineNumber(void);

int main(int argc, char **argv) {
    int token;

    // Error if no file is passed when executing the program
    if (argc < 2) {
        fprintf(stderr, "Call: ./a.out file_name\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");

    while(isRunning()) {
        token = yylex();
        
        if (!isRunning()) break;
        
        exit(0);
    }
}