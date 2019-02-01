//
// Created by Kingqi on 2019/1/30.
//

#include "../head/MyStack.h"
MyStack *push (MyStack *myStack,int literal,int backPoint)
{
    if (literal == 0)
        return  myStack;
    if (myStack==NULL)
    {
        myStack = (MyStack *)malloc(sizeof(MyStack));
        if (myStack == NULL)
        {
            printf("memory error!\n");
            return NULL;
        }
        myStack->literal = literal;
        myStack->backPoint = backPoint;
        myStack->next = NULL;
    } else
    {
        MyStack *new = (MyStack *)malloc(sizeof(MyStack));
        if (new == NULL)
        {
            printf("memory error!\n");
            return NULL;
        }
        new->next = myStack;
        new->literal = literal;
        new->backPoint = backPoint;
        myStack = new;
    }
    return  myStack;
}
MyStack *pop  (MyStack *myStack,int *literal)
{
    if (myStack == NULL)
    {
        *literal = 0;
        return  NULL;
    }
    else{
        MyStack *save = myStack;
        *literal = myStack->literal;
        myStack = myStack->next;
        free(save);
    }
    return myStack;
}