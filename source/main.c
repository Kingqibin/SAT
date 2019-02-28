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
int readTime(char *file);
void readResFile(char *file);
int main() {
    char a[2] ;
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
        char n[3] ;
        scanf("%s",n);

#endif
        if (strcmp(n,"0")==0)
        {
            exit(0);
        } else if (strcmp(n,"1")==0)
        {
            sat();
        } else if (strcmp(n,"2")==0)
        {
            sudo();
        } else if (strcmp(n,"3")==0)
        {
            game("./Sudoku/sudo3");
        } else
        {
            printf("错误输入！\n");
        }
        printf("是否继续执行？是：1/否：0\n");
        scanf("%s",a);
        if (strcmp(a,"1")!=0 && strcmp(a,"0")!=0)
        {
            printf("错误输入！\n");
            break;
        }
    }while (strcmp(a,"1")==0);
    return 0;
}
void sat()
{
    char *string[4] = {"./input_file/base/function/sat-20.cnf",
                       "./input_file/base/function/unsat-5cnf-30.cnf",
                       "./input_file/base/performance/ais10.cnf",
                       "./input_file/base/performance/sud00009.cnf"};
    char a[3];
    int b;
    char path[1024];
    printf("选择将要执行的功能:\n");
    printf("1.测试功能样例\n");
    printf("2.测试性能样例\n");
    printf("3.对比优化\n");
    printf("4.测试其他样例\n");
    printf("5.求解文件\n");
    printf("请输入【1 2 3 4 5】:   ");
    scanf("%s",a);
    if (strcmp(a,"1")==0)
    {
        printf("正在求解sat-20.cnf...\n");
        SAT(string[0],1);
        printf("求解完成\n");
        printf("正在求解unsat-5cnf-30.cnf...\n");
        SAT(string[1],1);
        printf("求解完成\n");
        printf("是否输出结果\t是：1/否：0\n");
        char t[3];
        scanf("%s",t);
        if (strcmp(t,"1")==0)
        {
            printf("sat-20.res:\n");
            readResFile("./input_file/base/function/sat-20.res");
            printf("\n");

            printf("unsat-5cnf-30.cnf:\n");
            readResFile("./input_file/base/function/unsat-5cnf-30.res");
            printf("\n");
        }
    } else if (strcmp(a,"2")==0)
    {
        printf("正在求解ais10.cnf...\n");
        SAT(string[2],1);
        printf("求解完成\n");
        printf("正在求解sud00009.cnf...\n");
        SAT(string[3],1);
        printf("求解完成\n");
        printf("是否输出结果\t是：1/否：0\n");
        char t[3];
        scanf("%s",t);
        if (strcmp(t,"1") == 0)
        {
            printf("ais10.res:\n");
            readResFile("./input_file/base/performance/ais10.res");
            printf("\n");

            printf("sud00009.res:\n");
            readResFile("./input_file/base/performance/sud00009.res");
            printf("\n");
        }

    } else if (strcmp(a,"3")==0)
    {
        printf("正在求解...\n");
        remove("./input_file/base/performance/ais10.res");
        char *out = SAT("./input_file/base/performance/ais10.cnf",0);
        int a1 = readTime(out);
        remove(out);
        free(out);
        out = SAT("./input_file/base/performance/ais10.cnf",1);
        int a2 = readTime(out);
        remove(out);
        free(out);

        remove("./input_file/base/performance/sud00009.res");
        out = SAT("./input_file/base/performance/sud00009.cnf",0);
        int b1 = readTime(out);
        remove(out);
        free(out);
        out = SAT("./input_file/base/performance/sud00009.cnf",1);
        int b2 = readTime(out);
        remove(out);
        free(out);

        printf("文件\t\t优化前\t优化后（ms）\n");
        printf("ais10.cnf\t");
        printf("%d\t%d\n",a1,a2);
        printf("sud00009.cnf\t");
        printf("%d\t%d\n",b1,b2);
    } else if (strcmp(a,"4")==0)
    {
        printf("请输入文件路径\n");
        scanf("%s",path);
        printf("请输入测试次数\n");
        scanf("%d",&b);
        printf("优化前\t优化后（ms）\n");
        while(b--){
            char *out1 = SAT(path,0);
            int slow = readTime(out1);
            char *out2 = SAT(path,1);
            int fast = readTime(out2);
            printf("%d\t",slow);
            printf("%d\n",fast);
            free(out1);
            free(out2);

        }
    } else if (strcmp(a,"5")==0)
    {
        printf("请输入文件路径\n");
        scanf("%s",path);
        char *out1 = SAT(path,3);
        printf("求解完成\n");
        printf("是否输出结果\t是：1/否：0\n");
        char t[3];
        scanf("%s",t);
        if (strcmp(t,"1") == 0)
        {
            readResFile(out1);
        }
        free(out1);
    } else
    {
        printf("错误输入！默认退出！\n");
    }
}
void sudo()
{
    system("clear");
    char a[4];
    printf("1.读取已经存在的数独\n");
    printf("2.生成新的数独\n");
    printf("请输入【1 2】 ：  ");

    scanf("%s",a);

    if (strcmp(a,"1")==0)
    {
        srand(time(0));
        int  m = readSudoNum("./Sudoku/sudoNum");
        int n = rand()%m + 1;
        char *fileName = getSudoFileName(n);
        printf("正在跳转中...\n");
        Sudoku(fileName);
        game(fileName);
        free(fileName);
    } else if (strcmp(a,"2")==0)
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

int readTime(char *fileName)
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
    fclose(file);
    return atoi(str);
}
void readResFile(char *fileName)
{
    FILE *file = fopen(fileName,"r");
    char c;
    while (!feof(file))
    {
        fscanf(file,"%c",&c);
        printf("%c",c);
    }
    fclose(file);
}
#undef DEBUG