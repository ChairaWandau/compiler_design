%{
    // Подключаем код на flex
    #include "lexer.h"
    void yyerror(char const * msg);
    int line=1;
%}

%token EOL IDENTIFIER LPARENT RPARENT COMMA ASSIGN ILIT BOR BAND BXOR BNOT

%left BOR
%left BXOR
%left BAND
%left BNOT

%%
    input: 
        | input line 
    ;
    line: EOL
        | oper EOL { line++; }
        | assignment EOL { line++; }
    ;
    oper: IDENTIFIER
        | ILIT
        | LPARENT oper RPARENT 
        | oper COMMA oper
        /*| oper ASSIGN oper*/
        | oper BOR oper
        | oper BAND oper
        | oper BXOR oper
        | BNOT oper
        | oper LPARENT oper RPARENT
        | oper LPARENT RPARENT
    ; 
    assignment: IDENTIFIER ASSIGN oper
    ;
%%

void yyerror(char const * msg){
    printf("In line %d: syntax error\n", line);
}