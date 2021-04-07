%{
int yylex();
int yyerror();

AST_NODE *ast;
%}

%union {
    HASH_NODE *symbol;
    AST_NODE *ast;
}

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
%token<symbol> TK_IDENTIFIER 

%token<symbol> LIT_INTEGER
%token<symbol> LIT_TRUE
%token<symbol> LIT_FALSE
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING

%token TOKEN_ERROR

%type<ast> program
%type<ast> decList
%type<ast> dec
%type<ast> decGlobalVariable
%type<ast> decGlobalVector
%type<ast> vectorValueList
%type<ast> literal
%type<ast> attr
%type<ast> flowControl
%type<ast> return
%type<ast> read
%type<ast> func
%type<ast> funcParamList
%type<ast> headParamList
%type<ast> tailParamList
%type<ast> cmdBlock
%type<ast> cmdList
%type<ast> cmd
%type<ast> print
%type<ast> tailPrintList
%type<ast> headPrintList
%type<ast> expr
%type<ast> argList
%type<ast> tailArgList
%type<ast> type

%left '|' '&'
%left '<' '>' OPERATOR_EQ OPERATOR_DIF OPERATOR_GE OPERATOR_LE
%left '+' '-'
%left '*' '/'

%right '~' '$' '#'

%%

program: decList                                                    {ast =$1; astPrint($1, 0);}                               
    ;

decList: dec ';' decList                                            {$$ = astCreate(T_AST_DEC, 0, $1, $3, 0, 0);}
    |                                                               {$$ = 0;}
    ;

dec: decGlobalVariable                                              
    | func                                                          
    | cmd                                                           
    ;

decGlobalVariable: type TK_IDENTIFIER ':' literal                   {$$ = astCreate(T_AST_DECGLOBALVAL, $2, $1, $4, 0, 0);}
    | decGlobalVector                                               {$$ = astCreate(T_AST_DECGLOBALVEC, 0, $1, 0, 0, 0);}
    ;

decGlobalVector: type '[' LIT_INTEGER ']' TK_IDENTIFIER             {$$ = astCreate(T_AST_DECVEC, $5, $1, astCreate(T_AST_SYMBOL, $3, 0, 0, 0, 0), 0, 0);}
    | type  '[' LIT_INTEGER ']' TK_IDENTIFIER ':' vectorValueList   {$$ = astCreate(T_AST_DECGLOBALVECWITHVALUE, $5, $1, $7, astCreate(T_AST_SYMBOL,$3, 0, 0, 0, 0), 0);}
    ;

vectorValueList: literal vectorValueList                            {$$ = astCreate(T_AST_VECVALLIST, 0, $1, $2, 0, 0);}
    |                                                               {$$ = 0;}
    ;

literal: LIT_INTEGER                                                {$$ = astCreate(T_AST_SYMBOL, $1, 0, 0, 0, 0);}
    | LIT_CHAR                                                      {$$ = astCreate(T_AST_SYMBOL, $1, 0, 0, 0, 0);}
    | LIT_FALSE                                                     {$$ = astCreate(T_AST_SYMBOL, $1, 0, 0, 0, 0);}
    | LIT_TRUE                                                      {$$ = astCreate(T_AST_SYMBOL, $1, 0, 0, 0, 0);}
    ;

attr: TK_IDENTIFIER LEFT_ASSIGN expr                                {$$ = astCreate(T_AST_LASSIGN, $1, $3, 0, 0, 0);}
    | expr RIGHT_ASSIGN TK_IDENTIFIER                               {$$ = astCreate(T_AST_RASSIGN, $3, $1, 0, 0, 0);}
    | TK_IDENTIFIER '[' expr ']' LEFT_ASSIGN expr                   {$$ = astCreate(T_AST_LASSIGNEXP, $1, $3, $6, 0, 0);}
    | expr RIGHT_ASSIGN TK_IDENTIFIER '[' expr ']'                  {$$ = astCreate(T_AST_RASSIGNREXP, $3, $1, $5, 0, 0);}
    ;

flowControl: KW_IF '(' expr ')' KW_THEN cmd                         {$$ = astCreate(T_AST_IFTHEN, 0, $3, $6, 0, 0);}
    | KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmd                    {$$ = astCreate(T_AST_IFTHENELSE, 0, $3, $6, $8, 0);}
    | KW_WHILE '(' expr ')' cmd                                     {$$ = astCreate(T_AST_WHILE, 0, $3, 0, 0, 0);}
    ;

return: KW_RETURN expr                                              {$$ = astCreate(T_AST_RETURN, 0, $2, 0, 0, 0);}
    ;

read: KW_READ TK_IDENTIFIER                                         {$$ = astCreate(T_AST_READ, $2, 0, 0, 0, 0);}
    ;

func: type TK_IDENTIFIER '(' funcParamList ')' cmdBlock             {$$ = astCreate(T_AST_FUNC, $2, $1, $4, $6, 0);}
    ;

funcParamList: headParamList tailParamList                          {$$ = astCreate(T_AST_FUNCPARAMLIST, 0, $1, $2, 0, 0);}
    |                                                               {$$ = 0;}
    ;

tailParamList: ',' headParamList funcParamList                      {$$ = astCreate(T_AST_TAILPARAMLIST, 0, $2, $3, 0, 0);}
    |                                                               {$$ = 0;}
    ;

headParamList: type TK_IDENTIFIER                                   {$$ = astCreate(T_AST_HEADPARAMLIST, $2, $1, 0, 0, 0);}
    ;

cmdBlock: '{' cmdList '};'                                          {$$ = astCreate(T_AST_CMDBLOCK, 0, $2, 0, 0, 0);}
    ;

