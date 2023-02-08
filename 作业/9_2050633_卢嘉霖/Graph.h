#pragma once
#include <iostream>
#include "my_stl.h"

struct Neighbor;
struct Node
{
    int Index;
    Neighbor *HeadNode; //ָ���ڽӱ��ͷ���
    int InDegree;       //���
    int EarliestTime;   //���緢��ʱ��
    int LatestTime;     //������ʱ��
    bool isCritical;    //�Ƿ��ǹؼ����
};

struct Neighbor
{
    Neighbor *NextNeighbor; //ָ����һ���ڽӵ�
    Node *Address;          //ָ���ڽӵĽ��
    int EdgeWeight;         //�ߵ�Ȩ��
};

class Graph
{
private:
    int NodeNum;                          //�����
    int EdgeNum;                          //����
    my_std::vector<Node> NodeList;        //�ڽ��б�
    my_std::vector<Node> ReverseNodeList; //���ڽ��б�

    my_std::vector<int> TopologicalOrder; //��������

    int CriticalMissionTime; //�����������ʱ��

public:
    Graph(int NodeNum, int EdgeNum);
    ~Graph();

    void TopologicalSort();           //�������򣬵õ���������
    void CalcEarliestTime(int Index); //�õ����緢��ʱ��
    void CalcLatestTime(int Index);   //�õ�������ʱ��

    int GetCriticalMissionTime() const //�õ������������ʱ��
    {
        return CriticalMissionTime;
    }
    void PrintCriticalMission(); //����ؼ�·��

    void Run(); //���У������������򡢼�����ڵ�����/��ʱ�䡢�ؼ�·���������������ʱ���
};

Graph::Graph(int NodeNum, int EdgeNum)
{
    this->NodeNum = NodeNum;
    this->EdgeNum = EdgeNum;

    // �����������
    NodeList = my_std::vector<Node>(NodeNum);
    ReverseNodeList = my_std::vector<Node>(NodeNum);
    for (int i = 0; i < NodeNum; i++)
    {
        NodeList[i].Index = ReverseNodeList[i].Index = i;
        NodeList[i].HeadNode = ReverseNodeList[i].HeadNode = nullptr;   //��ʼ���ڽӱ�ͷ���
        NodeList[i].InDegree = ReverseNodeList[i].InDegree = 0;         //��ʼ�����
        NodeList[i].EarliestTime = ReverseNodeList[i].EarliestTime = 0; //��ʼ�����緢��ʱ��
        NodeList[i].LatestTime = ReverseNodeList[i].LatestTime = 0;     //��ʼ��������ʱ��
        NodeList[i].isCritical = ReverseNodeList[i].isCritical = false; //��ʼ���Ƿ��ǹؼ����
    }

    // �����
    int StartNode, EndNode, EdgeWeight;
    for (int i = 0; i < EdgeNum; i++)
    {
        // ����ߵ���㡢�յ��Ȩ�أ�ȷ������Ϸ�
        std::cin >> StartNode >> EndNode >> EdgeWeight;
        std::cin.ignore(INT_MAX, '\n');
        if (!std::cin ||
            StartNode < 1 ||
            StartNode > NodeNum ||
            EndNode < 1 ||
            EndNode > NodeNum ||
            EdgeWeight < 0)
        {
            std::cout << "����Ƿ���������" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            i--;
            continue;
        }

        // �����ڽӵ�
        Neighbor *NewNeighbor = new Neighbor;
        NewNeighbor->NextNeighbor = nullptr;
        NewNeighbor->Address = &NodeList[EndNode - 1];
        NewNeighbor->EdgeWeight = EdgeWeight;

        // ���ڽӵ�����ڽӱ�
        NewNeighbor->NextNeighbor = NodeList[StartNode - 1].HeadNode;
        NodeList[StartNode - 1].HeadNode = NewNeighbor;

        // �������ڽӵ�
        Neighbor *NewReverseNeighbor = new Neighbor;
        NewReverseNeighbor->NextNeighbor = nullptr;
        NewReverseNeighbor->Address = &ReverseNodeList[StartNode - 1];
        NewReverseNeighbor->EdgeWeight = EdgeWeight;

        // �����ڽӵ�������ڽӱ�
        NewReverseNeighbor->NextNeighbor = ReverseNodeList[EndNode - 1].HeadNode;
        ReverseNodeList[EndNode - 1].HeadNode = NewReverseNeighbor;

        // ��β�����ȼ�һ
        NodeList[EndNode - 1].InDegree++;
    }

    // ����
    Run();
}

