#include "1.h"

int main()
{
    //自定义一个地图 （RowNumber * ColumnNumber）大小
    //'s':起始点字符
    //'e':终点字符
    //'x':障碍物字符
    //'.':可通过点
    char chMapDraw[RowNumber][ColumnNumber] =
    {
        { '.','.','.','x','x','x','.','.'},
        { '.','.','.','.','.','x','x','.'},
        { '.','x','.','x','.','x','.','e'},
        { '.','x','.','x','.','x','.','.'},
        { 's','x','.','.','.','x','.','x'},
        { '.','x','.','.','.','.','.','.'},
    };

    //初始化地图
    A_Star Astar(chMapDraw);

    //A*算法
    Astar.AstarAlgorithm();

    //找到路径
    if (Astar.findRoute())
    {
        Astar.printRoute();//打印路径
    }

    getchar();
}
