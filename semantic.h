#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "y.tab.h"

extern int semanticErrors;

void check_and_set_declarations(AST_NODE *node);
void check_undeclared();
int get_semantic_errors();
void check_operands(AST_NODE *node);
int convert_to_datatype(AST_NODE * node);
#endif