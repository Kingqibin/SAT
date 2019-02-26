//
// Created by kingqi on 19-2-21.
//

#include "../head/game.h"
void showSudoGame(int sudo[9][9]);
void parseSudo(char *fileName,int sudo[9][9]);
void parseResult(char *,int result[][9]);
int correct(int sudo[][9],int result[][9]);
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
    char n[10];
    int c =1,d=1;
    do
    {
        if (c)
        {
            showSudoGame(sudo);
        }
        if (d)
        {
            scanf("%s",n);
        }
        if (strcmp(n,"1") == 0)
        {
            printf("按照 x y z 的形式填写，x代表行数，y代表列数，z代表值\n");
            int x , y , z;
            scanf("%d %d %d",&x,&y,&z);

            if (x>10||x<1||y>10||y<1||z>10||z<1)
            {
                printf("填写失败,请重试\n");
                c = 0;
                d = 0;
            }
            else
            {
                sudo[x-1][y-1] = z;
                c = 1;
                d = 1;
            }

        } else if (strcmp(n,"2") == 0)
        {
            int b = 0;
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (sudo[i][j] == 0)
                        continue;
                    if (sudo[i][j]!=result[i][j]){
                        b++;
                    }
                }
            }
            if (b == 0)
            {
                printf("当前没有错误,请继续\n");
                c = 0;
                d = 1;
            } else
            {
                printf("存在%d处错误，建议退出\n",b);
                c = 0;
                d = 1;
            }

        } else if (strcmp(n,"0") == 0)
        {
            printf("已经结束游戏\n");
            return;
        }
    }while(!correct(sudo,result));
    printf("你小子可真他娘的诗歌人才!\n");
}
int correct(int sudo[][9],int result[][9])
{
    int b = 1;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (sudo[i][j] != result[i][j])
            {
                b = 0;
                return b;
            }
        }
    }
    return 1;
}
void showSudoGame(int sudo[9][9])
{
    system("clear");
    printf("%s\n","Sudo Game As Fellow:");
    printf("  + 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 +\n");
    printf("+ +---+---+---+---+---+---+---+---+---+\n");
    for (int i = 0; i < 9; ++i) {
        printf("%d |",i+1);
        for (int j = 0; j < 9; ++j) {
            if (sudo[i][j] != 0)
                printf(" %d |",sudo[i][j]);
            else
                printf("   |");
        }
        printf("\n");
        printf("+ +---+---+---+---+---+---+---+---+---+\n");
    }
    printf("\n1.填写数字\n"
           "2.提示当前结果是否正确\n"
           "0.结束游戏\n"
           "请输入[1,2,0]\n");
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
