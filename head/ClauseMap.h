//
// Created by Kingqi on 2019/1/29.
//

#ifndef SAT_2_CLAUSEMAP_H
#define SAT_2_CLAUSEMAP_H

#include "ClauseList.h"
struct count{
    int clas;
    int eles;
};
struct clauseMap{
    struct count Count;
    ClauseList *head;
    ClauseList *tail;
};
typedef struct clauseMap ClauseMap;
void showClauseMap(ClauseMap *map);
void freeClauseMap(ClauseMap *map);
int hasSingleton(ClauseMap *map);
int watchMap(ClauseMap *map);

#endif //SAT_2_CLAUSEMAP_H
