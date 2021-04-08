#include "ast.h"

void description(int type) {
    switch(type) {
        case T_AST_DEC: fprintf(stderr, "T_AST_DEC"); break;
        case T_AST_DECGLOBALVAL: fprintf(stderr, "T_AST_DECGLOBALVAL");  break;
        case T_AST_DECGLOBALVEC: fprintf(stderr, "T_AST_DECGLOVALVEC");  break;
        case T_AST_DECVEC: fprintf(stderr, "T_AST_DECVEC");  break;
        case T_AST_DECGLOBALVECWITHVALUE: fprintf(stderr, "T_AST_DECGLOBALVECWITHVALUE");  break;
        case T_AST_VECVALLIST: fprintf(stderr, "T_AST_VECVALLIST");  break;
        case T_AST_SYMBOL: fprintf(stderr, "T_AST_SYMBOL");  break;
        case T_AST_LASSIGN: fprintf(stderr, "T_AST_LASSIGN");  break;
        case T_AST_RASSIGN: fprintf(stderr, "T_AST_RASSING");  break;
        case T_AST_LASSIGNEXP: fprintf(stderr, "T_AST_LASSIGNEXP");  break;
        case T_AST_RASSIGNREXP: fprintf(stderr, "T_AST_RASSINGEXP");  break;
        case T_AST_IFTHEN: fprintf(stderr, "T_AST_IFTHEN");  break;
        case T_AST_IFTHENELSE: fprintf(stderr, "T_AST_IFTHENELSE");  break;
        case T_AST_WHILE: fprintf(stderr, "T_AST_WHILE");  break;
        case T_AST_RETURN: fprintf(stderr, "T_AST_RETURN");  break;
        case T_AST_READ: fprintf(stderr, "T_AST_READ");  break;
        case T_AST_FUNCPARAMLIST: fprintf(stderr, "T_AST_FUNCPARAMLIST");  break;
        case T_AST_TAILPARAMLIST: fprintf(stderr, "T_AST_TAILPARAMLIST");  break;
        case T_AST_HEADPARAMLIST: fprintf(stderr, "T_AST_HEADPARAMLIST");  break;
        case T_AST_CMDBLOCK: fprintf(stderr, "T_AST_CMDBLOCK");  break;
        case T_AST_CMDLIST: fprintf(stderr, "T_AST_CMDLIST");  break;
        case T_AST_CMDATTR: fprintf(stderr, "T_AST_CMDATTR");  break;
        case T_AST_CMDFLOW: fprintf(stderr, "T_AST_CMDFLOW");  break;
        case T_AST_CMDREAD: fprintf(stderr, "T_AST_CMDREAD");  break;
        case T_AST_CMDPRINT: fprintf(stderr, "T_AST_CMDPRINT");  break;
        case T_AST_CMDRETURN: fprintf(stderr, "T_AST_CMDRETURN");  break;
        case T_AST_CMDCMBLOCK: fprintf(stderr, "T_AST_CMDBLOCK");  break;
        case T_AST_PRINT: fprintf(stderr, "T_AST_PRINT");  break;
        case T_AST_TAILPRINTLIST: fprintf(stderr, "T_AST_TAILPRINTLIST");  break;
        case T_AST_HEADPRINTLIST: fprintf(stderr, "T_AST_HEADPRINTLIST");  break;
        case T_AST_EXPRHEADPRINTLIST: fprintf(stderr, "T_AST_EXPRHEADPRINTLIST");  break;
        case T_AST_EXPARR: fprintf(stderr, "T_AST_EXPARR");  break;
        case T_AST_CHAR: fprintf(stderr, "T_AST_CHAR");  break;
        case T_AST_CLOSEDEXP: fprintf(stderr, "T_AST_CLOSEDEXP");  break;
        case T_AST_ADD: fprintf(stderr, "T_AST_ADD");  break;
        case T_AST_SUB: fprintf(stderr, "T_AST_SUB");  break;
        case T_AST_MULT: fprintf(stderr, "T_AST_MULT");  break;
        case T_AST_DIV: fprintf(stderr, "T_AST_DIV");  break;
        case T_AST_LESS: fprintf(stderr, "T_AST_LESS");  break;
        case T_AST_GREATER: fprintf(stderr, "T_AST_GREATER");  break;
        case T_AST_PIPE: fprintf(stderr, "T_AST_PIPE");  break;
        case T_AST_ADDRESS: fprintf(stderr, "T_AST_ADDRESS");  break;
        case T_AST_NOT: fprintf(stderr, "T_AST_NOT");  break;
        case T_AST_DOL: fprintf(stderr, "T_AST_DOL");  break;
        case T_AST_HASHTAG: fprintf(stderr, "T_AST_HASHTAG");  break;
        case T_AST_LE: fprintf(stderr, "T_AST_LE");  break;
        case T_AST_GE: fprintf(stderr, "T_AST_GE");  break;
        case T_AST_EQ: fprintf(stderr, "T_AST_EQ");  break;
        case T_AST_DIF: fprintf(stderr, "T_AST_DIF");  break;
        case T_AST_FUNCTIONCALLER: fprintf(stderr, "T_AST_FUNCTIONCALLER");  break;
        case T_AST_ARGLIST: fprintf(stderr, "T_AST_ARGLIST");  break;
        case T_AST_TAILARGLIST: fprintf(stderr, "T_AST_TAILARGLIST");  break;
        case T_AST_KWCHAR: fprintf(stderr, "T_AST_KWCHAR"); break;
        case T_AST_KWINT: fprintf(stderr, "T_AST_KWINT"); break;
        case T_AST_KWBOOL: fprintf(stderr, "T_AST_KWBOOL"); break;
        case T_AST_KWPOINTER: fprintf(stderr, "T_AST_KWPOINTER"); break;
        case T_AST_FUNC: fprintf(stderr, "T_AST_FUNC"); break;
        default: fprintf(stderr, "UNKNOWN"); break;
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

    for(int i=0; i < level; ++i) {
        fprintf(stderr, " ");
    }

    if(level == 0) {
        fprintf(stderr, "AST(\n");
    }

    description(node->type);

    if(node->symbol) {
        fprintf(stderr, ",%s\n", node->symbol->text);
    } else {
        fprintf(stderr, ",0\n");
    }

    for(int i=0; i<MAX_SONS; ++i) {
        astPrint(node->son[i], level+1);
    }
}

void astUncompile(AST_NODE *node, FILE *file) {
    if(!node) {
        return;
    }

    switch (node->type)
    {
        case T_AST_DEC: 
            astUncompile(node->son[0], file);
            fprintf(file, ";\n");
            astUncompile(node->son[1], file);
            break;
        case T_AST_DECGLOBALVAL:
            astUncompile(node->son[0], file);
            fprintf(file, " %s :", node->symbol->text);
            astUncompile(node->son[1], file);
            break;
        case T_AST_DECGLOBALVEC: 
            astUncompile(node->son[0], file);
            break;
        case T_AST_DECVEC: 
            astUncompile(node->son[0], file);
            fprintf(file, "[" );
            astUncompile(node->son[1], file);
            fprintf(file,"] %s", node->symbol->text);
            break;
        case T_AST_DECGLOBALVECWITHVALUE: 
            astUncompile(node->son[0], file);
            fprintf(file, "[ ");
            astUncompile(node->son[2], file);
            fprintf(file, "] %s :", node->symbol->text);
            astUncompile(node->son[1], file);
            break;
        case T_AST_VECVALLIST: 
            astUncompile(node->son[0], file);
            astUncompile(node->son[1], file);
            break;
        case T_AST_SYMBOL: 
            fprintf(file, " %s ", node->symbol->text);
            break;
        case T_AST_LASSIGN:
            fprintf(file, " %s <- ", node->symbol->text);
            astUncompile(node->son[0], file);
            break;
        case T_AST_RASSIGN: 
            astUncompile(node->son[0], file);
            fprintf(file, " -> %s", node->symbol->text);
            break;
        case T_AST_LASSIGNEXP:
            fprintf(file, "%s [", node->symbol->text);
            astUncompile(node->son[0], file);
            fprintf(file, "] <- ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_RASSIGNREXP: 
            astUncompile(node->son[0], file);
            fprintf(file, " <- %s [", node->symbol->text);
            astUncompile(node->son[1], file);
            fprintf(file, "]");
            break;
        case T_AST_IFTHEN: 
            fprintf(file, "if (");
            astUncompile(node->son[0], file);
            fprintf(file, ") then ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_IFTHENELSE:
            fprintf(file, "if (");
            astUncompile(node->son[0], file);
            fprintf(file, ") then ");
            astUncompile(node->son[1], file);
            fprintf(file, "else ");
            astUncompile(node->son[2], file);
            break;
        case T_AST_WHILE:
            fprintf(file, "while (");
            astUncompile(node->son[0], file);
            fprintf(file, ") ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_RETURN:
            fprintf(file, "return ");
            astUncompile(node->son[0], file);
            break;
        case T_AST_READ: 
            fprintf(file, "read %s", node->symbol->text);
            break;
        case T_AST_FUNCPARAMLIST:
            astUncompile(node->son[0], file);
            astUncompile(node->son[1], file);
            break;
        case T_AST_TAILPARAMLIST: 
            fprintf(file, ", ");
            astUncompile(node->son[0], file);
            astUncompile(node->son[1], file);
            break;
        case T_AST_HEADPARAMLIST:
            astUncompile(node->son[0], file);
            fprintf(file, " %s ", node->symbol->text);
            break;
        case T_AST_CMDBLOCK:
            fprintf(file, "{ ");
            astUncompile(node->son[0], file);            
            fprintf(file, " }");
            break;
        case T_AST_CMDLIST: 
            astUncompile(node->son[0], file);            
            fprintf(file, ";\n");
            astUncompile(node->son[1], file);            
            break;
        case T_AST_CMDATTR: 
            astUncompile(node->son[0], file);            
            break;
        case T_AST_CMDFLOW: 
            astUncompile(node->son[0], file);            
            break;
        case T_AST_CMDREAD: 
            astUncompile(node->son[0], file);            
            break;
        case T_AST_CMDPRINT:
            astUncompile(node->son[0], file);            
            break;
        case T_AST_CMDRETURN:
            astUncompile(node->son[0], file);            
            break;
        case T_AST_CMDCMBLOCK: 
            astUncompile(node->son[0], file);            
            break;
        case T_AST_PRINT:
            fprintf(file, "print ");
            astUncompile(node->son[0], file);            
            astUncompile(node->son[1], file);            
            break;
        case T_AST_TAILPRINTLIST:
            fprintf(file, ", ");
            astUncompile(node->son[0], file);            
            astUncompile(node->son[1], file);            
            break;
        case T_AST_HEADPRINTLIST: 
            fprintf(file, "%s", node->symbol->text);
            break;
        case T_AST_EXPRHEADPRINTLIST:
            astUncompile(node->son[0], file);            
            break;
        case T_AST_EXPARR: 
            fprintf(file, "%s [", node->symbol->text);
            astUncompile(node->son[0], file);            
            fprintf(file, "]");
            break;
        case T_AST_CHAR:   
            fprintf(file, "%s", node->symbol->text);
            break;
        case T_AST_CLOSEDEXP:
            fprintf(file, "(");
            astUncompile(node->son[0], file);
            fprintf(file, ")");
            break;
        case T_AST_ADD: 
            astUncompile(node->son[0], file);
            fprintf(file, " + ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_SUB:
            astUncompile(node->son[0], file);
            fprintf(file, " - ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_MULT: 
            astUncompile(node->son[0], file);
            fprintf(file, " * ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_DIV: 
            astUncompile(node->son[0], file);
            fprintf(file, " / ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_LESS: 
            astUncompile(node->son[0], file);
            fprintf(file, " < ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_GREATER: 
            astUncompile(node->son[0], file);
            fprintf(file, " > ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_PIPE: 
            astUncompile(node->son[0], file);
            fprintf(file, " | ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_ADDRESS: 
            astUncompile(node->son[0], file);
            fprintf(file, " & ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_NOT:
            fprintf(file, "~");  
            astUncompile(node->son[0], file);
            break;
        case T_AST_DOL: 
            fprintf(file, "$");  
            astUncompile(node->son[0], file);
            break;
        case T_AST_HASHTAG: 
            fprintf(file, "#");  
            astUncompile(node->son[0], file);
            break;
        case T_AST_LE: 
            astUncompile(node->son[0], file);
            fprintf(file, " <= ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_GE: 
            astUncompile(node->son[0], file);
            fprintf(file, " >= ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_EQ: 
            astUncompile(node->son[0], file);
            fprintf(file, " == ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_DIF: 
            astUncompile(node->son[0], file);
            fprintf(file, " != ");
            astUncompile(node->son[1], file);
            break;
        case T_AST_FUNCTIONCALLER:
            fprintf(file, "%s (", node->symbol->text);
            astUncompile(node->son[0], file);
            fprintf(file, ")");
            break;
        case T_AST_ARGLIST:
            astUncompile(node->son[0], file);
            astUncompile(node->son[1], file);
            break;
        case T_AST_TAILARGLIST:
            fprintf(file, ", ");
            astUncompile(node->son[0], file);
            astUncompile(node->son[1], file);
            break;
        case T_AST_KWCHAR: 
            fprintf(file, "char ");
            break;
        case T_AST_KWINT: 
            fprintf(file, "int ");
            break;
        case T_AST_KWBOOL: 
            fprintf(file, "bool ");
            break;
        case T_AST_KWPOINTER:
            fprintf(file, "pointer ");
            break;
        case T_AST_FUNC: 
            astUncompile(node->son[0], file);
            fprintf(file, "%s (", node->symbol->text);
            astUncompile(node->son[1], file);
            fprintf(file, ") ");
            astUncompile(node->son[2], file);
            break;
        default: fprintf(stderr, "UNKNOWN"); break;
    }
}