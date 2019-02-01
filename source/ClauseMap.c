//
// Created by Kingqi on 2019/1/29.
//

#include "../head/ClauseMap.h"
void showClauseMap(ClauseMap *map)
{
    printf("clas:%d\teles:%d\n",map->Count.clas,map->Count.eles);
    showClauseList(map->head);
}
void freeClauseMap(ClauseMap *map)
{
    freeClauseList(map->head);
    free(map);
}
int hasSingleton(ClauseMap *map)
{
    ClauseList *list = map->head;
    Clause *clause = NULL;
    while (list!=NULL)
    {
        clause = list->clause;
        //如果是已经满足的句子直接跳过
        if (clause->status != Success)
        //如果是则表明为singletong 否则不是
            if (clause->singleton!=0)
                return clause->singleton;
        list=list->next;
    }
    return 0;
}
int watchMap(ClauseMap *map)
{
    ClauseList *list = map->head;
    int i = 0;
    while (list!=NULL)
    {
        switch (list->clause->status)
        {
            case Success:
                i++;
                break;
            case Fail:
                return -1;
            default:
                break;
        }
        list = list->next;
    }
    if (i == map->Count.clas)
        return 1;
    else
        return 0;
}