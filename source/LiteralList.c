//
// Created by Kingqi on 2019/1/29.
//

#include "../head/LiteralList.h"
LiteralList *createLiteralList(LiteralList *head,int n)
{
    if (head ==NULL)
    {
        head = (LiteralList *)malloc(sizeof(LiteralList));
        if (head==NULL)
        {
            printf("memory error!\n");
            return NULL;
        }
        head->literal = n;
        head ->next = NULL;
        head ->value = 0;
    } else{
        LiteralList *new = (LiteralList *)malloc(sizeof(LiteralList));
        if (new==NULL)
        {
            printf("memory error!\n");
            return NULL;
        }
        new->next = head;
        new->literal = n;
        new->value= 0 ;
        head = new;
    }
    return head;
}
void showLiteralList(LiteralList *list)
{
    while (list!=NULL)
    {
        printf("%d:%d\t",list->literal,list->value);
        list = list->next;
    }
}
void freeLiteralList(LiteralList *literalList)
{
    LiteralList *save = literalList;
    while (literalList!=NULL)
    {
        literalList = literalList->next;
        free(save);
        save = literalList;
    }
}
