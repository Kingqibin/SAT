//
// Created by Kingqi on 2019/1/29.
//

#include "../head/Literal.h"
void updateLiteralClauseList(Literal *literal, Clause *clause)
{
    if (literal->head ==NULL)
    {
        literal->head = createClauseList(NULL,clause);
        literal->tail = literal->head;
    } else
    {
        literal->tail = insertClauseList(literal->tail,clause);
    }
}
Literal *createLiteralArray(int size)
{
    Literal *array = (Literal *)malloc((2*size+1) * sizeof(Literal));
    if (array==NULL)
    {
        printf("memory error!\n");
        return NULL;
    }
    array += size;
    //中间结点保存array的大小
    array->value = size;
    array->num = 0;
    array->head=NULL;
    for (int i = 1; i <= size; ++i) {
        (array+i)->head = NULL;
        (array+i)->value = Not;
        (array+i)->num=i;
        (array+i)->clause_nums = 0;

        (array-i)->head = NULL;
        (array-i)->value = Not;
        (array-i)->num = -i;
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
    showClauseList(literal->head);
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
    ClauseList *list = literal->head;
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
    return satClauseList(literal->head,literal->num);
}
int backSatLiteral(Literal *literal)
{
    literal->value = Not;
    return backSatClauseList(literal->head,literal->num);
}
void unSatLiteral(Literal *literal)
{
    literal->value = False;
    unSatClauseList(literal->head,literal->num);
}
void backUnSatLiteral(Literal *literal)
{
    literal->value = Not;
    backUnSatClauseList(literal->head,literal->num);
}
int countClause(Literal *literal)
{
    int i = 0 ;
    ClauseList *clauseList = literal->head ;
    while (clauseList!=NULL)
    {
        if(clauseList->clause->status != Success)
            i++;
        clauseList=clauseList->next;
    }
    return i;
}