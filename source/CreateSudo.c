//
// Created by kingqi on 19-2-19.
//

#include "../head/CreateSudo.h"
#define NUM_BOX 11
#define DEBUG
void pickBoxes(int []);
void showBoxes(int box[]);
char * makeFile(int sudo[9][9]);
int las_vegas(int [][9],int []);
void showSudo(int sudo[][9]);
void makeSudo(int sudo[][9], char *);
void initSudo(int sudo[][9]);
void dibble(int sudo[][9]);
int hasSingleRes(int sudo[9][9]);
void pickIJ(int *i,int *j,int sudo[][9]);
char *createSudo()
{
    int sudo[9][9]={0};
    int boxes[NUM_BOX*2];
    srand(time(0));
#ifndef DEBUG
    while(las_vegas(sudo,boxes)!=1);
#endif
#ifdef DEBUG
    makeSudo(sudo,"/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudo3.res");
    showSudo(sudo);
#endif
    dibble(sudo);
    //更新数目
    int m = readSudoNum("/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudoNum");
    FILE *file = fopen("/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudoNum","w");
    fprintf(file,"%d",m+1);
    fclose(file);

    return makeFile(sudo);
}
void dibble(int sudo[][9])
{
    int log[9][9] = {0};
    int i,j;
    int k = rand()%8+17;
    for (int c = 81; c >= k ; c--) {
        do
        {
            i = rand()%9;
            j = rand()%9;
        }while (sudo[i][j]==0 || log[i][j]!=0 );

        int save = sudo[i][j];
        sudo[i][j] = 0;
        if (hasSingleRes(sudo)==1)
        {
            sudo[i][j] = save;
            log[i][j] = -1;
        } else
        {
            log[i][j] = 1;
        }
    }
}

int hasSingleRes(int sudo[9][9])
{
    int i=0,j=0;
    pickIJ(&i,&j,sudo);
    int x = sudo[i][j];
    for (int k = 1; k <= 9; ++k) {
        if (k==x)
            continue;
        sudo[i][j] = k;
        FILE *file = fopen("/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudo_temp","w");
        for (int m = 0; m < 9; ++m) {
            for (int n = 0; n < 9; ++n) {
                fprintf(file,"%d",sudo[m][n]);
            }
            if (m!=8)
                fprintf(file,"\n");
        }
        fclose(file);

        int r = Sudoku("/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudo_temp");
        //删除临时文件
        remove("/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudo_temp");
        remove("/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudo_temp.cnf");
        remove("/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudo_temp.res");

        if (r==1)
        {
            sudo[i][j] = x;
            return 1;
        }
    }
    sudo[i][j] = x;
    return 0;
}
void pickIJ(int *i,int *j,int sudo[][9])
{
    do
    {
        *i = rand()%9;
        *j = rand()%9;
    }while (sudo[*i][*j]==0);
}
int las_vegas(int sudo[9][9],int box[9])
{
    pickBoxes(box);
    for (int i = 0; i < NUM_BOX*2; i+=2) {
        int m = box[i];
        int n = box[i+1];
        sudo[m][n] = rand()%9+1;
    }
    char *name = makeFile(sudo);
    int n = Sudoku(name);
    if (n == 1)
    {
        char *res = (char *)malloc(strlen(name)+4);
        strcpy(res,name);
        strcat(res,".res");
        makeSudo(sudo,res);
        free(res);
    }
    else
        initSudo(sudo);
    free(name);
    return n;
}
void makeSudo(int sudo[][9], char *res)
{
    FILE *file = fopen(res,"r");
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
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            for (int k = 0; k < 9; ++k) {
                fscanf(file,"%d",&n);
                if (n>0)
                    sudo[i][j] = n-i*81-j*9;
            }
        }
    }
    fclose(file);
}
void pickBoxes(int boxes[])
{
    for (int i = 0; i < NUM_BOX*2; i+=2) {
        boxes[i] = rand()%9;
        boxes[i+1] = rand()%9;
    }
}

char *makeFile(int sudo[][9])
{
#ifndef DEBUG
    int m = readSudoNum("/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudoNum");
#endif
#ifdef DEBUG
    int m = 2;
#endif
    char *buffer = getSudoFileName(m+1);

    FILE *file = fopen(buffer,"w");

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            fprintf(file,"%d",sudo[i][j]);
        }
        if (i!=8)
            fprintf(file,"\n");
    }
    fclose(file);
    return buffer;
}
void showSudo(int sudo[][9])
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf("%d",sudo[i][j]);
        }
        printf("\n");
    }

}
void showBoxes(int box[])
{
    for (int i = 0; i < NUM_BOX*2; i+=2) {
        printf("%d %d \n",box[i],box[i+1]);
    }
}
void initSudo(int sudo[][9])
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            sudo[i][j]=0;
        }
    }
}
#undef DEBUG