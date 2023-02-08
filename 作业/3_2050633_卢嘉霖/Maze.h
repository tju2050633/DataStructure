#pragma once
#include <iostream>
#include "my_stl.h"

const int ROW_NUM = 15; // 地图尺寸
const int COL_NUM = 17;

const int ORIG_ROW = 1; // 起点
const int ORIG_COL = 1;
const int DEST_ROW = 13; // 终点
const int DEST_COL = 15;

class Node
{
    friend class Maze;

private:
    int row;
    int col;
    int step;
    int cost;                         // A*算法的核心，计算每个节点的预估代价
    bool vacant;                      //非墙体
    bool visited;                     //已访问过
    bool onPath;                      //在路径上
    my_std::vector<Node *> neighbors; //结点上下左右的邻接结点

public:
    Node(int r, int c) : row(r), col(c), step(INT_MAX), cost(INT_MAX), vacant(true), visited(false), onPath(false) {}
    bool NoWay(); //判断是否有路可走
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
    Node *orig;                   //起点
    Node *dest;                   //终点
    Node *maze[ROW_NUM][COL_NUM]; //迷宫

    Node *currentPos;                //当前正在访问的节点
    my_std::vector<Node *> frontier; //已访问结点的边界
    my_std::vector<Node *> path;     //有效路径

public:
    Maze();          //初始化迷宫数据
    ~Maze();         // delete所有结点
    void InitMaze(); //初始化墙体和结点邻接关系
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
    //画出迷宫
    InitMaze();

    //确定起点和终点
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
            //初始化墙体
            if (map[i][j] == '#')
                maze[i][j]->vacant = false;

            //初始化结点邻接关系
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
    //表头
    std::cout << "迷宫地图：(为方便测试，已使用固定数据)" << std::endl
              << std::endl;
    //表身
    for (int i = 0; i < ROW_NUM; i++)
    {
        for (int j = 0; j < COL_NUM; j++)
        {
            if (maze[i][j]->onPath)
            {
                std::cout << "〇";
            }
            else if (maze[i][j]->vacant)
            {
                std::cout << "  ";
            }
            else
            {
                std::cout << "██";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Maze::PrintPath()
{
    std::cout << "迷宫路径：" << std::endl
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
    //初始化currentPos
    currentPos = orig;
    currentPos->step = 0;
    currentPos->cost = 0;
    currentPos->visited = true;
    path.push_back(currentPos);

    while (currentPos != dest)
    {
        //若Noway，回溯
        if (currentPos->NoWay())
        {
            //沿着path数组往回搜索
            while (true)
            {
                if (path.empty())
                {
                    std::cout << "找不到路径" << std::endl;
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

        //相邻可通行node加入frontier,更新cost
        frontier.clear();
        for (my_std::vector<Node *>::iterator it = currentPos->neighbors.begin(); it != currentPos->neighbors.end(); it++)
        {
            if ((*it)->vacant && !(*it)->visited)
            {
                (*it)->step = currentPos->step + 1 < (*it)->step ? currentPos->step + 1 : (*it)->step; // step可以更小，则更新
                (*it)->cost = (*it)->step + abs(dest->col - (*it)->col) + abs(dest->row - (*it)->row); //更新cost
                frontier.push_back(*it);
            }
        }

        //找cost最小的，更新currentPos
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

    // 标记路径
    for (my_std::vector<Node *>::iterator it = path.begin(); it != path.end(); it++)
    {
        maze[(*it)->row][(*it)->col]->onPath = true;
    }
}
