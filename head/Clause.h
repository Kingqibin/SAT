//
// Created by Kingqi on 2019/1/29.
//


#ifndef SAT_2_CLAUSE_H
#define SAT_2_CLAUSE_H

#include "LiteralList.h"
#include <stdlib.h>
typedef enum {Success = 0,Fail=1,NoValue=2} ClauseStatus;
struct clause {
    int index;
    int count;//保存总的元素个数    count-nowstep获得还没有进行赋值的元素个数
    int singleton;
    ClauseStatus status;
    LiteralList *myList;
};
typedef struct clause Clause;
Clause *createClause(int index, char *);
void showClause(Clause *);
void freeClause(Clause *);
void satClause(Clause *,int);
void backSatClause(Clause *clause,int);
int unSatClause(Clause *, int);
void backUnSatClause(Clause *, int);
#endif //SAT_2_CLAUSE_H