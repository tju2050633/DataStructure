#pragma once
#include <iostream>
#include "my_stl.h"

const int ROW_NUM = 15; // ��ͼ�ߴ�
const int COL_NUM = 17;

const int ORIG_ROW = 1; // ���
const int ORIG_COL = 1;
const int DEST_ROW = 13; // �յ�
const int DEST_COL = 15;

class Node
{
    friend class Maze;

private:
    int row;
    int col;
    int step;
    int cost;                         // A*�㷨�ĺ��ģ�����ÿ���ڵ��Ԥ������
    bool vacant;                      //��ǽ��
    bool visited;                     //�ѷ��ʹ�
    bool onPath;                      //��·����
    my_std::vector<Node *> neighbors; //����������ҵ��ڽӽ��

public:
    Node(int r, int c) : row(r), col(c), step(INT_MAX), cost(INT_MAX), vacant(true), visited(false), onPath(false) {}
    bool NoWay(); //�ж��Ƿ���·����
};

bool Node::NoWay()
{
    bool flag = true;
    for (my_std::vector<Node *>::iterator it = neighbors.begin(); it != neighbors.end(); it++)
    {
        if ((*it)->vacant && !(*it)->visited)
        {
            flag = false;
            break;
        }
    }

    return flag;
}

class Maze
{
private:
    Node *orig;                   //���
    Node *dest;                   //�յ�
    Node *maze[ROW_NUM][COL_NUM]; //�Թ�

    Node *currentPos;                //��ǰ���ڷ��ʵĽڵ�
    my_std::vector<Node *> frontier; //�ѷ��ʽ��ı߽�
    my_std::vector<Node *> path;     //��Ч·��

public:
    Maze();          //��ʼ���Թ�����
    ~Maze();         // delete���н��
    void InitMaze(); //��ʼ��ǽ��ͽ���ڽӹ�ϵ
    void PrintMaze();
    void PrintPath();
    void Search();
};

Maze::Maze()
{
    for (int i = 0; i < ROW_NUM; i++)
    {
        for (int j = 0; j < COL_NUM; j++)
        {
            maze[i][j] = new Node(i, j);
        }
    }
    //�����Թ�
    InitMaze();

    //ȷ�������յ�
    orig = maze[ORIG_ROW][ORIG_COL];
    dest = maze[DEST_ROW][DEST_COL];
}

Maze::~Maze()
{
    for (int i = 0; i < ROW_NUM; i++)
    {
        for (int j = 0; j < COL_NUM; j++)
        {
            delete maze[i][j];
        }
    }
}

void Maze::InitMaze()
{
    // char map[ROWS][COLS] = {
    //     {'#','#','#','#','#','#','#'},
    //     {'#','0','#','0','0','0','#'},
    //     {'#','0','#','0','#','#','#'},
    //     {'#','0','0','0','#','0','#'},
    //     {'#','0','#','0','0','0','#'},
    //     {'#','0','#','0','#','0','#'},
    //     {'#','#','#','#','#','#','#'}};

    char map[ROW_NUM][COL_NUM] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '#'},
        {'#', '0', '#', '#', '#', '#', '#', '0', '#', '#', '#', '0', '#', '0', '#', '0', '#'},
        {'#', '0', '0', '#', '0', '0', '#', '0', '#', '0', '0', '0', '#', '0', '0', '0', '#'},
        {'#', '0', '#', '#', '#', '0', '#', '0', '#', '0', '#', '#', '#', '0', '#', '0', '#'},
        {'#', '0', '0', '0', '#', '0', '#', '0', '0', '0', '0', '0', '0', '0', '#', '0', '#'},
        {'#', '0', '#', '0', '#', '0', '#', '#', '#', '#', '#', '#', '#', '#', '#', '0', '#'},
        {'#', '#', '#', '0', '#', '0', '0', '0', '0', '0', '0', '0', '0', '0', '#', '0', '#'},
        {'#', '0', '0', '0', '#', '0', '#', '0', '#', '#', '#', '0', '#', '#', '#', '0', '#'},
        {'#', '0', '#', '#', '#', '0', '#', '0', '0', '0', '#', '0', '0', '0', '0', '0', '#'},
        {'#', '0', '#', '0', '0', '0', '#', '0', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '0', '#', '0', '#', '0', '#', '0', '0', '0', '0', '0', '0', '0', '#', '0', '#'},
        {'#', '0', '0', '0', '#', '0', '#', '0', '#', '0', '#', '#', '#', '0', '#', '0', '#'},
        {'#', '0', '#', '0', '#', '0', '#', '0', '#', '0', '#', '0', '0', '0', '0', '0', '0'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    };

    for (int i = 0; i < ROW_NUM; i++)
    {
        for (int j = 0; j < COL_NUM; j++)
        {
            //��ʼ��ǽ��
            if (map[i][j] == '#')
                maze[i][j]->vacant = false;

            //��ʼ������ڽӹ�ϵ
            if (i > 0)
            {
                maze[i][j]->neighbors.push_back(maze[i - 1][j]);
            }
            if (i < ROW_NUM - 1)
            {
                maze[i][j]->neighbors.push_back(maze[i + 1][j]);
            }
            if (j > 0)
            {
                maze[i][j]->neighbors.push_back(maze[i][j - 1]);
            }
            if (j < COL_NUM - 1)
            {
                maze[i][j]->neighbors.push_back(maze[i][j + 1]);
            }
        }
    }
}

