#ifndef AST_HEADER
#define AST_HEADER

#include <stdio.h>
#include "hash.h"

#define MAX_SONS 4

#define T_AST_DEC 1
#define T_AST_DECVAL 2
#define T_AST_DECFUNC 3
#define T_AST_DECCMD 4
#define T_AST_DECGLOBALVAL 5
#define T_AST_DECGLOBALVEC 6
#define T_AST_DECVEC 7
#define T_AST_DECGLOBALVECWITHVALUE 8
#define T_AST_VECVALLIST 9
#define T_AST_SYMBOL 10
#define T_AST_LASSIGN 11
#define T_AST_RASSIGN 12
#define T_AST_LASSIGNEXP 13
#define T_AST_RASSIGNREXP 14
#define T_AST_IFTHEN 15
#define T_AST_IFTHENELSE 16
#define T_AST_WHILE 17
#define T_AST_RETURN 18
#define T_AST_READ 19
#define T_AST_FUNCPARAMLIST 20
#define T_AST_TAILPARAMLIST 21
#define T_AST_HEADPARAMLIST 22
#define T_AST_CMDBLOCK 23
#define T_AST_CMDLIST 24
#define T_AST_CMDATTR 25
#define T_AST_CMDFLOW 26
#define T_AST_CMDREAD 27
#define T_AST_CMDPRINT 28
#define T_AST_CMDRETURN 29
#define T_AST_CMDCMBLOCK 30
#define T_AST_PRINT 31
#define T_AST_TAILPRINTLIST 32
#define T_AST_HEADPRINTLIST 33
#define T_AST_EXPRHEADPRINTLIST 34
#define T_AST_EXPARR 35
#define T_AST_CHAR 36
#define T_AST_CLOSEDEXP 37
#define T_AST_ADD 38
#define T_AST_SUB 39
#define T_AST_MULT 40
#define T_AST_DIV 41
#define T_AST_LESS 42
#define T_AST_GREATER 43
#define T_AST_PIPE 44
#define T_AST_ADDRESS 45
#define T_AST_NOT 46
#define T_AST_DOL 47
#define T_AST_HASHTAG 48
#define T_AST_LE 49
#define T_AST_GE 50
#define T_AST_EQ 51
#define T_AST_DIF 52
#define T_AST_FUNCTIONCALLER 53
#define T_AST_ARGLIST 54
#define T_AST_TAILARGLIST 55
#define T_AST_KWCHAR 56
#define T_AST_KWINT 57
#define T_AST_KWBOOL 58
#define T_AST_KWPOINTER 59
#define T_AST_FUNC 60
typedef struct ast_struct {
    int type;
    HASH_NODE *symbol;
    struct ast_struct *son[MAX_SONS];
} AST_NODE;

AST_NODE *astCreate(int type, HASH_NODE *symbol, AST_NODE *son0, AST_NODE *son1, AST_NODE *son2, AST_NODE *son3);
void astPrint(AST_NODE *node, int level);

#endif