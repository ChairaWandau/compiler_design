// Класс, содержащий методы для работы с деревом
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "tree.h"
//----------------------------------------------------------------
/// @brief Типы узлов в строковом представлении
static const char * NodeType_String[] =
{
    // Стартовый узел дерева
    [Node_PROGRAM] = "PROGRAM",
    // Идентификатор 
    [Node_IDENTIFIER] = "IDENTIFIER",
    // Узел целочисленного литерала
    [Node_ILIT] = "ILIT",
    // Узел вызова функции
    [Node_CALL] = "CALL",
    // Присваивание
    [Node_ASSIGN] = "ASSIGN",
    // Битовое и
    [Node_BAND] = "BAND",
    // Битовое или
    [Node_BOR] = "BOR",
    // Битовое исключающее или
    [Node_BXOR] = "BXOR",
    // Битовое не
    [Node_BNOT] = "BNOT",
};
//----------------------------------------------------------------
/// @brief Создание нового узла
/// @param Type тип узла
/// @return Новый узел дерева
NodeDescription* CreateNode(NodeType Type){
    // Создаем объект узла
    NodeDescription* NewNode;
    // Выделяем память под него
    NewNode = calloc(1, sizeof(NodeDescription));
    // Присваиваем тип узла
    NewNode->Type = Type;
    // При создании узла у него еще нет дочерних узлов
    NewNode->NumberOfChildren = 0;
    return NewNode;
}
//----------------------------------------------------------------
/// @brief Присваивание значения полю IDENTIFIER_Char
/// @param Node Узел, которому присваиваем
/// @param IDENTIFIER_Char Название идентификатора
void SetIDENTIFIER(NodeDescription* Node, char* IDENTIFIER_Char){
    Node->IDENTIFIER_Char = strdup(IDENTIFIER_Char);
}
//----------------------------------------------------------------
/// @brief Присваивание значения полю ILIT_Char
/// @param Node Узел, которому присваиваем
/// @param ILIT_Char Число в строковом представлении
void SetILIT(NodeDescription* Node, char* ILIT_Char){
    Node->ILIT_Char = strdup(ILIT_Char);
}
//----------------------------------------------------------------
/// @brief Добавление дочернего узла
/// @param Node Узел, которому присваиваем
/// @param ChildNode Дочерний узел
void AddChildNode(NodeDescription* Node, NodeDescription* ChildNode){
    if(ChildNode!= NULL){
        // Увеличиваем количество дочерних узлов на 1
        Node->NumberOfChildren+=1;
        // Увеличиваем размер массива дочерних узлов на 1
        Node->Children=(NodeDescription**)realloc(Node->Children, Node->NumberOfChildren*sizeof(NodeDescription*));
        // На всякий случай проверяем, что массив не нулевого размера
        if (Node->Children != NULL){
            // Добавляем новый дочений узел в массив
            Node->Children[Node->NumberOfChildren-1] = ChildNode;
        }
    }
}
//----------------------------------------------------------------
/// @brief Добавление дочерних узлов другого узла
/// @param Node Узел, в который добавляем
/// @param NodeWithChildren Узел, чьи дочерние узлы добавляем
void AddChildrenFromNode(NodeDescription* Node, NodeDescription* NodeWithChildren){
    
    // Увеличиваем размер массива дочерних узлов на количество детей узла, чьи дочерние узлы добавляем
    Node->Children=(NodeDescription**)realloc(Node->Children, (Node->NumberOfChildren+NodeWithChildren->NumberOfChildren)*sizeof(NodeDescription*));
    // Добавляем все новые дочерние узлы 
    for(int i=0; i< NodeWithChildren->NumberOfChildren; i++){
        Node->Children[Node->NumberOfChildren+i]=NodeWithChildren->Children[i];
        // Очищаем детей узла, чьи дочерние узлы добавляем (потому что этот узел нам уже не нужен, его нужно полность очистить)
        NodeWithChildren->Children[i]=NULL;
    }
    // Увеличиваем число дочерних узлов на количество детей узла, чьи дочерние узлы добавляем
    Node->NumberOfChildren += NodeWithChildren->NumberOfChildren;
    // Освобождаем весь массив детей
    free(NodeWithChildren->Children);
    // Освобождаем весь узел
    free(NodeWithChildren);
}
//----------------------------------------------------------------
/// @brief Рекурсивное удаление всего дерева
/// @param Node Узел, с которого начинается удаление
/// @param depth Глубина рекурсии
void DelNode(NodeDescription * Node, int depth){
    int next_depth = depth;
    if(Node->NumberOfChildren>0){
        next_depth++;
        // Доходим до самого последнего узла дерева
        for(int i=0;i< Node->NumberOfChildren;i++){
            DelNode(Node->Children[i], next_depth);
        }
    }
    // Чистим Идентификатор
    free(Node->IDENTIFIER_Char);
    // Чистим Число
    free(Node->ILIT_Char);
    // Чистим массив дочерних узлов
    for(int i=0; i<Node->NumberOfChildren; i++){
        free(Node->Children[i]);
    }
    free(Node->Children);
    // Чистим самый первый узел
    if(depth==0){
        free(Node);
    }    
}
//----------------------------------------------------------------
/// @brief Рекурсивный вывод дерева
/// @param Node Узел, с которого начинается обход дерева
/// @param depth Глубина рекурсии
/// @param LastChild Флаг, указывающий на количество осмотренных последних детей узлов
void PrintNode(NodeDescription* Node, int depth, int LastChild){
    // Вывод данных об узле
    if(Node->IDENTIFIER_Char!=NULL){
        printf("<%s, \"%s\">\n", NodeType_String[Node->Type], Node->IDENTIFIER_Char);
    }
    else if(Node->ILIT_Char!=NULL){
        printf("<%s, %s>\n", NodeType_String[Node->Type], Node->ILIT_Char);
    }
    else{
        printf("<%s>\n", NodeType_String[Node->Type]);
    }
    // Вывод "ветвей" и обход дочерних узлов
    int next_depth = depth;
    if(Node->NumberOfChildren>0){
        next_depth++;
        for(int i=0; i< Node->NumberOfChildren;i++){
            for(int j=0; j<LastChild;j++){
                printf("  ");
            }
            for(int j=0; j<depth-LastChild;j++){
                printf("| ");
            }
            if(i==Node->NumberOfChildren-1){
                LastChild++;
            }
            printf("|-");
            PrintNode(Node->Children[i], next_depth, LastChild);
        }
    }
}