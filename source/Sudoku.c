//
// Created by Kingqi on 2019/2/13.
//

#include "../head/Sudoku.h"
void parseProblem(char *fileName, char *output);
char *getOutputName(char *fileName);
void write_1(char *);
void write_2(char *);
void write_3(char *);
void write_4(char *);
void show(char *);
void Sudoku(char *fileName)
{
    char *outputName = getOutputName(fileName);
    parseProblem(fileName,outputName);
    //each cell has a value
    write_1(outputName);
    //each row has one value
    write_2(outputName);
    //each col has one value
    write_3(outputName);
    //each 3*3 box has one value
    write_4(outputName);
    //求解：
    char *solution =  SAT(outputName);
    show(solution);
}
void show(char *solution)
{
    FILE *file = fopen(solution,"r");
    if (file==NULL)
    {
        printf("error!\n");
        return;
    }
    char c;
    while (!feof(file))
    {
        fscanf(file,"%c",&c);
        if (c == 'v')
        {
            fscanf(file,"%c",&c);
            break;
        }
    }
    int n;
    printf("----------------------------------------\n");
    for (int i = 0; i < 9; ++i) {
        printf("|");
        for (int j = 0; j < 9; ++j) {
            for (int k = 0; k < 9; ++k) {
                fscanf(file,"%d",&n);
                if (n>0)
                {
                    printf("%3d ",n-i*81-j*9);
                }
            }
            if ((j+1)%3 == 0)
            {
                printf("|");
            }
        }
        printf("\n");
        if ((i+1)%3 == 0)
        {
            printf("----------------------------------------\n");
        }
    }
    fclose(file);
}

void write_4(char *outputName)
{
    FILE *output = fopen(outputName,"a");
    int first , second;
    for (int k = 1; k < 10; ++k) {
        for (int a = 0; a < 3; ++a) {
            for (int b = 0; b < 3; ++b) {
                for (int u = 1; u < 4; ++u) {
                    for (int v = 1; v < 3; ++v) {
                        for (int w = v+1; w < 4; ++w) {
                           first = 81*((3*a+u)-1) + 9*((3*b+v)-1) + (k-1) +1;
                           second = 81*((3*a+u)-1) + 9*((3*b+w) -1) + (k-1) + 1;
                           fprintf(output,"-%d -%d 0\n",first,second);
                        }
                    }
                }
            }
        }
    }

    for (int k = 1; k < 10; ++k) {
        for (int a = 0; a < 3; ++a) {
            for (int b = 0; b < 3; ++b) {
                for (int u = 1; u < 3; ++u) {
                    for (int v = 1; v < 4; ++v) {
                        for (int w = u+1; w < 4; ++w) {
                            for (int t = 1; t < 4; ++t) {
                                first = 81*((3*a+u)-1) + 9*((3*b+v)-1) + (k-1) +1;
                                second = 81*((3*a+w)-1) + 9*((3*b+t) -1) + (k-1) + 1;
                                fprintf(output,"-%d -%d 0\n",first,second);
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(output);
}
void write_3(char *outputName)
{
    FILE *output = fopen(outputName,"a");
    int first,second;
    for (int j = 1; j < 10; ++j) {
        for (int k = 1; k < 10; ++k) {
            for (int i = 1; i < 9; ++i) {
                for (int l = i+1; l < 10; ++l) {
                    first = 81*(i-1) + 9*(j-1) + (k-1) + 1;
                    second = 81*(l-1) + 9*(j-1) + (k-1) +1;
                    fprintf(output,"-%d -%d 0\n",first,second);
                }
            }
        }
    }
    fclose(output);
}
void write_2(char *outputName)
{
    FILE *output = fopen(outputName,"a");
    int first;
    int second;
    for (int i = 1; i < 10; ++i) {
        for (int k = 1; k < 10; ++k) {
            for (int j = 1; j < 9;j++){
                for (int l = j+1; l < 10; ++l) {
                    first = 81*(i-1) + 9*(j-1) + (k-1) + 1;
                    second = 81*(i-1) + 9*(l-1) + (k-1) + 1;
                    fprintf(output,"-%d -%d 0\n",first,second);
                }
            }
        }
    }
    fclose(output);
}
void write_1(char *outputName)
{
    FILE *output = fopen(outputName,"a");
    for (int i = 0; i < 81; ++i) {
        for (int j = 1; j <= 9; ++j) {
            fprintf(output,"%d ",i*9+j);
        }
        fprintf(output,"0\n");
    }
    fclose(output);
}
void parseProblem(char *fileName, char *outputName)
{
    FILE *input = fopen(fileName,"r");
    FILE *output = fopen(outputName,"w");
    if(input==NULL)
    {
        printf("file not exist,please check it\n");
        return;
    }
    int c = 0,t = 0 ;
    char n;
    int array[81]={0};
    while (!feof(input))
    {
        fscanf(input,"%c",&n);
        if (n=='\n' || n=='\r')
            continue;
        if (n != '0')
        {
            array[c] = n-48+t;
            c++;
        }
        t+=9;
    }
    c--;//除去最后的一个文件尾
    fprintf(output,"p cnf 729 %d\n",8829+c);
    for (int i = 0; i < c; ++i) {
        fprintf(output,"%d 0\n",array[i]);
    }
    fclose(input);
    fclose(output);
}
char *getOutputName(char *fileName)
{
    char *outputName = (char *)malloc(strlen(fileName)+1);
    outputName = strcpy(outputName,fileName);
    strcat(outputName,".cnf");
    return outputName;
}