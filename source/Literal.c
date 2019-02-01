//
// Created by Kingqi on 2019/1/29.
//

#include "../head/Literal.h"
ClauseList *createLiteralClauseList(Literal *literal,Clause *clause)
{
    ClauseList *head = literal->myList;
    return createClauseList(head,clause);
}
Literal *createLiteralArray(int size)
{
    Literal *array = (Literal *)calloc((size_t)(2*size + 1) , sizeof(Literal));
    array += size;
    array->value = size;
    array->num = 0;
    array->myList=NULL;
    for (int i = 1; i <= size; ++i) {
        (array+i)->myList = NULL;
        (array+i)->value = Not;
        (array+i)->num=i;
        (array-i)->myList = NULL;
        (array-i)->value = Not;
        (array-i)->num = -i;
        (array+i)->clause_nums = 0;
        (array-i)->clause_nums = 0;
    }
    return array;
}
void showLiteral(Literal *literal)
{
    printf("num:%d\t",literal->num);
    switch (literal->value)
    {
        case Not:
            printf("Not\t");
            break;
        case True:
            printf("True\t");
            break;
        case False:
            printf("False\t");
            break;
    }
    printf("clause num is:%d\n",literal->clause_nums);
    printf("clause as fellows:\n");
    showClauseList(literal->myList);
    printf("\n");
}
void showLiteralArray(Literal *array)
{
    int size = array->value;
    for (int i = 1; i <= size; ++i) {
        showLiteral(array+i);
    }
    for (int i = 0; i <= size; ++i) {
        showLiteral(array-i);
    }
}
void freeLiteralClauseList(Literal *literal)
{
    ClauseList *list = literal->myList;
    ClauseList *save = list;
    while (list!=NULL)
    {
        list=list->next;
        free(save);
        save = list;
    }
}
void freeLiteralArray(Literal *array)
{
    int size = array->value;
    for (int i = 0; i <= size; ++i) {
        freeLiteralClauseList(array+i);
    }
    for (int i = 1; i <= size; ++i) {
        freeLiteralClauseList(array-i);
    }
    array-=size;
    free(array);
}
int satLiteral(Literal *literal)
{
    literal->value = True ;
    return satClauseList(literal->myList,literal->num);
}
int backSatLiteral(Literal *literal)
{
    literal->value = Not;
    return backSatClauseList(literal->myList,literal->num);
}
void unSatLiteral(Literal *literal)
{
    literal->value = False;
    unSatClauseList(literal->myList,literal->num);
}
void backUnSatLiteral(Literal *literal)
{
    literal->value = Not;
    backUnSatClauseList(literal->myList,literal->num);
}
int countClause(Literal *literal)
{
    int i = 0 ;
    ClauseList *clauseList = literal->myList ;
    while (clauseList!=NULL)
    {
        if(clauseList->clause->status != Success)
            i++;
        clauseList=clauseList->next;
    }
    return i;
}