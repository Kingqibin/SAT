//
// Created by kingqi on 19-2-21.
//

#include "../head/game.h"
void showSudoGame(int sudo[9][9]);
void parseSudo(char *fileName,int sudo[9][9]);
void parseResult(char *,int result[][9]);
void game(char *fileName)
{
    system("clear");
    int sudo[9][9]={0};
    int result[9][9]={0};
    parseSudo(fileName,sudo);

    char *resultName = (char *)malloc(strlen(fileName)+4);
    strcpy(resultName,fileName);
    strcat(resultName,".res");

    parseResult(resultName,result);

    printf("sudo:\n");
    showSudoGame(sudo);
    printf("result:\n");
    showSudoGame(result);
}
void showSudoGame(int sudo[9][9])
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf("%d ",sudo[i][j]);
        }
        printf("\n");
    }
}
void parseSudo(char *fileName,int sudo[9][9])
{
    FILE *file = fopen(fileName,"r");
    if (file == NULL)
    {
        printf("error\n");
        return;
    }
    int c = 0;
    char n;
    int array[81]={0};
    while (!feof(file))
    {
        fscanf(file,"%c",&n);
        if (n=='\n' || n=='\r')
            continue;
        array[c] = n-'0';
        c++;
    }
    fclose(file);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            sudo[i][j] = array[i*9+j];
        }
    }
}
void parseResult(char *solution,int sudo[][9])
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
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            for (int k = 0; k < 9; ++k) {
                fscanf(file,"%d",&n);
                if (n>0)
                {
                    sudo[i][j] = n-i*81-j*9;
                }
            }
        }
    }
    fclose(file);
}
