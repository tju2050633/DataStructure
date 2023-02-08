#include "Graph.h"

void GetNodeEdgeNum(int &NodeNum, int &EdgeNum)
{
    while (true)
    {
        std::cin >> NodeNum >> EdgeNum;
        std::cin.ignore(INT_MAX, '\n');
        if (!std::cin ||
            NodeNum < 2 ||
            EdgeNum < NodeNum - 1 ||
            EdgeNum > NodeNum * (NodeNum - 1) / 2)
        {
            std::cout << "����Ƿ���������" << std::endl;
            std::cin.clear();
        }
        else
        {
            break;
        }
    }
}

int main()
{
    // ���������ͱ���
    int NodeNum, EdgeNum;
    GetNodeEdgeNum(NodeNum, EdgeNum);

    // ����ͼ
    Graph G(NodeNum, EdgeNum);

    // ��������������ʱ��͹ؼ�·��
    std::cout << G.GetCriticalMissionTime() << std::endl;
    G.PrintCriticalMission();

    return 0;
}