void Maze::PrintMaze()
{
    //��ͷ
    std::cout << "�Թ���ͼ��(Ϊ������ԣ���ʹ�ù̶�����)" << std::endl
              << std::endl;
    //����
    for (int i = 0; i < ROW_NUM; i++)
    {
        for (int j = 0; j < COL_NUM; j++)
        {
            if (maze[i][j]->onPath)
            {
                std::cout << "��";
            }
            else if (maze[i][j]->vacant)
            {
                std::cout << "  ";
            }
            else
            {
                std::cout << "����";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Maze::PrintPath()
{
    std::cout << "�Թ�·����" << std::endl
              << std::endl;

    for (int i = 0; i < path.size(); i++)
    {
        std::cout << "<" << path[i]->row << "," << path[i]->col << ">";
        if (i != path.size() - 1)
            std::cout << " ---> ";
    }
    std::cout << std::endl
              << std::endl;
}

void Maze::Search()
{
    //��ʼ��currentPos
    currentPos = orig;
    currentPos->step = 0;
    currentPos->cost = 0;
    currentPos->visited = true;
    path.push_back(currentPos);

    while (currentPos != dest)
    {
        //��Noway������
        if (currentPos->NoWay())
        {
            //����path������������
            while (true)
            {
                if (path.empty())
                {
                    std::cout << "�Ҳ���·��" << std::endl;
                    return;
                }

                Node *node = path[path.size() - 1];
                if (!node->NoWay())
                {
                    currentPos = node;
                    break;
                }

                path[path.size() - 1]->step = INT_MAX;
                path[path.size() - 1]->cost = INT_MAX;
                path.pop_back();
            }
        }

        //���ڿ�ͨ��node����frontier,����cost
        frontier.clear();
        for (my_std::vector<Node *>::iterator it = currentPos->neighbors.begin(); it != currentPos->neighbors.end(); it++)
        {
            if ((*it)->vacant && !(*it)->visited)
            {
                (*it)->step = currentPos->step + 1 < (*it)->step ? currentPos->step + 1 : (*it)->step; // step���Ը�С�������
                (*it)->cost = (*it)->step + abs(dest->col - (*it)->col) + abs(dest->row - (*it)->row); //����cost
                frontier.push_back(*it);
            }
        }

        //��cost��С�ģ�����currentPos
        Node *nextPos = nullptr;
        int min_cost = INT_MAX;
        for (my_std::vector<Node *>::iterator it = frontier.begin(); it != frontier.end(); it++)
        {
            if ((*it)->cost < min_cost)
            {
                min_cost = (*it)->cost;
                nextPos = *it;
            }
        }
        currentPos = nextPos;
        currentPos->visited = true;
        path.push_back(currentPos);
    }

    // ���·��
    for (my_std::vector<Node *>::iterator it = path.begin(); it != path.end(); it++)
    {
        maze[(*it)->row][(*it)->col]->onPath = true;
    }
}
