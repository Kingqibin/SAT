//
// Created by Kingqi on 2019/1/29.
//

#include <string.h>
#include "../head/Clause.h"
int hasAppeared(LiteralList *list,int n);
Clause *createClause(int index,char *string)
{
    Clause *my = (Clause *)malloc(sizeof(Clause));
    my->index = index;
    char *token = strtok(string," ");
    LiteralList *head = NULL;
    int i=0;//计数变量
    //创建LiteralList
    while (token!=NULL)
    {
        int n = atoi(token);
        if (n==0)
            break;
        //预处理，如果出现过则跳过
        if (!hasAppeared(head,n))
        {
            head = createLiteralList(head,n);
            i++;
        }
        token = strtok(NULL, " ");
    }

    my->myList = head;
    my->status = NoValue;
    my->singleton = 0;
    my->count=i;
    if (i == 1)
    {
        my->singleton  = my->myList->literal;
    }
    return my;
}
void showClause(Clause *clause)
{
    printf("clause index:%d\tstatus:",clause->index);
    switch (clause->status)
    {
        case Success:
            printf("S");
            break;
        case Fail:
            printf("F");
            break;
        case NoValue:
            printf("N");
    }
    printf("\tliterals :");
    showLiteralList(clause->myList);
    printf("\n");
}
void freeClause(Clause *clause)
{
    freeLiteralList(clause->myList);
    free(clause);
}
int hasAppeared(LiteralList *list,int n)
{
    while (list!=NULL)
    {
        if (list->literal == n)
            return 1;
        list = list->next;
    }
    return 0;
}
void satClause(Clause *clause,int literal)
{
    //进入这里clause的状态不可能是fail
    if(clause->status==Fail)
        printf("something may error in SatClause of literal %dits status is %d\n",literal,clause->status);
    LiteralList *list = clause->myList;
    while (list!=NULL)
    {
        if (list->literal == literal)
        {
            list->value = 1;
            break;
        }
        list = list->next;
    }
    clause->status = Success;
    clause->singleton = 0;
}
void backSatClause(Clause *clause,int literal)
{
    //进入这里的clause的状态只能是Success的
    if(clause->status!=Success)
        printf("something may error in backSatClause of literal %dits status is %d\n",literal,clause->status);

    LiteralList *list = clause->myList;

    while (list!=NULL)
    {
        if (list->literal == literal)
        {
            list->value = 0;
            break;
        }
        list = list->next;
    }

    int i = 0,s = 0,save = 0;
    LiteralList *head =clause->myList;

    while (head!=NULL)
    {
        switch (head->value)
        {
            case 0:
                s++;
                save = head->literal;
                break;
            case 1:
                i++;
                break;
            default:
                break;
        }
        head = head->next;
    }

    if (i == 0)
    {
        clause->status = NoValue;
        if (s==1)
            clause->singleton = save;
        else
            clause->singleton = 0;
    }
    else
        clause->status = Success;

}
void unSatClause(Clause *clause,int literal)
{
    //进入此处的clause的status只能是NoValue
    if((clause->status)!= NoValue)
        printf("something may error in unSatClause of literal %dits status is %d\n",literal,clause->status);
    LiteralList *list = clause->myList;
    while (list!=NULL)
    {
        if (list->literal == literal)
        {
            list->value = -1;
            break;
        }
        list = list->next;
    }

    LiteralList *head = clause->myList;

    int i = 0 , s = 0, save =0;

    while (head!=NULL)
    {
        switch (head->value)
        {
            case -1:
                i++;
                break;
            case 0:
                s++;
                save = head->literal;
                break;
            default:
                break;
        }
        head=head->next;
    }

    if (i==clause->count)
    {
        clause->status = Fail;
    }

    if (s==1)
    {
        clause->singleton = save;
    } else
        clause->singleton = 0;
}
void backUnSatClause(Clause *clause, int literal)
{
    //进入这里的语句的状态不可能是Success
    if (clause->status == Success)
        printf("something may error in backUnSatClause of literal %dits status is %d\n",literal,clause->status);
    LiteralList *list = clause->myList;

    while (list!=NULL)
    {
        if (list->literal == literal )
        {
            list->value = 0;
            if (clause->status  == Fail)
                clause->status= NoValue;
            break;
        }
        list = list->next;
    }
    LiteralList *head = clause->myList;
    int s = 0,save = 0;
    while (head!=NULL)
    {
        switch (head->value)
        {
            case 0:
                s++;
                save = head->literal;
                break;
            default:
                break;
        }
        head = head->next;
    }

    if (s == 1)
        clause->singleton = save;
    else
        clause->singleton = 0;
}