#include "lexer.h"
#include "sintax.h"
#include "tree.h"
int main(int argc, char **argv)
{
    int out = 0;
    // Создаем первый узел дерева
    NodeDescription* ProgramNode = CreateNode(Node_PROGRAM);
    // Ошибка некорректного использования на ввод более одного файла
    if(argc > 2)
    {
        printf("ERROR: Incorrect use.\n");
        return 1;
    }
    // Чтение файла
    else if(argc == 2)
    {
        FILE *fpt;
        fpt = fopen(argv[1],"r");
        // Если файл нельзя открыть - завершение программы
        if(!fpt)
        { 
            return 1;
        }
        yyin = fpt;
        yyparse(ProgramNode);
        fclose(fpt);
        // Если нет ошибок - выводим дерево
        if(!(out = GotError())) PrintNode(ProgramNode, 0, 0);
        // Удаляем дерево (очищаем память)
        DelNode(ProgramNode, 0);
        return out;
    }
    // Чтение с консоли
    yyparse(ProgramNode);
    // Если нет ошибок - выводим дерево
    if(!(out = GotError())) PrintNode(ProgramNode, 0, 0);
    // Удаляем дерево (очищаем память)
    DelNode(ProgramNode, 0);
    return out;
}