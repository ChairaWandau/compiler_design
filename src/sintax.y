%{
    // Подключаем код на flex и код для отрисовки дерева
    #include <stdio.h>
    #include <stdbool.h>
    #include "lexer.h"
    #include "../src/tree.h"
    // Индикатор наличия/отсутствия ошибки
    static bool Error = false;
    // Метод для возвращения ошибки 
    bool GotError(void);
    void yyerror(NodeDescription * ProgramNode,char const * msg);
%}

// Код перед объявлениями бизона
%code requires {
  #include "../src/tree.h"
}

// Код, потребный в хедере
%code provides
{
  #include <stdbool.h>
  #include "../src/tree.h"
  bool GotError(void);
}

// Передача корня дерева в бизон
%parse-param 
{
    NodeDescription * ProgramNode
}

// Возвращаемые типы
%union
{
   NodeDescription * NodeValue;
   char * StringValue;
}

%token EOL IDENTIFIER LPARENT RPARENT COMMA ASSIGN ILIT BOR BAND BXOR BNOT

%left BOR
%left BXOR
%left BAND
%left BNOT

// Присваиваем возвращаемые типы нетерминалам
%type<NodeValue> input line func func_arg oper assignment
%type<StringValue> identifier ilit

%destructor { if($$!= ProgramNode && $$ != NULL) {DelNode($$, 0);}} <NodeValue>
%destructor { free($$); } <StringValue>

%%
    input:  { 
                $$ = NULL; 
            }
        | input line  
            {
                if($2!=NULL){
                    AddChildNode (ProgramNode, $2);
                    $$ = ProgramNode; 
                }
                else{
                    $$ = NULL; 
                }
            }
    ;
    line: EOL
            { 
                $$ = NULL; 
            }
        | oper EOL 
            { 
                $$ = $1; 
            }
        | assignment EOL 
            { 
                $$ = $1; 
            }
    ;
    oper: identifier 
            { 
                $$ = CreateNode(Node_IDENTIFIER); 
                SetIDENTIFIER($$, $1);  
                free($1);
            }
        | ilit 
            { 
                $$ = CreateNode(Node_ILIT); 
                SetILIT($$, $1); 
                free($1);
            }
        | func 
            { 
                $$ = $1; 
            }
        | LPARENT oper RPARENT 
            { 
                $$ = $2;
            }
        | oper BOR oper 
            {
                $$ = CreateNode(Node_BOR);
                AddChildNode ($$, $1);
                AddChildNode ($$, $3);
            }
        | oper BAND oper 
            {
                $$ = CreateNode(Node_BAND);
                AddChildNode ($$, $1);
                AddChildNode ($$, $3);
            }
        | oper BXOR oper 
            {
                $$ = CreateNode(Node_BXOR);
                AddChildNode ($$, $1);
                AddChildNode ($$, $3);
            }
        | BNOT oper 
            {
                $$ = CreateNode(Node_BNOT);
                AddChildNode ($$, $2);
            } 
    ; 
    func: identifier LPARENT RPARENT 
            { 
                $$ = CreateNode(Node_CALL);
                SetIDENTIFIER($$, $1);
                free($1);
            }
        | identifier LPARENT func_arg RPARENT  
            {
                $$ = CreateNode(Node_CALL);
                SetIDENTIFIER($$, $1);
                AddChildrenFromNode($$, $3);

                free($1);
            }
    ;
    func_arg: oper 
            { 
                $$ = CreateNode(Node_CALL);
                AddChildNode ($$, $1);
            }
        | func_arg COMMA func_arg 
            { 
                $$ = CreateNode(Node_CALL);
                AddChildrenFromNode($$, $1);

                AddChildrenFromNode($$, $3);

            }
    ;
    assignment: identifier ASSIGN oper 
            {
                $$ = CreateNode(Node_ASSIGN);
                NodeDescription * Node_Identifier = CreateNode(Node_IDENTIFIER); 
                SetIDENTIFIER(Node_Identifier, $1);  
                AddChildNode ($$, Node_Identifier);
                AddChildNode ($$, $3);
                free($1);
            }
    ;
    identifier: IDENTIFIER 
            { 
                $$ = strdup(yytext);
            }
    ;
    ilit: ILIT  
            { 
                $$ = strdup(yytext);
            }
    ;
%%

bool GotError(void)
{
    return Error;
}
void yyerror(NodeDescription * ProgramNode, char const * msg){
    Error = true;
}