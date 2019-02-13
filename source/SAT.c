//
// Created by Kingqi on 2019/1/29.
//

#include "../head/SAT.h"
#define MAX_CHAR 1024*1024
//#define DEBUG
ClauseMap *createClauseMap(char *filename);
int checkResult(char *input, char *output);
void add_clauselist_to_literal(Literal *array,ClauseMap map);
char *replaceCNF(char *fileName);
char *SAT(char *name)
{
    ClauseMap *myMap = createClauseMap(name);
    Literal *array = createLiteralArray(myMap->Count.eles);
    add_clauselist_to_literal(array,*myMap);
    clock_t  s , f ;
    s = clock();
    Result r = DPLL(myMap,array);
    f = clock();
    char *outputFile = replaceCNF(name);
    freopen(outputFile,"w",stdout);

    printf("s ");
    if (r== Sat)
    {
        printf("1\nv ");
        int size = array->value;
        for (int i = 1; i <= size; ++i) {
            if ((array+i)->value != False)
                printf("%d ",i);
            else
                printf("-%d ",i);
        }
    }
    else
        printf("0\nv ");

    printf("\nt %ld\n",f-s);
    freopen("CON","w",stdout);
#ifdef DEBUG
    int size = array->value;
    for (int i = 1; i < size; ++i) {
        printf("%d\t%d\t%d\t",i,(array+i)->value,(array-i)->value);
        if (((array+i)->value) == -((array-i)->value))
            printf("Y");
        else
            printf("N");
        printf("\n");
    }

    printf("\n");
#endif
    freeLiteralArray(array);
    freeClauseMap(myMap);
    return outputFile;
}

char *replaceCNF(char *fileName)
{
    char *new  = (char *)malloc(strlen(fileName)+1);
    new  = strcpy(new,fileName);
    char *p = strstr(new,".cnf");
    *(p+1) = 'r';
    *(p+2) = 'e';
    *(p+3) = 's';
    return new;
}
void add_clauselist_to_literal(Literal *array,ClauseMap map)
{
    if (map.head==NULL)
        return;
    ClauseList *list = map.head;
    while (list!=NULL)
    {
        Clause *clause = list->clause;
        LiteralList *literalList = clause->myList;
        while (literalList!=NULL)
        {
            int n = literalList->literal;
            (array+n)->myList = createLiteralClauseList(array+n,clause);
            (array+n)->clause_nums ++;
            literalList = literalList->next;
        }
        list=list->next;
    }
}
ClauseMap *createClauseMap(char *filename)
{
    FILE *file = fopen(filename,"r");
    if (file==NULL)
    {
        printf("file not exist, please check it!\n");
        return NULL;
    }
    char str[MAX_CHAR];
    ClauseMap *map = (ClauseMap *)malloc(sizeof(ClauseMap));
    if (map == NULL)
    {
        printf("create total map error!\n");
        return NULL;
    }
    map->head = NULL;
    int k = 1;
    while (!feof(file))
    {
        fgets(str, MAX_CHAR, file);
        //略过注释
        if (*str == 'c')
            continue;
            //提取p开头行的信息
        else  if (*str == 'p')
        {
            int i = 0;
            char *token = strtok(str, " ");
            while (token != NULL)
            {
                if (i == 2)
                    (map->Count).eles = atoi(token);
                else if (i == 3)
                    (map->Count).clas = atoi(token);
                token = strtok(NULL, " ");
                i++;
            }
        } else
        {
            Clause *myClause = createClause(k,str);
            k++;
            map->head = createClauseList(map->head,myClause);
        }
    }
    return map;
}
#undef DEBUG
