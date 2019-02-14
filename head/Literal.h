//
// Created by Kingqi on 2019/1/29.
//


#ifndef SAT_2_LITERAL_H
#define SAT_2_LITERAL_H

#include "ClauseList.h"

typedef enum {True=1,False=-1,Not=0} Value;
struct literal{
    int num ; //当num为0时  Value存储数组长度的一半 n；
    Value value;
    ClauseList *head;
    ClauseList *tail;
    int clause_nums;
};
typedef struct literal Literal;
void updateLiteralClauseList(Literal *literal, Clause *clause);
Literal *createLiteralArray(int size);
void showLiteral(Literal *literal);
void showLiteralArray(Literal *array);
void freeLiteralClauseList(Literal *);
void freeLiteralArray(Literal *array);
int satLiteral(Literal *literal);
int backSatLiteral(Literal *literal);
void unSatLiteral(Literal *literal);
void backUnSatLiteral(Literal *literal);
int countClause(Literal *literal);
#endif //SAT_2_LITERAL_H

