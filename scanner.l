%{
    #include "hash.h"
    #include "ast.h"
    #include "y.tab.h"

    int running = 1;
    int lineNumber = 0;
    int getLineNumber() { return lineNumber; }
%}

%x COMMENT

%%

"char"                                                  {return KW_CHAR;}
"int"                                                   {return KW_INT;}
"bool"                                                  {return KW_BOOL;}
"pointer"                                               {return KW_POINTER;}

"if"                                                    {return KW_IF;}
"then"                                                  {return KW_THEN;}
"else"                                                  {return KW_ELSE;}
"while"                                                 {return KW_WHILE;}
"read"                                                  {return KW_READ;}
"print"                                                 {return KW_PRINT;}
"return"                                                {return KW_RETURN;}

"true"                                                  {yylval.symbol = hashInsert(yytext, LIT_TRUE); return LIT_TRUE;}
"false"                                                 {yylval.symbol = hashInsert(yytext, LIT_FALSE); return LIT_FALSE;}

"<="                                                    {return OPERATOR_LE;}
">="                                                    {return OPERATOR_GE;}
"=="                                                    {return OPERATOR_EQ;}
"!="                                                    {return OPERATOR_DIF;}
"<-"                                                    {return LEFT_ASSIGN;}
"->"                                                    {return RIGHT_ASSIGN;}

\'([^\"\\\n]|\\.)\'                                     {yylval.symbol = hashInsert(yytext, LIT_CHAR); return LIT_CHAR;}
\'([^'\\\n]?|\\.)*\'                                    {return TOKEN_ERROR;} 

\"([^\"\\\n]|\\.)*\"                                    {yylval.symbol = hashInsert(yytext, LIT_STRING); return LIT_STRING;}

[\,\;\:\(\)\[\]\{\}\+\-\*\/\<\>\=\.\~\&\$\#\|]          {return yytext[0];}

[0-9]+                                                  {yylval.symbol = hashInsert(yytext, LIT_INTEGER); return LIT_INTEGER;}

[A-Za-z_][A-Za-z_0-9]*                                  {yylval.symbol = hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER;}

[ \t]

"\n"                                                    {lineNumber++;}

"//".*
"/*"                                                    {BEGIN(COMMENT);}

.                                                       {return TOKEN_ERROR;}                                

<COMMENT>"*/"                                           {BEGIN(INITIAL);}
<COMMENT>"\n"                                           {lineNumber++;}
<COMMENT>.

%%

#include "y.tab.c"
#include "hash.c"
#include "main.c"
#include "ast.c"
// #include "main_prof.c"


int yywrap() {
    running = 0;
    return 1;
}

int isRunning(void) {
    return running;
}

void initMe(void) {

}