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
            std::cout << "输入非法，请重试" << std::endl;
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
    // 输入结点数和边数
    int NodeNum, EdgeNum;
    GetNodeEdgeNum(NodeNum, EdgeNum);

    // 创建图
    Graph G(NodeNum, EdgeNum);

    // 输出完成任务所需时间和关键路径
    std::cout << G.GetCriticalMissionTime() << std::endl;
    G.PrintCriticalMission();

    return 0;
}
