#include<stdio.h>
#include<stdlib.h>

#define TIME 100 //只搜索100次
#define MAXSIZE 100
int n=1;
int result[9]={1,2,3,8,0,4,7,6,5};//0是空格
typedef struct Node{
    int num[9];
    char expension;//记录是否可以拓展，Y可以，N不可以
    char banOperate;/*表示不能执行的操作，L代表不能左移，
R代表不能右移，U代表不能上移，D代表不能下移，
C代表可以随意移动*/
    int father;//父节点的下标
}Node;
Node store[MAXSIZE];//将搜索过的状态存储于数组中

int same(int temp)//判断是否达到了目标状态
{
    for(int j=0;j<9;j++)

        if(store[temp].num[j]!=result[j])
            return 0;
        return 1;

}

void printResult()//输出搜索结果
{
    for(int j=1;j<=n;j++)
    {
        printf("第%d步搜索后:\n",j);
        printf("\t%d\t%d\t%d\n",
        store[j].num[0],store[j].num[1],store[j].num[2]);
        printf("\t%d\t%d\t%d\n",
        store[j].num[3],store[j].num[4],store[j].num[5]);
        printf("\t%d\t%d\t%d\n",
        store[j].num[6],store[j].num[7],store[j].num[8]);
        printf("\n\n");
    }
}

int left(int temp)//将空格左移
{
    int o;
    for(int j=0;j<9;j++)//判断空格位置
    {
        if(store[temp].num[j]==0)
            o=j;
        break;
    }
    if(o==0||o==3||o==6)
        return 0;
    for(int k=0;k<9;k++)
        store[n].num[k]=store[temp].num[k];
    int tempNum=store[n].num[o-1];//移动后的状态
    store[n].num[o-1]=0;
    store[n].num[o]=tempNum;
    store[temp].expension='N';
    store[n].banOperate='L';
    store[n].expension='Y';
    store[n].father=temp;

    if(same(n))
    {

        printResult();
        exit(1);
    }
    n++;
    return 1;
}

int right(int temp)//将空格右移
{
    int o;
    for(int j=0;j<9;j++)//判断空格位置
    {
        if(store[temp].num[j]==0)
            o=j;
        break;
    }
    if(o==2||o==5||o==8)
        return 0;
    for(int k=0;k<9;k++)
        store[n].num[k]=store[temp].num[k];
    int tempNum=store[n].num[o+1];//移动后的状态
    store[n].num[o+1]=0;
    store[n].num[o]=tempNum;
    store[temp].expension='N';
    store[n].banOperate='R';
    store[n].expension='Y';
    store[n].father=temp;

    if(same(n))
    {

        printResult();
        exit(1);
    }
    n++;
    return 1;
}

int up(int temp)//将空格上移
{
    int o;
    for(int j=0;j<9;j++)//判断空格位置
    {
        if(store[temp].num[j]==0)
            o=j;
        break;
    }
    if(o==0||o==1||o==2)
        return 0;
    for(int k=0;k<9;k++)
        store[n].num[k]=store[temp].num[k];
    int tempNum=store[n].num[o-3];//移动后的状态
    store[n].num[o-3]=0;
    store[n].num[o]=tempNum;
    store[temp].expension='N';
    store[n].banOperate='U';
    store[n].expension='Y';
    store[n].father=temp;

    if(same(n))
    {

        printResult();
        exit(1);
    }
    n++;
    return 1;
}

int down(int temp)//将空格下移
{
    int o;
    for(int j=0;j<9;j++)//判断空格位置
    {
        if(store[temp].num[j]==0)
            o=j;
        break;
    }
    if(o==6||o==7||o==8)
        return 0;
    for(int k=0;k<9;k++)
        store[n].num[k]=store[temp].num[k];
    int tempNum=store[n].num[o+3];//移动后的状态
    store[n].num[o+3]=0;
    store[n].num[o]=tempNum;
    store[temp].expension='N';
    store[n].banOperate='D';
    store[n].expension='Y';
    store[n].father=temp;

    if(same(n))
    {

        printResult();
        exit(1);
    }
    n++;
    return 1;
}

void init()
{
    Node start;
    printf("请输入初始状态，用空格分开，0代表空格:\n");//输入初始状态
    for(int i=0;i<9;i++)
        scanf("%d",&start.num[i]);
    for(int k=0;k<9;k++)
        if(start.num[k]==0)
            break;
    start.banOperate='C';
    start.expension='Y';
    start.father=-1;
    store[0]=start;
}//将初始状态赋予store[0]

int main()
{
    init();
    if(same(0))
    {
        printf("没有必要进行搜索");
        exit(1);
    }


    for(int i=0;i<TIME;i++)
    {
        if(store[i].expension=='Y')
        {
            if(store[i].banOperate=='L')
            {
                up(i);
                right(i);
                down(i);
            }
             if(store[i].banOperate=='R')
            {
                left(i);
                up(i);
                down(i);
            }
             if(store[i].banOperate=='U')
            {
                left(i);
                right(i);
                down(i);
            }
             if(store[i].banOperate=='D')
            {
                left(i);
                up(i);
                right(i);
            }
             if(store[i].banOperate=='C')
            {
                left(i);
                up(i);
                right(i);
                down(i);
            }
        }
        if(n>=TIME)
        {
            n--;
            printResult();
            printf("在搜索范围内没有结果");
            exit(1);
        }
    }
    return 0;
}













