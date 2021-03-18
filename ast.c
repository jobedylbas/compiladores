#include "ast.h"

void description(int type) {
    switch(type) {
        case T_AST_DEC: printf("T_AST_DEC"); break;
        case T_AST_DECVAL: printf("T_AST_DECVAL");  break;
        case T_AST_DECFUNC: printf("T_AST_DECFUNC");  break;
        case T_AST_DECCMD: printf("T_AST_DECCMD");  break;
        case T_AST_DECGLOBALVAL: printf("T_AST_DECGLOBALVAL");  break;
        case T_AST_DECGLOBALVEC: printf("T_AST_DECGLOVALVEC");  break;
        case T_AST_DECVEC: printf("T_AST_DECVEC");  break;
        case T_AST_DECGLOBALVECWITHVALUE: printf("T_AST_DECGLOBALVECWITHVALUE");  break;
        case T_AST_VECVALLIST: printf("T_AST_VECVALLIST");  break;
        case T_AST_SYMBOL: printf("T_AST_SYMBOL");  break;
        case T_AST_LASSIGN: printf("T_AST_LASSIGN");  break;
        case T_AST_RASSIGN: printf("T_AST_RASSING");  break;
        case T_AST_LASSIGNEXP: printf("T_AST_LASSIGNEXP");  break;
        case T_AST_RASSIGNREXP: printf("T_AST_RASSINGEXP");  break;
        case T_AST_IFTHEN: printf("T_AST_IFTHEN");  break;
        case T_AST_IFTHENELSE: printf("T_AST_IFTHENELSE");  break;
        case T_AST_WHILE: printf("T_AST_WHILE");  break;
        case T_AST_RETURN: printf("T_AST_RETURN");  break;
        case T_AST_READ: printf("T_AST_READ");  break;
        case T_AST_FUNCPARAMLIST: printf("T_AST_FUNCPARAMLIST");  break;
        case T_AST_TAILPARAMLIST: printf("T_AST_TAILPARAMLIST");  break;
        case T_AST_HEADPARAMLIST: printf("T_AST_HEADPARAMLIST");  break;
        case T_AST_CMDBLOCK: printf("T_AST_CMDBLOCK");  break;
        case T_AST_CMDLIST: printf("T_AST_CMDLIST");  break;
        case T_AST_CMDATTR: printf("T_AST_CMDATTR");  break;
        case T_AST_CMDFLOW: printf("T_AST_CMDFLOW");  break;
        case T_AST_CMDREAD: printf("T_AST_CMDREAD");  break;
        case T_AST_CMDPRINT: printf("T_AST_CMDPRINT");  break;
        case T_AST_CMDRETURN: printf("T_AST_CMDRETURN");  break;
        case T_AST_CMDCMBLOCK: printf("T_AST_CMDBLOCK");  break;
        case T_AST_PRINT: printf("T_AST_PRINT");  break;
        case T_AST_TAILPRINTLIST: printf("T_AST_TAILPRINTLIST");  break;
        case T_AST_HEADPRINTLIST: printf("T_AST_HEADPRINTLIST");  break;
        case T_AST_EXPRHEADPRINTLIST: printf("T_AST_EXPRHEADPRINTLIST");  break;
        case T_AST_EXPARR: printf("T_AST_EXPARR");  break;
        case T_AST_CHAR: printf("T_AST_CHAR");  break;
        case T_AST_CLOSEDEXP: printf("T_AST_CLOSEDEXP");  break;
        case T_AST_ADD: printf("T_AST_ADD");  break;
        case T_AST_SUB: printf("T_AST_SUB");  break;
        case T_AST_MULT: printf("T_AST_MULT");  break;
        case T_AST_DIV: printf("T_AST_DIV");  break;
        case T_AST_LESS: printf("T_AST_LESS");  break;
        case T_AST_GREATER: printf("T_AST_GREATER");  break;
        case T_AST_PIPE: printf("T_AST_PIPE");  break;
        case T_AST_ADDRESS: printf("T_AST_ADDRESS");  break;
        case T_AST_NOT: printf("T_AST_NOT");  break;
        case T_AST_DOL: printf("T_AST_DOL");  break;
        case T_AST_HASHTAG: printf("T_AST_HASHTAG");  break;
        case T_AST_LE: printf("T_AST_LE");  break;
        case T_AST_GE: printf("T_AST_GE");  break;
        case T_AST_EQ: printf("T_AST_EQ");  break;
        case T_AST_DIF: printf("T_AST_DIF");  break;
        case T_AST_FUNCTIONCALLER: printf("T_AST_FUNCTIONCALLER");  break;
        case T_AST_ARGLIST: printf("T_AST_ARGLIST");  break;
        case T_AST_TAILARGLIST: printf("T_AST_TAILARGLIST");  break;
        default: printf("UNKNOWN"); break;
    }
}

AST_NODE *astCreate(int type, HASH_NODE *symbol, AST_NODE *son0, AST_NODE *son1, AST_NODE *son2, AST_NODE *son3) {
    AST_NODE *newNode;
    newNode = (AST_NODE*) calloc(1, sizeof(AST_NODE));
    
    newNode->type = type;
    newNode->symbol = symbol;
    newNode->son[0] = son0;
    newNode->son[1] = son1;
    newNode->son[2] = son2;
    newNode->son[3] = son3;

    return newNode;
}

void astPrint(AST_NODE *node, int level) {
    if (!node) return;

    for(int i=0; i < level; i++) {
        printf(" ");
    }

    printf("\nAST(");

    description(node->type);

    if(node->symbol) {
        printf(",%s\n", node->symbol->text);
    } else {
        printf(",0\n");
    }

    for(int i=0; i<MAX_SONS; ++i) {
        astPrint(node->son[i], level+1);
    }
}