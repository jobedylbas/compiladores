#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isRunning(void);
int getLineNumber(void);

const char* getTokenName(int tokenASCII) {
    switch(tokenASCII) {
        case KW_CHAR:       return "KW_CHAR ";      break;
        case KW_INT:        return "KW_INT  ";      break;
        case KW_BOOL:       return "KW_BOOL ";      break;
        case KW_POINTER:    return "KW_POINTER";    break;
        case KW_IF:         return "KW_IF    ";      break;
        case KW_THEN:       return "KW_THEN ";      break;
        case KW_ELSE:       return "KW_ELSE ";      break;
        case KW_WHILE:      return "KW_WHILE";      break;
        case KW_READ:       return "KW_READ ";      break;
        case KW_PRINT:      return "KW_PRINT";      break;
        case KW_RETURN:     return "KW_RETURN";     break;

        case OPERATOR_LE:   return "OPERATOR_LE";   break;
        case OPERATOR_GE:   return "OPERATOR_GE";   break;
        case OPERATOR_EQ:   return "OPERATOR_EQ";   break;
        case OPERATOR_DIF:  return "OPERATOR DIF";  break;
        case LEFT_ASSIGN:   return "LEFT_ASSIGN";   break;
        case RIGHT_ASSIGN:  return "RIGHT_ASSIGN";  break;
        case TK_IDENTIFIER: return "TK_IDENTIFIER"; break;

        case LIT_INTEGER:   return "LIT_INTEGER";   break;
        case LIT_TRUE:      return "LIT_TRUE";      break;
        case LIT_FALSE:     return "LIT_FALSE";     break;
        case LIT_CHAR:      return "LIT_CHAR";      break;
        case LIT_STRING:    return "LIT_STRING";    break;

        case TOKEN_ERROR:   return "TOKEN_ERROR";   break;
        default:            return "Special char";  break;
    }
}

int tokenInHash(int token) {
    if ((token == TK_IDENTIFIER) || (token == LIT_INTEGER) || (token == LIT_CHAR) || (token == LIT_STRING)) {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    int token, inserted;
    char *tokenName;
    // Error if no file is passed when executing the program
    if (argc < 2) {
        fprintf(stderr, "Call: ./etapa1 file_name\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");

    // Error if file doesn't exist
    if (yyin == NULL) {
        fprintf(stderr, "Failed to openfile: %s.\n", argv[1]);
        exit(2);
    }

    yyparse();  
    printf("Passed!\n");
    exit(0);
}