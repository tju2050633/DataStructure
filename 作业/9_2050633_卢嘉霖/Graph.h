#pragma once
#include <iostream>
#include "my_stl.h"

struct Neighbor;
struct Node
{
    int Index;
    Neighbor *HeadNode; //指向邻接表的头结点
    int InDegree;       //入度
    int EarliestTime;   //最早发生时间
    int LatestTime;     //最晚发生时间
    bool isCritical;    //是否是关键结点
};

struct Neighbor
{
    Neighbor *NextNeighbor; //指向下一个邻接点
    Node *Address;          //指向邻接的结点
    int EdgeWeight;         //边的权重
};

class Graph
{
private:
    int NodeNum;                          //结点数
    int EdgeNum;                          //边数
    my_std::vector<Node> NodeList;        //邻接列表
    my_std::vector<Node> ReverseNodeList; //逆邻接列表

    my_std::vector<int> TopologicalOrder; //拓扑序列

    int CriticalMissionTime; //完成任务所需时间

public:
    Graph(int NodeNum, int EdgeNum);
    ~Graph();

    void TopologicalSort();           //拓扑排序，得到拓扑序列
    void CalcEarliestTime(int Index); //得到最早发生时间
    void CalcLatestTime(int Index);   //得到最晚发生时间

    int GetCriticalMissionTime() const //得到完成任务所需时间
    {
        return CriticalMissionTime;
    }
    void PrintCriticalMission(); //输出关键路径

    void Run(); //运行，进行拓扑排序、计算各节点最早/晚时间、关键路径、完成任务所需时间等
};

Graph::Graph(int NodeNum, int EdgeNum)
{
    this->NodeNum = NodeNum;
    this->EdgeNum = EdgeNum;

    // 创建结点数组
    NodeList = my_std::vector<Node>(NodeNum);
    ReverseNodeList = my_std::vector<Node>(NodeNum);
    for (int i = 0; i < NodeNum; i++)
    {
        NodeList[i].Index = ReverseNodeList[i].Index = i;
        NodeList[i].HeadNode = ReverseNodeList[i].HeadNode = nullptr;   //初始化邻接表头结点
        NodeList[i].InDegree = ReverseNodeList[i].InDegree = 0;         //初始化入度
        NodeList[i].EarliestTime = ReverseNodeList[i].EarliestTime = 0; //初始化最早发生时间
        NodeList[i].LatestTime = ReverseNodeList[i].LatestTime = 0;     //初始化最晚发生时间
        NodeList[i].isCritical = ReverseNodeList[i].isCritical = false; //初始化是否是关键结点
    }

    // 输入边
    int StartNode, EndNode, EdgeWeight;
    for (int i = 0; i < EdgeNum; i++)
    {
        // 输入边的起点、终点和权重，确保输入合法
        std::cin >> StartNode >> EndNode >> EdgeWeight;
        std::cin.ignore(INT_MAX, '\n');
        if (!std::cin ||
            StartNode < 1 ||
            StartNode > NodeNum ||
            EndNode < 1 ||
            EndNode > NodeNum ||
            EdgeWeight < 0)
        {
            std::cout << "输入非法，请重试" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            i--;
            continue;
        }

        // 创建邻接点
        Neighbor *NewNeighbor = new Neighbor;
        NewNeighbor->NextNeighbor = nullptr;
        NewNeighbor->Address = &NodeList[EndNode - 1];
        NewNeighbor->EdgeWeight = EdgeWeight;

        // 将邻接点插入邻接表
        NewNeighbor->NextNeighbor = NodeList[StartNode - 1].HeadNode;
        NodeList[StartNode - 1].HeadNode = NewNeighbor;

        // 创建逆邻接点
        Neighbor *NewReverseNeighbor = new Neighbor;
        NewReverseNeighbor->NextNeighbor = nullptr;
        NewReverseNeighbor->Address = &ReverseNodeList[StartNode - 1];
        NewReverseNeighbor->EdgeWeight = EdgeWeight;

        // 将逆邻接点插入逆邻接表
        NewReverseNeighbor->NextNeighbor = ReverseNodeList[EndNode - 1].HeadNode;
        ReverseNodeList[EndNode - 1].HeadNode = NewReverseNeighbor;

        // 弧尾结点入度加一
        NodeList[EndNode - 1].InDegree++;
    }

    // 运行
    Run();
}

