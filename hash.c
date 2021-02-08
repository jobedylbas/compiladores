#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

HASH_NODE *Table[HASH_SIZE];

void HashInit(void) {
    for(int i=0; i<HASH_SIZE; i++) Table[i]=NULL;
}

int hashAddress(char *text) {
    int address = 1;
    for(int i=0; i<strlen(text); i++) {
        address = (address * text[i]) % HASH_SIZE + 1;
    }
    return address - 1;
}

HASH_NODE *hashFind(char *text) {
    HASH_NODE *node;
    int address = hashAddress(text);
    for(node=Table[address]; node; node = node->next) {
        if (!strcmp(node->text, text)) return node;
    }
    return NULL;
}

HASH_NODE *hashInsert(char *text, int type) {
    HASH_NODE *new_node;
    if ((new_node = hashFind(text))!=0) return new_node;

    int address = hashAddress(text);

    new_node = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
    new_node-> type = type;
	new_node-> text = (char*) calloc(strlen(text)+1, sizeof(char));
	strcpy(new_node->text, text);
	new_node-> next = Table[address];
	Table[address] = new_node;
    
    return new_node;
}

void hashPrint(void)
{
	HASH_NODE *node;
	for(int i=0; i<HASH_SIZE; i++)
		for(node=Table[i]; node; node = node->next)
			printf("[Table %d] has %s\n", i, Table[i]->text);
}