#include <iostream>
#include "my_stl.h"

const int MAX_LENGTH = 20;
const int INF = INT_MAX;

/* 输入一定范围内的整数 */
int GetInt(const char *prompt, int low = INT_MIN, int high = INT_MAX)
{
    int number;
    while (true)
    {
        std::cout << prompt;
        std::cin >> number;
        std::cin.ignore(INT_MAX, '\n');
        if (!std::cin || number < low || number > high)
        {
            std::cout << "输入非法，请重新输入!" << std::endl;
            std::cin.ignore(INT_MAX, '\n');
            std::cin.clear();
        }
        else
        {
            break;
        }
    }
    return number;
}

struct Node
{
    // char name[MAX_LENGTH];
    my_std::string name;
    bool visited;

    Node() : name(""), visited(false) {}
};

struct TreeNode
{
    my_std::pair<my_std::string, my_std::string> nodes;
    int weight;

    TreeNode() : nodes(my_std::pair<my_std::string, my_std::string>("", "")), weight(0) {}
    TreeNode(const my_std::string first, const my_std::string second, int weight) : weight(weight)
    {
        nodes.first = first;
        nodes.second = second;
    }
};

class ElectricityNet
{
private:
    int node_num;
    my_std::vector<Node> nodes_list;
    my_std::vector<my_std::vector<int> > AdjMatrix;

    int tree_node_num;
    my_std::vector<TreeNode> tree;

    bool nodeInited;  // 结点是否已初始化
    bool edgeInited;  // 边是否已初始化
    bool treeCreated; // 最小生成树是否已创建

public:
    ElectricityNet();

    void CreateNodes();
    void CreateEdges();
    void CreateMST();
    void PrintMST() const;
};

ElectricityNet::ElectricityNet()
{
    // 初始化标志
    nodeInited = false;
    edgeInited = false;
    treeCreated = false;
}

void ElectricityNet::CreateNodes()
{
    if (nodeInited)
    {
        std::cout << "结点已初始化，无需再次初始化" << std::endl;
        return;
    }

    // 输入结点个数
    node_num = GetInt("请输入顶点的个数：", 1);

    // 初始化结点列表 邻接矩阵
    for (int i = 0; i < node_num; i++)
    {
        nodes_list.push_back(Node());
        AdjMatrix.push_back(my_std::vector<int>());
        for (int j = 0; j < node_num; j++)
        {
            AdjMatrix[i].push_back(i == j ? 0 : INF);
        }
    }

    // 初始化结点数据
    std::cout << "请输入各顶点的名称：" << std::endl;
    for (int i = 0; i < node_num; i++)
    {
        std::cin >> nodes_list[i].name;
        nodes_list[i].visited = false;
    }
    std::cout << std::endl;

    nodeInited = true;
}

void ElectricityNet::CreateEdges()
{
    if (!nodeInited)
    {
        std::cout << "请先初始化结点！" << std::endl;
        return;
    }

    if (edgeInited)
    {
        std::cout << "边已初始化，无需再次初始化" << std::endl;
        return;
    }

    while (true)
    {
        // 输入结点和权重
        std::cout << "请输入边的两个顶点及其权值：";
        my_std::pair<my_std::string, my_std::string> two_nodes;
        int weight;

        while (true)
        {
            std::cin >> two_nodes.first >> two_nodes.second >> weight;

            if (!std::cin || weight < 0)
            {
                std::cout << "输入非法，请重新输入!" << std::endl;
                std::cin.clear();
            }
            else
            {
                break;
            }
            std::cin.ignore(INT_MAX, '\n');
        }

        // 查找结点
        int index1 = -1, index2 = -1;
        for (int i = 0; i < node_num; i++)
        {
            if (two_nodes.first == nodes_list[i].name)
                index1 = i;
            if (two_nodes.second == nodes_list[i].name)
                index2 = i;
        }

        // 添加边
        if (index1 != -1 && index2 != -1)
            AdjMatrix[index1][index2] = AdjMatrix[index2][index1] = weight;
        else
        {
            std::cout << "输入的结点不存在！" << std::endl;
            std::cout << "是否停止输入？y/n : ";
            char c;
            std::cin >> c;
            std::cin.ignore(INT_MAX, '\n');
            if (c == 'y' || c == 'Y')
                break;
            else if (c == 'n' || c == 'N')
                continue;
            else
            {
                std::cout << "输入非法，请继续输入！" << std::endl;
                continue;
            }
        }
    }
    std::cout << std::endl;

    edgeInited = true;
}

void ElectricityNet::CreateMST()
{
    if (!nodeInited)
    {
        std::cout << "请先初始化结点！" << std::endl;
        return;
    }
    if (!edgeInited)
    {
        std::cout << "请先初始化边！" << std::endl;
        return;
    }

    // 先清空最小生成树
    tree.clear();
    for(int i = 0; i < node_num; i++)
        nodes_list[i].visited = false;

    // 输入起始顶点
    my_std::string start_node;
    std::cout << "请输入起始顶点：";
    std::cin >> start_node;

    // 维护访问过的结点数组
    my_std::vector<Node> VisitedNodes;

    // 起始结点入栈
    int start_node_index = 0;
    for (; start_node_index < node_num; start_node_index++)
    {
        if (start_node == nodes_list[start_node_index].name)
        {
            VisitedNodes.push_back(nodes_list[start_node_index]);
            nodes_list[start_node_index].visited = true;
            break;
        }
    }
    if (start_node_index == node_num)
    {
        std::cout << "起始结点不存在！" << std::endl;
        return;
    }

    // 判断起始结点是否在连通图内
    bool flag = false;
    for (int i = 0; i < node_num; i++)
    {
        if (AdjMatrix[start_node_index][i] != INF && i != start_node_index)
        {
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        std::cout << "起始结点不在连通图内！" << std::endl
                  << std::endl;
        return;
    }

    // 生成最小生成树
    while (true)
    {
        int r = -1;
        int c = -1;
        int min_weight = INF;
        for (int k = 0; k < VisitedNodes.size(); k++) // 对已访问结点遍历
        {
            // 找到当前结点的索引
            int i = 0;
            for (; i < node_num; i++)
            {
                if (VisitedNodes[k].name == nodes_list[i].name)
                    break;
            }
            // 找当前最小生成树的最近结点
            for (int j = 0; j < node_num; j++)
            {
                if (i != j && !nodes_list[j].visited && AdjMatrix[i][j] < min_weight)
                {
                    min_weight = AdjMatrix[i][j];
                    r = i;
                    c = j;
                }
            }
        }
        // 若未找到可以入栈的结点，说明连通图已遍历完毕
        if (r == -1 || c == -1)
            break;

        // 结点入栈
        nodes_list[c].visited = true;
        VisitedNodes.push_back(nodes_list[c]);
        tree.push_back(TreeNode(nodes_list[r].name, nodes_list[c].name, min_weight));
    }

    tree_node_num = tree.size();
    std::cout << "生成Prim最小生成树！" << std::endl
              << std::endl;

    treeCreated = true;
}

void ElectricityNet::PrintMST() const
{
    if (!treeCreated)
    {
        std::cout << "请先生成最小生成树！" << std::endl;
        return;
    }
    std::cout << "最小生成树的顶点及边为：" << std::endl
              << std::endl;

    for (int i = 0; i < tree_node_num; i++)
    {
        std::cout << tree[i].nodes.first << "-(" << tree[i].weight << ")->" << tree[i].nodes.second << "     ";
    }

    std::cout << std::endl
              << std::endl;
}
