#pragma once
#include <stdio.h>
#include <iostream>
#include <queue>
#include <math.h>
#include <stdlib.h>
using namespace std;

//定义是否可以走对角线的宏
#define WALK_DIAGONAL

#ifdef WALK_DIAGONAL

#define NeighborNum 8       //邻居个数
static int offset[NeighborNum][2]={{1,0},{1,1},{1,-1},{-1,0},{-1,-1},{-1,1},{0,-1},{0,1}};//邻居的坐标选择

#else

#define NeighborNum 4   //邻居个数
static int offset[NeighborNum][2]={{1,0},{-1,0},{0,-1},{0,1}};//邻居的坐标选择

#endif

//定义二维数组的长度
#define RowNumber 6
#define ColumnNumber 8

//定义曼哈顿距离的扩大比例
#define ManhattanSacle 10 //10倍

enum NodeType
{
    Node_Start = 0,     //起始点
    Node_Barrier,       //障碍物，把所有不能通过的点都认为是障碍物
    Node_Way,           //可通行的路
    Node_FindWay,       //经过寻路后，会经过的点
    Node_End,           //终点
    Node_Null,          //未定义的点
};

//定义找到的路径的符号表示
#define FindWay '*' //最终找到的路径的符号表示
#define HaveFindPlace 'o'//找过的地方的符号表示

//定义一个节点的数据结构
struct myNode
{
    myNode()
    {
        m_ParentNode = NULL;
        m_Type = Node_Null;
        m_X = m_Y = 0;
        m_Gvalue = 0;
        m_Hvalue = 0;
        m_ParentNode = NULL;
        m_IsFind = false;
    }
    char m_cSymbol;     //该节点的符号
    int m_Type;         //该节点的类型
    int m_X;            //节点的X坐标
    int m_Y;            //节点的Y坐标
    float m_Gvalue;     //g(x)  G值
    float m_Hvalue;     //h(x)  H值
    myNode* m_ParentNode;   //该节点指向的父节点
    bool m_IsFind;      //该节点是否被找过

    //按F值（= G + H） 从小到大排序，F值小的优先级高
    friend bool operator<(myNode nNodeA,myNode nNodeB)
    {
        return (nNodeA.m_Gvalue+nNodeA.m_Hvalue > nNodeB.m_Gvalue+nNodeB.m_Hvalue);
    }

    //重载操作符 ==
    friend bool operator==(myNode nNodeA,myNode nNodeB)
    {
        return (nNodeA.m_X == nNodeB.m_X &&  nNodeA.m_Y == nNodeB.m_Y);
    }
};

class A_Star
{
public:

    A_Star(const char pImportMap[RowNumber][ColumnNumber]);

    ~A_Star();

protected:

    //初始化地图
    bool initMap(const char pImportMap[RowNumber][ColumnNumber]);

    //曼哈顿距离为：|x1 - x2| + |y1 - y2|
    float manhattanDis(int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y);

    //加权曼哈顿距离 better  不大清楚为什么用这个
    float jiaquan_manhattanDis(int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y);

    //欧氏距离为： sqrt((x1-x2)^2+(y1-y2)^2 )
    float euclideanDis(int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y);

    //切比雪夫距离为：max(|x1 - x2| , |y1 - y2|)
    float chebyshevDis(int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y);

    //大小比较函数
    int max(int a,int b)
    {
        return a>b?a:b;
    }


//对外接口
public:

    //判断节点是否超过边界
    //return true 超过边界，false：未超过
    bool isOverBorder(int nX,int nY);

    //A*核心算法
    void AstarAlgorithm();

    //找到路线路线
    bool findRoute();

    //打印出路线
    void printRoute();


private:

    myNode  m_StarNode[RowNumber][ColumnNumber];    //存储所有节点数
    myNode  m_StarStart;        //开始节点
    myNode  m_StartEnd;         //终点节点
};
