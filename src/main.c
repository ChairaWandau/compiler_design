#include "lexer.h"
#include "sintax.h"
int main(int argc, char **argv)
{
    int out = 0;
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
        out = yyparse();
        //yyrestart(fpt);
        //yylex();
        fclose(fpt);
        return out;
    }
    // Чтение с консоли
    out = yyparse();
    //yylex();
    return out;
}