//
// Created by Kingqi on 2019/1/30.
//

#ifndef SAT_2_MYSTACK_H
#define SAT_2_MYSTACK_H

#include "LiteralList.h"

struct myStack{
    int literal;
    int backPoint;
    struct myStack *next;
};
typedef struct myStack MyStack;
MyStack *push (MyStack *,int ,int backPoint);
MyStack *pop  (MyStack *,int *);
#endif //SAT_2_MYSTACK_H
