%{
int yylex();
int yyerror();
%}

%token KW_CHAR
%token KW_INT
%token KW_BOOL
%token KW_POINTER

%token KW_IF 
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_READ
%token KW_PRINT
%token KW_RETURN 

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token LEFT_ASSIGN
%token RIGHT_ASSIGN
%token TK_IDENTIFIER 

%token LIT_INTEGER
%token LIT_TRUE
%token LIT_FALSE 
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%left '|' '&'
%left '<' '>' OPERATOR_EQ OPERATOR_DIF OPERATOR_GE OPERATOR_LE
%left '+' '-'
%left '*' '/'

%right '~' '$' '#'

%%

program: decList
    ;

decList: dec ';' decList
    |
    ;

dec: decGlobalVariable
    | func
    | cmd
    ;

decGlobalVariable: type TK_IDENTIFIER ':' literal
    | decGlobalVector
    ;

decGlobalVector: type '[' LIT_INTEGER ']' TK_IDENTIFIER 
    | type  '[' LIT_INTEGER ']' TK_IDENTIFIER ':' vectorValueList
    ;

vectorValueList: literal vectorValueList
    |
    ;

literal: LIT_INTEGER
    | LIT_CHAR
    | LIT_FALSE
    | LIT_TRUE
    ;

attr: TK_IDENTIFIER LEFT_ASSIGN expr
    | expr RIGHT_ASSIGN TK_IDENTIFIER
    | TK_IDENTIFIER '[' expr ']' LEFT_ASSIGN expr
    | expr RIGHT_ASSIGN TK_IDENTIFIER '[' expr ']'
    ;

flowControl: KW_IF '(' expr ')' KW_THEN cmd
    | KW_IF '(' expr ')' KW_THEN cmdBlock
    | KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmd
    | KW_IF '(' expr ')' KW_THEN cmdBlock KW_ELSE cmdBlock
    | KW_IF '(' expr ')' KW_THEN cmdBlock KW_ELSE cmd
    | KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmdBlock
    | KW_WHILE '(' expr ')' cmd
    | KW_WHILE '(' expr ')' cmdBlock
    ;

return: KW_RETURN expr
    ;

read: KW_READ TK_IDENTIFIER
    ;

func: type TK_IDENTIFIER '(' funcParamList ')' cmdBlock
    ;

funcParamList: headParamList tailParamList
    |
    ;

tailParamList: ','  funcParamList
    |
    ;

headParamList: type TK_IDENTIFIER
    ;

cmdBlock: '{' cmdList '}'
    ;

cmdList: cmd tailCmdList
    ;

tailCmdList: ';' cmd tailCmdList
    |
    ;

cmd: attr
    | flowControl
    | read
    | print
    | return
    | cmdBlock
    |
    ;

print: KW_PRINT headPrintList tailPrintList
    ;

tailPrintList: ',' headPrintList tailPrintList
    |
    ;

headPrintList: LIT_STRING
    | expr
    ;

expr: TK_IDENTIFIER
    | TK_IDENTIFIER '[' expr ']'
    | LIT_CHAR
    | LIT_TRUE
    | LIT_FALSE
    | LIT_INTEGER
    | '(' expr ')'
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr
    | expr '|' expr
    | expr '&' expr
    | '~' expr
    | '$' expr
    | '#' expr
    | expr OPERATOR_LE expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_DIF expr
    | TK_IDENTIFIER '(' argList ')'
    ;

argList: expr tailArgList
    ;

tailArgList: ',' expr tailArgList
    |
    ;

type: KW_CHAR
    | KW_INT
    | KW_BOOL
    | KW_POINTER
    ;

%%

int yyerror() {
    printf("Syntax error at line %d.\n", getLineNumber());
    exit(3);
}