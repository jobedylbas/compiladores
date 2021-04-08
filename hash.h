#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>

#define HASH_SIZE 1021

typedef struct hash_node {
    int type;
    int datatype;
    char *text;
    struct hash_node *next;
} HASH_NODE;

void hashInit(void);
int hashAddres(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
int hash_check_undeclared();

#endif
