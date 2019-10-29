#include "1.h"

A_Star::A_Star(const char pImportMap[RowNumber][ColumnNumber])
{
    if (!initMap(pImportMap))
    {
        exit(0);
    }
}

A_Star::~A_Star()
{

}

bool A_Star::initMap( const char pImportMap[RowNumber][ColumnNumber] )
{
    bool isHaveStart,isHaveEnd;
    isHaveStart = isHaveEnd = false;//检测是否有起点和终点

    for(int i=0;i<RowNumber;i++)
    {
        for(int j=0;j<ColumnNumber;j++)
        {
            m_StarNode[i][j].m_cSymbol = pImportMap[i][j];
            m_StarNode[i][j].m_X=i;
            m_StarNode[i][j].m_Y=j;
            if(m_StarNode[i][j].m_cSymbol=='s')
            {
                m_StarNode[i][j].m_Type = Node_Start;
                m_StarNode[i][j].m_Gvalue=0;
                m_StarNode[i][j].m_IsFind=true;
                isHaveStart = true;
                m_StarStart=m_StarNode[i][j];
            }
            else if(m_StarNode[i][j].m_cSymbol=='e')
            {
                m_StarNode[i][j].m_Type = Node_End;
                m_StartEnd=m_StarNode[i][j];
                isHaveEnd = true;
            }
            else if(m_StarNode[i][j].m_cSymbol=='x')
            {
                m_StarNode[i][j].m_Type = Node_Barrier;
            }
            else
            {
                m_StarNode[i][j].m_Type = Node_Way;
            }
        }
    }
    if (!isHaveStart)
    {
        cout<<"Where will We Start"<<endl;
    }
    else if(!isHaveEnd)
    {
        cout<<"Where will We Go ?"<<endl;
    }
    return (isHaveStart&&isHaveEnd);
}

bool A_Star::isOverBorder(int nX,int nY)
{
    if (nX < 0 || nX >= RowNumber || nY < 0 || nY >= ColumnNumber)
    {
        return true;
    }
    return false;
}


//曼哈顿距离为：|x1 - x2| + |y1 - y2|
float A_Star::manhattanDis(int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y)
{
    float hVal;
    hVal=(float)abs(nDisStart_x-nDisEnd_x)+abs(nDisStart_y-nDisEnd_y);
    hVal*=ManhattanSacle;
    return hVal;
}

//加权曼哈顿 better
float A_Star::jiaquan_manhattanDis( int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y )
{
    float hVal,dx,dy;
    dx=(float)abs(nDisStart_x-nDisEnd_x);
    dy=(float)abs(nDisStart_y-nDisEnd_y);
    if(dx>dy)
        hVal=10*dx+6*dy;
    else
        hVal=6*dx+10*dy;
    return hVal;
}

//欧氏距离为： sqrt((x1-x2)^2+(y1-y2)^2 )
float A_Star::euclideanDis( int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y )
{
    float hVal;
    hVal=(float)sqrt(pow((nDisStart_x-nDisEnd_x),2)+pow((nDisStart_y-nDisEnd_y),2));
    return hVal;
}

//切比雪夫距离为：max(|x1 - x2| , |y1 - y2|)
float A_Star::chebyshevDis( int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y )
{
    float hVal;
    hVal=(float)max(abs(nDisStart_x-nDisEnd_x),abs(nDisStart_y-nDisEnd_y));
    return hVal;
}

void A_Star::AstarAlgorithm()
{
    priority_queue<myNode> openQueue;//open表

    openQueue.push(m_StarStart);//将起始点压入open表
    myNode currNode,*neighborNode;
    int nNeighborX,nNeighborY;  //邻居的x，y坐标, 邻居相对于选定点的G值偏移
    float offsetG;
    while(!openQueue.empty())//oepn表不为空一直循环
    {
        currNode = openQueue.top();//每次有元素插入都会进行排序，myNode 重载了操作运算符 < ，每次队列头的元素的F值最小

        if (currNode == m_StartEnd)//当前节点为终点，退出
        {
            break;
        }
        openQueue.pop();//出队列
    //  printRoute();
        for (int i=0;i<NeighborNum;++i)//遍历该节点的邻居
        {
            //根据所有偏移量找到邻居
            nNeighborX = currNode.m_X + offset[i][0];
            nNeighborY = currNode.m_Y + offset[i][1];
            //邻居节点超出边界，障碍物，查找过了都跳过
            if (isOverBorder(nNeighborX,nNeighborY))
            {
                continue;
            }
            neighborNode = &m_StarNode[nNeighborX][nNeighborY];//找到邻居节点的信息
            if (neighborNode->m_IsFind || neighborNode->m_Type == Node_Barrier)
            {
                continue;
            }

            //这里 可以替换不同的算法，选择想用的h(x)
            neighborNode->m_Hvalue = jiaquan_manhattanDis(nNeighborX,nNeighborY,m_StartEnd.m_X,m_StartEnd.m_Y);

            offsetG = 1.0f;//不是对角线的邻居，默认 1 个距离，相当于一个格子
            if (offset[i][0]!=0 && offset[i][1]!=0)//说明是对对角线上的邻居
            {
                offsetG = 1.4f;//取近似值,利于计算,1.4个格子
            }

            //还没压入open表 或者
            //如果该邻居之前的G值(G值是重新选择父亲节点前计算得到的)小于从新计算的G值(以当前点为父节点计算的)
            //该邻居节点的父节点要做更改，指向当前节点作为父节点, 因为这个估值更小，代价更低
            if(neighborNode->m_Gvalue == 0 || neighborNode->m_Gvalue>currNode.m_Gvalue+offsetG)
            {
                neighborNode->m_ParentNode = &m_StarNode[currNode.m_X][currNode.m_Y];
                neighborNode->m_Gvalue = currNode.m_Gvalue+offsetG;
            }

            neighborNode->m_IsFind = true;//被查找过了

            openQueue.push(*neighborNode);
        }
    }
}

bool A_Star::findRoute()
{
    myNode* pNode = m_StarNode[m_StartEnd.m_X][m_StartEnd.m_Y].m_ParentNode;//最后节点，非终点
    if (pNode == NULL)
    {
        cout<<"坑爹啊？根本没有路径可以到达终点"<<endl;
        return false;
    }
    //根据终点，一个个往回找
    while (pNode)
    {
        if (pNode->m_ParentNode)
        {
            pNode->m_Type = Node_FindWay;
        }
        pNode = pNode->m_ParentNode;
    }
    return true;
}

void A_Star::printRoute()
{
    int nFindNum = 0;//统计遍历的节点数
    for(int i=0;i<RowNumber;i++)
    {
        for(int j=0;j<ColumnNumber;j++)
        {
            if (m_StarNode[i][j].m_IsFind)//统计遍历的节点数
            {
                nFindNum++;
            }
            if(m_StarNode[i][j].m_Type==Node_FindWay)//找到的路
                cout<<FindWay;//<<"F:"<<m_StarNode[i][j].m_Gvalue+m_StarNode[i][j].m_Hvalue;
            else if(m_StarNode[i][j].m_IsFind)//找过的地方
            {
                if (m_StarNode[i][j].m_Type == Node_Way)
                {
                    cout<<HaveFindPlace;//<<"F:"<<m_StarNode[i][j].m_Gvalue+m_StarNode[i][j].m_Hvalue;
                }
                else
                {
                    cout<<m_StarNode[i][j].m_cSymbol;
                }
            }
            else
                cout<<m_StarNode[i][j].m_cSymbol;
        }
        cout<<endl;
    }
    cout<<"共找了 "<<nFindNum<<" 个节点，终于找到了路"<<endl;
}