Graph::~Graph()
{
    // �ͷ�Neighbor
    for (int i = 0; i < NodeNum; i++)
    {
        // �ͷ��ڽӱ�
        Neighbor *p = NodeList[i].HeadNode;
        while (p != nullptr)
        {
            Neighbor *t = p;
            p = p->NextNeighbor;
            delete t;
        }

        // �ͷ����ڽӱ�
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
    // pָ�����ڽӱ�ͷ���
    Neighbor *p = ReverseNodeList[Index].HeadNode;
    int EarliestTime = 0;

    // ���������ϼ����,�������緢��ʱ��
    while (p != nullptr)
    {
        int Time = p->Address->EarliestTime + p->EdgeWeight; //�ϼ�������緢��ʱ��+��Ȩ��
        if (EarliestTime < Time)                             //�������緢��ʱ��
            EarliestTime = Time;
        p = p->NextNeighbor;
    }

    // ���½�����緢��ʱ��
    NodeList[Index].EarliestTime = EarliestTime;
    ReverseNodeList[Index].EarliestTime = EarliestTime;
}

void Graph::CalcLatestTime(int Index)
{
    // pָ���ڽӱ�ͷ���
    Neighbor *p = NodeList[Index].HeadNode;
    int LatestTime = INT_MAX;

    // ���������¼����,����������ʱ��
    while (p != nullptr)
    {
        int Time = p->Address->LatestTime - p->EdgeWeight; //�¼����������ʱ��-��Ȩ��
        if (LatestTime > Time)                             //����������ʱ��
            LatestTime = Time;
        p = p->NextNeighbor;
    }

    // ���½��������ʱ��
    NodeList[Index].LatestTime = LatestTime;
    ReverseNodeList[Index].LatestTime = LatestTime;
}

void Graph::TopologicalSort()
{
    // ��ʼ�������ʣ����Ϊ0������
    my_std::queue<int> ToBeVisited;

    // �����Ϊ0�Ľ�����
    for (int i = 0; i < NodeNum; i++)
    {
        if (NodeList[i].InDegree == 0)
        {
            ToBeVisited.push(i);
        }
    }

    // �ӿ�ʱ�˳��������ظ������Ϊ0�Ľ����ӡ����ӡ��������
    while (!ToBeVisited.empty())
    {
        // ����, ����������������
        int Index = ToBeVisited.front();
        ToBeVisited.pop();
        TopologicalOrder.push_back(Index);

        // �������ӽ����ڽӵ�,�����ڽӵ����
        for (Neighbor *p = NodeList[Index].HeadNode; p != nullptr; p = p->NextNeighbor)
        {
            // ��ȼ�һ
            p->Address->InDegree--;

            // ���Ϊ0ʱ���
            if (p->Address->InDegree == 0)
            {
                ToBeVisited.push(p->Address->Index);
            }
        }
    }

    // �����������н���������ڽ����,����ڻ�
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

        // �Թؼ��ڵ㣬�������²�ڵ㣬�ҵ��ؼ�·��
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
    // ��������
    TopologicalSort();

    // ����1~n-1������緢��ʱ��
    for (int i = 1; i < NodeNum; i++)
    {
        CalcEarliestTime(TopologicalOrder[i]);
    }

    // ����0~n-2���������ʱ��
    CriticalMissionTime = NodeList[NodeNum - 1].LatestTime = NodeList[NodeNum - 1].EarliestTime;
    for (int i = NodeNum - 2; i >= 0; i--)
    {
        CalcLatestTime(TopologicalOrder[i]);
    }

    // ���緢��ʱ��=������ʱ��Ľ��Ϊ�ؼ����
    for (int i = 0; i < NodeNum; i++)
    {
        // ����������˳�����
        int TopoIndex = TopologicalOrder[i];
        if (NodeList[TopoIndex].EarliestTime == NodeList[TopoIndex].LatestTime)
        {
            NodeList[TopoIndex].isCritical = ReverseNodeList[TopoIndex].isCritical = true;
        }
    }
}
