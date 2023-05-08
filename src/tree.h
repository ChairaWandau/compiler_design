// Класс, описывающий дерево
#ifndef TREE_H
#define TREE_H
#include <stdbool.h>
//----------------------------------------------------------------
// Типы узлов
typedef enum
{
    // Стартовый узел дерева
    Node_PROGRAM,
    // Идентификатор 
    Node_IDENTIFIER, 
    // Узел целочисленного литерала
    Node_ILIT, 
    // Узел вызова функции
    Node_CALL, 
    // Присваивание
    Node_ASSIGN, 
    // Битовое и
    Node_BAND, 
    // Битовое или
    Node_BOR, 
    // Битовое исключающее или
    Node_BXOR, 
    // Битовое не
    Node_BNOT
} NodeType;
//----------------------------------------------------------------
// Описание узла
typedef struct NodeStruct
{
    // Тип узла
    NodeType Type;
    // Динамический массив дочерних узлов
    struct NodeStruct** Children; 
    // Количество детей 
    int NumberOfChildren; 
    // Число (если есть)
    char* ILIT_Char;
    // Идентификатор (если есть)
    char* IDENTIFIER_Char;
} NodeDescription;
//----------------------------------------------------------------
// Создание объекта узла
NodeDescription* CreateNode(NodeType Type);
//----------------------------------------------------------------
// Присваивание значения полю IDENTIFIER_Char
void SetIDENTIFIER(NodeDescription* Node, char* IDENTIFIER_Char);
//----------------------------------------------------------------
// Присваивание значения полю ILIT_Char
void SetILIT(NodeDescription* Node, char* ILIT_Char);
//----------------------------------------------------------------
// Добавление дочернего узла
void AddChildNode(NodeDescription* Node, NodeDescription* ChildNode);
//----------------------------------------------------------------
// Добавление дочерних узлов другого узла
void AddChildrenFromNode(NodeDescription* Node, NodeDescription* OtherNode);
//----------------------------------------------------------------
// Рекурсивное удаление всего дерева
void DelNode(NodeDescription * Node, int depth);
//----------------------------------------------------------------
// Рекурсивный вывод дерева
void PrintNode(NodeDescription* Node, int depth, int LastChild);
//----------------------------------------------------------------
#endif