Graph::~Graph()
{
    // 释放Neighbor
    for (int i = 0; i < NodeNum; i++)
    {
        // 释放邻接表
        Neighbor *p = NodeList[i].HeadNode;
        while (p != nullptr)
        {
            Neighbor *t = p;
            p = p->NextNeighbor;
            delete t;
        }

        // 释放逆邻接表
        Neighbor *q = ReverseNodeList[i].HeadNode;
        while (q != nullptr)
        {
            Neighbor *t = q;
            q = q->NextNeighbor;
            delete t;
        }
    }
}

void Graph::CalcEarliestTime(int Index)
{
    // p指向逆邻接表头结点
    Neighbor *p = ReverseNodeList[Index].HeadNode;
    int EarliestTime = 0;

    // 遍历结点的上级结点,计算最早发生时间
    while (p != nullptr)
    {
        int Time = p->Address->EarliestTime + p->EdgeWeight; //上级结点最早发生时间+边权重
        if (EarliestTime < Time)                             //更新最早发生时间
            EarliestTime = Time;
        p = p->NextNeighbor;
    }

    // 更新结点最早发生时间
    NodeList[Index].EarliestTime = EarliestTime;
    ReverseNodeList[Index].EarliestTime = EarliestTime;
}

void Graph::CalcLatestTime(int Index)
{
    // p指向邻接表头结点
    Neighbor *p = NodeList[Index].HeadNode;
    int LatestTime = INT_MAX;

    // 遍历结点的下级结点,计算最晚发生时间
    while (p != nullptr)
    {
        int Time = p->Address->LatestTime - p->EdgeWeight; //下级结点最晚发生时间-边权重
        if (LatestTime > Time)                             //更新最晚发生时间
            LatestTime = Time;
        p = p->NextNeighbor;
    }

    // 更新结点最晚发生时间
    NodeList[Index].LatestTime = LatestTime;
    ReverseNodeList[Index].LatestTime = LatestTime;
}

void Graph::TopologicalSort()
{
    // 初始化待访问（入度为0）队列
    my_std::queue<int> ToBeVisited;

    // 将入度为0的结点入队
    for (int i = 0; i < NodeNum; i++)
    {
        if (NodeList[i].InDegree == 0)
        {
            ToBeVisited.push(i);
        }
    }

    // 队空时退出；否则重复将入度为0的结点入队、出队、更新入度
    while (!ToBeVisited.empty())
    {
        // 出队, 将结点加入拓扑序列
        int Index = ToBeVisited.front();
        ToBeVisited.pop();
        TopologicalOrder.push_back(Index);

        // 遍历出队结点的邻接点,更新邻接点入度
        for (Neighbor *p = NodeList[Index].HeadNode; p != nullptr; p = p->NextNeighbor)
        {
            // 入度减一
            p->Address->InDegree--;

            // 入度为0时入队
            if (p->Address->InDegree == 0)
            {
                ToBeVisited.push(p->Address->Index);
            }
        }
    }

    // 若拓扑序列中结点数不等于结点数,则存在环
    if (TopologicalOrder.size() != NodeNum)
    {
        std::cout << "0" << std::endl;
        exit(0);
    }
}

void Graph::PrintCriticalMission()
{
    for (int i = 0; i < NodeNum; i++)
    {
        if (!NodeList[i].isCritical)
            continue;

        // 对关键节点，遍历其下层节点，找到关键路径
        for (Neighbor *p = NodeList[i].HeadNode; p != nullptr; p = p->NextNeighbor)
        {
            if (p->Address->isCritical)
            {
                std::cout << i + 1 << " -> " << p->Address->Index + 1 << std::endl;
            }
        }
    }
}

void Graph::Run()
{
    // 拓扑排序
    TopologicalSort();

    // 计算1~n-1结点最早发生时间
    for (int i = 1; i < NodeNum; i++)
    {
        CalcEarliestTime(TopologicalOrder[i]);
    }

    // 计算0~n-2结点最晚发生时间
    CriticalMissionTime = NodeList[NodeNum - 1].LatestTime = NodeList[NodeNum - 1].EarliestTime;
    for (int i = NodeNum - 2; i >= 0; i--)
    {
        CalcLatestTime(TopologicalOrder[i]);
    }

    // 最早发生时间=最晚发生时间的结点为关键结点
    for (int i = 0; i < NodeNum; i++)
    {
        // 以拓扑排序顺序遍历
        int TopoIndex = TopologicalOrder[i];
        if (NodeList[TopoIndex].EarliestTime == NodeList[TopoIndex].LatestTime)
        {
            NodeList[TopoIndex].isCritical = ReverseNodeList[TopoIndex].isCritical = true;
        }
    }
}
