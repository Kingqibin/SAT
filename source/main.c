#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../head/SAT.h"
#include <time.h>
#include "../head/Sudoku.h"
#include "../head/helper.h"
#include "../head/CreateSudo.h"
#include "../head/game.h"
//#define DEBUG
void sat();
void sudo();
void readTime(char *file);
int main() {
    int a ;
    do
    {
        system("clear");
        printf("欢迎进入我的程序\n\n");
        printf("请选择将要执行的模块\n");
        printf("1 --- SAT模块 \n");
        printf("2 --- Sudoku模块\n");
#ifdef DEBUG
        printf("3 --- test\n");
        int n = 3;
#endif // DEBUG
        printf("0 --- 退出程序\n\n\n");
#ifndef DEBUG
        printf("请输入【0 1 2】:   ");
        int n ;
        scanf("%d",&n);

#endif
        switch (n)
        {
            case 0:
                exit(0);
            case 1:
                sat();
                break;
            case 2:
                sudo();
                break;
            case 3:
                game("/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudo3");
                break;
            default:
                printf("错误输入！\n");
                break;
        }
        printf("是否继续执行？是：1/否：0\n");
        scanf("%d",&a);
        if (a!=1 && a!=0)
        {
            printf("错误输入！\n");
            break;
        }
    }while (a);
    return 0;
}
void sat()
{
    char *string[4] = {"/home/kingqi/work/CLanguage/SAT_2/input_file/base/function/sat-20.cnf",
                       "/home/kingqi/work/CLanguage/SAT_2/input_file/base/function/unsat-5cnf-30.cnf",
                       "/home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/ais10.cnf",
                       "/home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/sud00009.cnf"};
    int a;
    printf("选择将要执行的功能:\n");
    printf("1.测试功能样例\n");
    printf("2.测试性能样例\n");
    printf("3.对比优化\n");
    printf("请输入【1 2 3】:   ");
    scanf("%d",&a);
    int t;
    switch (a)
    {
        case 1:
            printf("正在求解sat-20.cnf...\n");
            SAT(string[0],1);
            printf("求解完成\n");
            printf("正在求解unsat-5cnf-30.cnf...\n");
            SAT(string[1],1);
            printf("求解完成\n");
            printf("是否输出结果\t是：1/否：0\n");
            scanf("%d",&t);
            if (t==1)
            {
                printf("sat-20.res:\n");
                system("cat /home/kingqi/work/CLanguage/SAT_2/input_file/base/function/sat-20.res");
                printf("\n");

                printf("unsat-5cnf-30.cnf:\n");
                system("cat /home/kingqi/work/CLanguage/SAT_2/input_file/base/function/unsat-5cnf-30.res");
                printf("\n");
            }
            break;
        case 2:
            printf("正在求解ais10.cnf...\n");
            SAT(string[2],1);
            printf("求解完成\n");
            printf("正在求解sud00009.cnf...\n");
            SAT(string[3],1);
            printf("求解完成\n");
            printf("是否输出结果\t是：1/否：0\n");
            scanf("%d",&t);
            if (t==1)
            {
                printf("ais10.res:\n");
                system("cat /home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/ais10.res");
                printf("\n");

                printf("sud00009.res:\n");
                system("cat /home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/sud00009.res");
                printf("\n");
            }
            break;
        case 3:
            printf("正在求解...\n");
            SAT("/home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/ais10_0.cnf",0);
            SAT("/home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/ais10_1.cnf",1);
            SAT("/home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/sud00009_0.cnf",0);
            SAT("/home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/sud00009_1.cnf",1);
            printf("文件\t\t优化前\t优化后（ms）\n");
            printf("ais10.cnf\t");
            readTime("/home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/ais10_0.res");
            printf("\t");
            readTime("/home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/ais10_1.res");
            printf("\n");
            printf("sud00009.cnf\t");
            readTime("/home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/sud00009_0.res");
            printf("\t");
            readTime("/home/kingqi/work/CLanguage/SAT_2/input_file/base/performance/sud00009_1.res");
            printf("\n");
            break;
        default:
            printf("错误输入！默认退出！\n");
            break;
    }
}
void sudo()
{
    system("clear");
    int a;
    printf("1.读取已经存在的数独\n");
    printf("2.生成新的数独\n");
    printf("请输入【1 2】 ：  ");

    scanf("%d",&a);

    if (a == 1)
    {
        srand(time(0));
        int  m = readSudoNum("/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudoNum");
        int n = rand()%m + 1;
        char *fileName = getSudoFileName(n);
        printf("正在跳转中...\n");
        Sudoku(fileName);
        game(fileName);
        free(fileName);
    } else if (a == 2)
    {
        printf("生成新的数独中...\n");
        char *name = createSudo();
        printf("生成结束...\n正在跳转中...\n");
        Sudoku(name);
        game(name);
        free(name);
    } else
    {
        printf("输入错误!\n");
    }
}

void readTime(char *fileName)
{
    char str[1024];
    FILE *file = fopen(fileName,"r");
    while (!feof(file))
    {
        fscanf(file,"%s",str);
        if (*str == 't')
        {
            break;
        }
    }
    fscanf(file,"%s",str);
    printf("%s",str);
    fclose(file);
}
#undef DEBUG