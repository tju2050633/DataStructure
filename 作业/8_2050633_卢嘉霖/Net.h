#include <iostream>
#include "my_stl.h"

const int MAX_LENGTH = 20;
const int INF = INT_MAX;

/* ����һ����Χ�ڵ����� */
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
            std::cout << "����Ƿ�������������!" << std::endl;
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

    bool nodeInited;  // ����Ƿ��ѳ�ʼ��
    bool edgeInited;  // ���Ƿ��ѳ�ʼ��
    bool treeCreated; // ��С�������Ƿ��Ѵ���

public:
    ElectricityNet();

    void CreateNodes();
    void CreateEdges();
    void CreateMST();
    void PrintMST() const;
};

ElectricityNet::ElectricityNet()
{
    // ��ʼ����־
    nodeInited = false;
    edgeInited = false;
    treeCreated = false;
}

void ElectricityNet::CreateNodes()
{
    if (nodeInited)
    {
        std::cout << "����ѳ�ʼ���������ٴγ�ʼ��" << std::endl;
        return;
    }

    // ���������
    node_num = GetInt("�����붥��ĸ�����", 1);

    // ��ʼ������б� �ڽӾ���
    for (int i = 0; i < node_num; i++)
    {
        nodes_list.push_back(Node());
        AdjMatrix.push_back(my_std::vector<int>());
        for (int j = 0; j < node_num; j++)
        {
            AdjMatrix[i].push_back(i == j ? 0 : INF);
        }
    }

    // ��ʼ���������
    std::cout << "���������������ƣ�" << std::endl;
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
        std::cout << "���ȳ�ʼ����㣡" << std::endl;
        return;
    }

    if (edgeInited)
    {
        std::cout << "���ѳ�ʼ���������ٴγ�ʼ��" << std::endl;
        return;
    }

    while (true)
    {
        // �������Ȩ��
        std::cout << "������ߵ��������㼰��Ȩֵ��";
        my_std::pair<my_std::string, my_std::string> two_nodes;
        int weight;

        while (true)
        {
            std::cin >> two_nodes.first >> two_nodes.second >> weight;

            if (!std::cin || weight < 0)
            {
                std::cout << "����Ƿ�������������!" << std::endl;
                std::cin.clear();
            }
            else
            {
                break;
            }
            std::cin.ignore(INT_MAX, '\n');
        }

        // ���ҽ��
        int index1 = -1, index2 = -1;
        for (int i = 0; i < node_num; i++)
        {
            if (two_nodes.first == nodes_list[i].name)
                index1 = i;
            if (two_nodes.second == nodes_list[i].name)
                index2 = i;
        }

        // ��ӱ�
        if (index1 != -1 && index2 != -1)
            AdjMatrix[index1][index2] = AdjMatrix[index2][index1] = weight;
        else
        {
            std::cout << "����Ľ�㲻���ڣ�" << std::endl;
            std::cout << "�Ƿ�ֹͣ���룿y/n : ";
            char c;
            std::cin >> c;
            std::cin.ignore(INT_MAX, '\n');
            if (c == 'y' || c == 'Y')
                break;
            else if (c == 'n' || c == 'N')
                continue;
            else
            {
                std::cout << "����Ƿ�����������룡" << std::endl;
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
        std::cout << "���ȳ�ʼ����㣡" << std::endl;
        return;
    }
    if (!edgeInited)
    {
        std::cout << "���ȳ�ʼ���ߣ�" << std::endl;
        return;
    }

    // �������С������
    tree.clear();
    for(int i = 0; i < node_num; i++)
        nodes_list[i].visited = false;

    // ������ʼ����
    my_std::string start_node;
    std::cout << "��������ʼ���㣺";
    std::cin >> start_node;

    // ά�����ʹ��Ľ������
    my_std::vector<Node> VisitedNodes;

    // ��ʼ�����ջ
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
        std::cout << "��ʼ��㲻���ڣ�" << std::endl;
        return;
    }

    // �ж���ʼ����Ƿ�����ͨͼ��
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
        std::cout << "��ʼ��㲻����ͨͼ�ڣ�" << std::endl
                  << std::endl;
        return;
    }

    // ������С������
    while (true)
    {
        int r = -1;
        int c = -1;
        int min_weight = INF;
        for (int k = 0; k < VisitedNodes.size(); k++) // ���ѷ��ʽ�����
        {
            // �ҵ���ǰ��������
            int i = 0;
            for (; i < node_num; i++)
            {
                if (VisitedNodes[k].name == nodes_list[i].name)
                    break;
            }
            // �ҵ�ǰ��С��������������
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
        // ��δ�ҵ�������ջ�Ľ�㣬˵����ͨͼ�ѱ������
        if (r == -1 || c == -1)
            break;

        // �����ջ
        nodes_list[c].visited = true;
        VisitedNodes.push_back(nodes_list[c]);
        tree.push_back(TreeNode(nodes_list[r].name, nodes_list[c].name, min_weight));
    }

    tree_node_num = tree.size();
    std::cout << "����Prim��С��������" << std::endl
              << std::endl;

    treeCreated = true;
}

void ElectricityNet::PrintMST() const
{
    if (!treeCreated)
    {
        std::cout << "����������С��������" << std::endl;
        return;
    }
    std::cout << "��С�������Ķ��㼰��Ϊ��" << std::endl
              << std::endl;

    for (int i = 0; i < tree_node_num; i++)
    {
        std::cout << tree[i].nodes.first << "-(" << tree[i].weight << ")->" << tree[i].nodes.second << "     ";
    }

    std::cout << std::endl
              << std::endl;
}
