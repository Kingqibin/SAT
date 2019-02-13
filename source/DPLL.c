//
// Created by Kingqi on 2019/1/29.
//

#include "../head/DPLL.h"
void simplify(int, Literal *array);
void backSimplify(int , Literal *array);
int back(MyStack **myStack,Literal *array);
MyStack * backToNextPoint(MyStack *myStack,Literal *array);
int pickLiteral(Literal *array);
//#define DEBUG
Result DPLL(ClauseMap *map,Literal *array)
{
    int singleton = 0;
    MyStack *myStack = NULL;
    int r = 0 , b = 0 ;
    while (1)
    {
        if (b==0)
        {
            //判断map中是否还有singleton的clause，如果存在则返回值，否则返回0
            singleton = hasSingleton(map);
            if (singleton!=0)
            {
                //存在则将singleton压栈
                myStack = push(myStack,singleton,0);
            } else{
                //不存在则选择一个元素
                singleton = pickLiteral(array);
                //如果singleton == 0 则说明所有的元素都已经被选择，则直接返回
                if (singleton == 0)
                {
                    return Sat;
                }
                //决策标记
                r++;
                //压栈
                myStack = push(myStack,singleton,r);
            }
        } else if (b == -1)
        {
            //当b==-1时说明已经回退到最初的状态，即不满足，则直接跳出
            return UnSat;
        }
        //根据选择的元素进行化简
        simplify(myStack->literal,array);

        switch (watchMap(map))
        {
            //返会-1说明存在不满足的句子，进行回退操作
            case -1:
                b = back(&myStack,array);
                break;
            //返回1 说明句子已经满足  直接跳出即可
            case 1:
                return Sat;
            default:
                b = 0;
                break;
        }
    }
}

int back(MyStack **stack,Literal *array)
{
    MyStack *myStack = *stack;
    //还原点的值大于0时 改变方向 并回退  因为在还原点一定会产生回退的情况
    if (myStack->backPoint > 0)
    {
        backSimplify(myStack->literal,array);
        int n = myStack->literal;
        myStack->literal = -n;
        n = myStack->backPoint;
        myStack->backPoint = -n;
        *stack = myStack;
        return 1;
    } else if(myStack->backPoint == 0)
    {
        while (1)
        {
            myStack = backToNextPoint(myStack,array);
            *stack = myStack;
            if (myStack==NULL || myStack->backPoint == -1)
                return -1;
            else if (myStack->backPoint>0)
            {
                backSimplify(myStack->literal,array);
                int n = myStack->literal;
                myStack->literal = -n;
                n = myStack->backPoint;
                myStack->backPoint = -n;
                return 1;
            }
        }
    } else
    {
        if (myStack->backPoint == -1)
            return -1;
        while (1)
        {
            myStack = backToNextPoint(myStack,array);
            *stack = myStack;
            if (myStack==NULL || myStack->backPoint == -1)
                return -1;
            else if (myStack->backPoint>0)
            {
                backSimplify(myStack->literal,array);
                int n = myStack->literal;
                myStack->literal = -n;
                n = myStack->backPoint;
                myStack->backPoint = -n;
                return 1;
            }
        }
    }
}
MyStack * backToNextPoint(MyStack *myStack,Literal *array)
{
    //mySatck  的值无论时多少 总能退到下一个还原点  （-1）的情况单独讨论
    int literal =0;
    do
    {
        myStack = pop(myStack,&literal);
        backSimplify(literal,array);
    }while (myStack!=NULL && myStack->backPoint == 0 );
    //遇到不等于0的点就返回
    return myStack;
}
int pickLiteral(Literal *array)
{
    int size = array->value;
    int max = 0,save = 0;
//    for (int i = 1; i <= size; ++i) {
//        if ((array+i)->value != True &&(array+i)->value != False)
//        {
//            int p = countClause(array+i);
//            if (p > max)
//            {
//                max = p;
//                save = i;
//            }
//        }
//        if ((array-i)->value!=True && (array-i)->value != False)
//        {
//            int n = countClause(array-i);
//            if (n>max)
//            {
//                max = n;
//                save = -i;
//            }
//        }
//    }
//选择第一个符合条件的值：
    for (int i = 0; i <= size; ++i) {
        if ((array+i)->value != True &&(array+i)->value != False)
            save = i;
        else if ((array-i)->value!=True && (array-i)->value != False)
            save = -i;
    }
    return save;
}

void backSimplify(int literal, Literal *array)
{
    //回退已经被满足的clause
    backSatLiteral(array+literal);
    //回退包含 - literal 的句子
    backUnSatLiteral(array-literal);
}

void simplify(int literal, Literal *array)
{
    //将所有包含literal的句子设置为满足,返回被满足的句子个数
    satLiteral(array+literal);
    //将所有包含 -literal的句子进行操作
    unSatLiteral(array-literal);
}

#undef DEBUG