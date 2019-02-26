//
// Created by Kingqi on 2019/1/29.
//


#ifndef SAT_2_CLAUSELIST_H
#define SAT_2_CLAUSELIST_H

#include "Clause.h"
struct clause_list{
    Clause *clause;
    struct clause_list *next;
};
typedef struct clause_list ClauseList;
ClauseList *createClauseList(ClauseList *,Clause *);
ClauseList *insertClauseList(ClauseList *,Clause *);
void showClauseList(ClauseList *clauseList);
void freeClauseList(ClauseList *clauseList);
int satClauseList(ClauseList *list,int );
int backSatClauseList(ClauseList *list,int);
int unSatClauseList(ClauseList *list,int literal);
int backUnSatClauseList(ClauseList *list,int literal);
#endif //SAT_2_CLAUSELIST_H
