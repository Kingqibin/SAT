#include <stdio.h>
#include <stdlib.h>
#include "../head/SAT.h"
#include <time.h>
#define DEBUG

int main() {
    printf("------welcome to kingqi's program------\n\n");
    printf("Please enter number to choose function:\n");
    printf("1 --- SAT \n");
    printf("2 --- Sudoku\n");
#ifdef DEBUG
    printf("3 --- test\n");
    int n = 1;
#endif // DEBUG
    printf("0 --- exit\n\n\n");
#ifndef DEBUG
    int n ;
    scanf("%d",&n);
#endif
    switch (n)
    {
        case 0:
            exit(0);
        case 1:
            SAT("");
            break;
        case 2:
            break;
        default:
            printf("error input,exit\n");
            break;
    }
    return 0;
}

#undef DEBUG