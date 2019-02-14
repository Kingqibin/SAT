//
// Created by Kingqi on 2019/1/29.
//

#include "../head/ClauseList.h"
ClauseList *createClauseList(ClauseList *head,Clause *new)
{
    head = (ClauseList *) malloc(sizeof(ClauseList));
    if (head==NULL)
    {
        printf("memory error!\n");
        return NULL;
    }
    head->clause = new;
    head->next = NULL;
    return head;
}
ClauseList *insertClauseList(ClauseList *tail,Clause *clause)
{
    ClauseList *new = (ClauseList *)malloc(sizeof(ClauseList));
    if (new == NULL)
    {
        printf("memory error!\n");
        return  NULL;
    }
    new->next = NULL;
    new->clause = clause;
    tail->next = new;
    tail = new;
    return tail;
}
void showClauseList(ClauseList *clauseList)
{
    while (clauseList!=NULL)
    {
        showClause(clauseList->clause);
        clauseList=clauseList->next;
    }
}
void freeClauseList(ClauseList *clauseList)
{
    ClauseList *save = clauseList;
    while (clauseList!=NULL)
    {
        clauseList=clauseList->next;
        freeClause(save->clause);
        free(save);
        save = clauseList;
    }
}
int satClauseList(ClauseList *list,int literal)
{
    int i = 0;
    while (list!=NULL)
    {
        satClause(list->clause,literal);
        list = list->next;
        i++;
    }
    return i;
}

int backSatClauseList(ClauseList *list,int literal)
{
    int i = 0;
    while (list!=NULL)
    {
        backSatClause(list->clause,literal);
        list = list->next;
        i++;
    }
    return i;
}
void unSatClauseList(ClauseList *list,int literal)
{
    while (list!=NULL)
    {
        if (list->clause->status != Success)
        {
            unSatClause(list->clause,literal);
        }
        list=list->next;
    }
}
void backUnSatClauseList(ClauseList *list,int literal)
{
    while (list!=NULL)
    {
        if (list->clause->status != Success)
        {
            backUnSatClause(list->clause,literal);
        }
        list = list->next;
    }
}