cmdList: cmd ';' cmdList                                            {$$ = astCreate(T_AST_CMDLIST, 0, $1, $3, 0, 0);}
    |                                                               {$$ = 0;}
    ;

cmd: attr                                                           {$$ = astCreate(T_AST_CMDATTR, 0, $1, 0, 0, 0);}
    | flowControl                                                   {$$ = astCreate(T_AST_CMDFLOW, 0, $1, 0, 0, 0);}
    | read                                                          {$$ = astCreate(T_AST_CMDREAD, 0, $1, 0, 0, 0);}
    | print                                                         {$$ = astCreate(T_AST_CMDPRINT, 0, $1, 0, 0, 0);}
    | return                                                        {$$ = astCreate(T_AST_CMDRETURN, 0, $1, 0, 0, 0);}
    | cmdBlock                                                      {$$ = astCreate(T_AST_CMDCMBLOCK, 0, $1, 0, 0, 0);}
    |                                                               {$$ = 0;}
    ;

print: KW_PRINT headPrintList tailPrintList                         {$$ = astCreate(T_AST_PRINT, 0, $2, $3, 0, 0);}
    ;

tailPrintList: ',' headPrintList tailPrintList                      {$$ = astCreate(T_AST_TAILPRINTLIST, 0, $2, $3, 0, 0);}
    |                                                               {$$ = 0;}
    ;

headPrintList: LIT_STRING                                           {$$ = astCreate(T_AST_HEADPRINTLIST, $1, 0, 0, 0, 0);}
    | expr                                                          {$$ = astCreate(T_AST_EXPRHEADPRINTLIST, 0, $1, 0, 0, 0);}
    ;

expr: TK_IDENTIFIER                                                 {$$ = astCreate(T_AST_SYMBOL, $1, 0, 0, 0, 0);}
    | TK_IDENTIFIER '[' expr ']'                                    {$$ = astCreate(T_AST_EXPARR, $1, $3, 0, 0, 0);}
    | LIT_CHAR                                                      {$$ = astCreate(T_AST_SYMBOL, $1, 0, 0, 0, 0);}
    | LIT_TRUE                                                      {$$ = astCreate(T_AST_SYMBOL, $1, 0, 0, 0, 0);}
    | LIT_FALSE                                                     {$$ = astCreate(T_AST_SYMBOL, $1, 0, 0, 0, 0);}
    | LIT_INTEGER                                                   {$$ = astCreate(T_AST_SYMBOL, $1, 0, 0, 0, 0);}
    | '(' expr ')'                                                  {$$ = astCreate(T_AST_CLOSEDEXP, 0, $2, 0, 0, 0);}
    | expr '+' expr                                                 {$$ = astCreate(T_AST_ADD, 0, $1, $3, 0, 0);}
    | expr '-' expr                                                 {$$ = astCreate(T_AST_SUB, 0, $1, $3, 0, 0);}
    | expr '*' expr                                                 {$$ = astCreate(T_AST_MULT, 0, $1, $3, 0, 0);}
    | expr '/' expr                                                 {$$ = astCreate(T_AST_DIV, 0, $1, $3, 0, 0);}
    | expr '<' expr                                                 {$$ = astCreate(T_AST_LESS, 0, $1, $3, 0, 0);}
    | expr '>' expr                                                 {$$ = astCreate(T_AST_GREATER, 0, $1, $3, 0, 0);}
    | expr '|' expr                                                 {$$ = astCreate(T_AST_PIPE, 0, $1, $3, 0, 0);}
    | expr '&' expr                                                 {$$ = astCreate(T_AST_ADDRESS, 0, $1, $3, 0, 0);}
    | '~' expr                                                      {$$ = astCreate(T_AST_NOT, 0, $2, 0, 0, 0);}
    | '$' expr                                                      {$$ = astCreate(T_AST_DOL, 0, $2, 0, 0, 0);}
    | '#' expr                                                      {$$ = astCreate(T_AST_HASHTAG, 0, $2, 0, 0, 0);}
    | expr OPERATOR_LE expr                                         {$$ = astCreate(T_AST_LE, 0, $1, $3, 0, 0);}
    | expr OPERATOR_GE expr                                         {$$ = astCreate(T_AST_GE, 0, $1, $3, 0, 0);}
    | expr OPERATOR_EQ expr                                         {$$ = astCreate(T_AST_EQ, 0, $1, $3, 0, 0);}
    | expr OPERATOR_DIF expr                                        {$$ = astCreate(T_AST_DIF, 0, $1, $3, 0, 0);}
    | TK_IDENTIFIER '(' argList ')'                                 {$$ = astCreate(T_AST_FUNCTIONCALLER, $1, $3, 0, 0, 0);}
    ;

argList: expr tailArgList                                           {$$ = astCreate(T_AST_ARGLIST, 0, $1, $2, 0, 0);}
    ;

tailArgList: ',' expr tailArgList                                   {$$ = astCreate(T_AST_TAILARGLIST, 0, $2, $3, 0, 0);}
    |                                                               {$$ = 0;}
    ;

type: KW_CHAR                                                       {$$ = astCreate(T_AST_KWCHAR, 0, 0, 0, 0, 0);}
    | KW_INT                                                        {$$ = astCreate(T_AST_KWINT, 0, 0, 0, 0, 0);}
    | KW_BOOL                                                       {$$ = astCreate(T_AST_KWBOOL, 0, 0, 0, 0, 0);}
    | KW_POINTER                                                    {$$ = astCreate(T_AST_KWPOINTER, 0, 0, 0, 0, 0);}
    ;

%%

int yyerror() {
    printf("Syntax error at line %d.\n", getLineNumber());
    exit(3);
}

AST_NODE* getAST() {
    return ast;
} 