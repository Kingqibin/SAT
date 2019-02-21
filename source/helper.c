//
// Created by kingqi on 19-2-19.
//

#include <string.h>
#include <stdlib.h>
#include "../head/helper.h"
char *strrev(char *q, char *buffer)
{
    int i;
    int n;
    n = (int) strlen(q);
    for( i = 0;i < n;i++)
    {
        buffer[n-1-i]=*q++;
    }
    buffer[n]='\0';
    return buffer;
}

char * itoa(int n)
{
    int p=0 ;
    char a[8]={'\0'};
    do
    {
        a[p] =(char)((n%10)+'0');
        n = n / 10 ;
        p++;
    }while (n);
    char *buffer = (char *)malloc(9);
    for (int i = 0; i < 9; ++i) {
        *(buffer+i) = '\0';
    }
    return strrev(a,buffer);
}
int readSudoNum(char *filePath)
{
    int m = 0;
    FILE *file = fopen(filePath,"r");
    fscanf(file,"%d",&m);
    fclose(file);
    return m;
}
char *getSudoFileName(int n)
{
    char *string = "/home/kingqi/work/CLanguage/SAT_2/Sudoku/sudo";
    char *t = itoa(n);
    char *buffer = (char *)malloc(strlen(string)+strlen(t)+1);
    strcpy(buffer,string);
    strcat(buffer,t);
    buffer[strlen(buffer)]='\0';
    free(t);
    return buffer;
}