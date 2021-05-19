#include "semantic.h"

int semanticErrors = 0;

void check_and_set_declarations(AST_NODE *node) {
    int i;

    if(!node) return;

    switch (node->type)
    {
    case T_AST_DECGLOBALVAL:
        if (node->symbol->type != TK_IDENTIFIER) {
            fprintf(stderr, "Semantic ERROR: variable %s already declared.\n", node->symbol->text);
            ++semanticErrors;
        }
        node->symbol->type = SYMBOL_VAR;
        node->symbol->datatype = convert_to_datatype(node);
        break;
    case T_AST_FUNC:
        if (node->symbol->type != TK_IDENTIFIER) {
            fprintf(stderr, "Semantic ERROR: function %s already declared.\n", node->symbol->text);
            ++semanticErrors;
        }
        node->symbol->type = SYMBOL_FUNC;
        node->symbol->datatype = convert_to_datatype(node);
        break;
    case T_AST_DECVEC:
        if (node->symbol->type != TK_IDENTIFIER) {
            fprintf(stderr, "Semantic ERROR: vector %s already declared.\n", node->symbol->text);
            ++semanticErrors;
        }
        node->symbol->type = SYMBOL_VEC;
        node->symbol->datatype = convert_to_datatype(node);
        break;
    case T_AST_DECGLOBALVECWITHVALUE:
        if (node->symbol->type != TK_IDENTIFIER) {
            fprintf(stderr, "Semantic ERROR: vector %s already declared.\n", node->symbol->text);
            ++semanticErrors;
        }
        node->symbol->type = SYMBOL_VEC;
        node->symbol->datatype = convert_to_datatype(node);
        break;
    case T_AST_HEADPARAMLIST:
        if (node->symbol->type != TK_IDENTIFIER) {
            fprintf(stderr, "Semantic ERROR: vector %s already declared.\n", node->symbol->text);
            ++semanticErrors;
        }
        node->symbol->type = SYMBOL_PARAM;
        node->symbol->datatype = convert_to_datatype(node);
        break;
    default:
        break;
    }

    for(i=0; i< MAX_SONS; ++i) {
        check_and_set_declarations(node->son[i]);
    }
}

void check_undeclared() {
    semanticErrors += hash_check_undeclared();
}

int get_semantic_errors() {
    return semanticErrors;
}

void check_operands(AST_NODE *node) {
    int i;
    if(node == 0) return;

    switch (node->type)
    {
    case T_AST_ADD:
    case T_AST_SUB:
    case T_AST_MULT: 
    case T_AST_DIV:
        // Check all aritmetic operands
        for(int operand = 0; operand < 2; operand++) {
            if(node->son[operand]->type == T_AST_ADD ||
            node->son[operand]->type == T_AST_SUB ||
            node->son[operand]->type == T_AST_MULT ||
            node->son[operand]->type == T_AST_DIV ||
            (
             node->son[operand]->type == T_AST_SYMBOL &&
             node->son[operand]->symbol->type == SYMBOL_VAR &&
             node->son[operand]->symbol->datatype != DATATYPE_BOOL
            ) ||
            (
             node->son[operand]->type == T_AST_SYMBOL &&
             node->son[operand]->symbol->type == SYMBOL_LIT_INT
            ) ||
            (
             node->son[operand]->type == T_AST_SYMBOL &&
             node->son[operand]->symbol->type == SYMBOL_LIT_INT 
            )
          ){
          // tudo certo
        } else {
            fprintf(stderr, "Semantic ERROR: Operands not compatible.\n");
            semanticErrors++;
            node->type = T_AST_ERROR;
            }
        }      
        break;
    case T_AST_LESS:
    case T_AST_GREATER:
    case T_AST_LE:
    case T_AST_GE:
    case T_AST_EQ:
    case T_AST_DIF:
        // Check all above operands
        for(int operand = 0; operand < 2; operand++) {
            if(node->son[operand]->type != SYMBOL_LIT_INT &&
                node->son[operand]->type != SYMBOL_LIT_BOOL) {
                fprintf(stderr, "Semantic ERROR: Operands not compatible.\n");
                semanticErrors++;
                node->type = T_AST_ERROR;
            } else {
                node->type = DATATYPE_BOOL;
            }
        }
        break;
    case T_AST_PIPE:
        break; 
    case T_AST_ADDRESS:
        break; 
    case T_AST_NOT:
        if (node->son[0]->type != T_AST_SYMBOL &&
           node->son[0]->type != T_AST_EXPARR &&
           node->son[0]->type != T_AST_CLOSEDEXP &&
           node->son[0]->type != T_AST_ADD &&
           node->son[0]->type != T_AST_SUB &&
           node->son[0]->type != T_AST_MULT &&
           node->son[0]->type != T_AST_DIV &&
           node->son[0]->type != T_AST_LESS &&
           node->son[0]->type != T_AST_GREATER &&
           node->son[0]->type != T_AST_PIPE &&
           node->son[0]->type != T_AST_ADDRESS &&
           node->son[0]->type != T_AST_DOL &&
           node->son[0]->type != T_AST_HASHTAG &&
           node->son[0]->type != T_AST_LE &&
           node->son[0]->type != T_AST_GE &&
           node->son[0]->type != T_AST_EQ &&
           node->son[0]->type != T_AST_DIF &&
           node->son[0]->type != T_AST_FUNCTIONCALLER
           ) {
            fprintf(stderr, "Semantic ERROR: Operands not compatible.\n");
            semanticErrors++;
            node->type = T_AST_ERROR;
        }
        break;
    case T_AST_DOL:
        break;
    case T_AST_HASHTAG:
        break; 
    default:
        break;
    }

    for(i=0; i<MAX_SONS; ++i) {
        check_operands(node->son[i]);
    }
}

int convert_to_datatype(AST_NODE * node) {
    switch(node->son[0]->type) {
        case T_AST_KWCHAR: return DATATYPE_CHAR; break;
        case T_AST_KWINT: return DATATYPE_INT; break;
        case T_AST_KWBOOL: return DATATYPE_BOOL; break;
        default: return 0; break;
    }
}