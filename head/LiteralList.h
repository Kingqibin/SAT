//
// Created by Kingqi on 2019/1/29.
//

#ifndef SAT_2_LITERALLIST_H
#define SAT_2_LITERALLIST_H

#include <stdlib.h>
#include <stdio.h>
struct literal_list {
    int literal;
    int value;
    struct literal_list *next;
};
typedef struct literal_list LiteralList;
LiteralList *createLiteralList(LiteralList *head,int n);
void showLiteralList(LiteralList *);
void freeLiteralList(LiteralList *literalList);
#endif //SAT_2_LITERALLIST_H
