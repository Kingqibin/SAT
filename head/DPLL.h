//
// Created by Kingqi on 2019/1/29.
//

#ifndef SAT_2_DPLL_H
#define SAT_2_DPLL_H

#include "ClauseMap.h"
#include "Literal.h"
#include "MyStack.h"
#include <stdio.h>
typedef enum {Sat,UnSat} Result;
Result DPLL(ClauseMap *map,Literal *array,int );
#endif //SAT_2_DPLL_H
