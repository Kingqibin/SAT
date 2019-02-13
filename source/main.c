#include <stdio.h>
#include <stdlib.h>
#include "../head/SAT.h"
#include <time.h>
#include "../head/Sudoku.h"
//#define DEBUG

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
    char *string[4] = {"E:\\C\\SAT_2\\input_file\\base\\function\\sat-20.cnf",
                       "E:\\C\\SAT_2\\input_file\\base\\function\\unsat-5cnf-30.cnf",
                       "E:\\C\\SAT_2\\input_file\\base\\performance\\ais10.cnf",
                       "E:\\C\\SAT_2\\input_file\\base\\performance\\sud00009.cnf"};
#endif
    switch (n)
    {
        case 0:
            exit(0);
        case 1:
            for (int i = 0; i < 4; ++i) {
                SAT(string[i]);
                printf("solved %d/4\n",i+1);
            }
            printf("solved all\n");
            break;
        case 2:
            Sudoku("E:\\C\\SAT_2\\Sudoku\\sudo1");
            break;
        default:
            printf("error input,exit\n");
            break;
    }
    int c;
    printf("press any key to exit\n");
    scanf("%d",&c);
    return 0;
}

#undef DEBUG