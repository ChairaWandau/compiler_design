#ifndef TREE_H
#define TREE_H

// Виды узлов
typedef enum
{
    // Стартовый узел дерева
    PROGRAM,
    // Идентификатор 
    IDENTIFIER, 
    // Узел целочисленного литерала
    ILIT, 
    // Узел вызова функции
    CALL, 
    // Присваивание
    ASSIGN, 
    // Битовое и
    BAND, 
    // Битовое или
    BOR, 
    // Битовое исключающее или
    BXOR, 
    // Битовое не
    BNOT, 
    // Конец дерева
    END
} NodeType;

// Описание узла
typedef struct Node
{
    // Тип узла
    NodeType Type;
    // Родительский узел (для самого первого узла родительский узел отсутствует)
    struct Node *ParentNode;
    // Название типа узла
    char *TypeChar;   
    // Наименование литерала, идентификатора, названия функции (если есть)
    char *NameChar;

} Node_t;


#endif