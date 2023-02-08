#include <iostream>
#include "my_stl.h"

// 初始化链表
my_std::list<int> initList()
{
    my_std::list<int> list;
    while (true)
    {
        int value = 0;
        std::cin >> value;
        if (!std::cin)
        {
            std::cout << "Invalid input" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        else if (value == -1)
        {
            break;
        }
        else
        {
            list.push_back(value);
        }
    }
    return list;
}

// 求交集
my_std::list<int> getIntersection(const my_std::list<int> &list1, const my_std::list<int> &list2)
{
    my_std::list<int> intersection;
    my_std::list<int>::iterator p = list1.begin();
    my_std::list<int>::iterator q = list2.begin();

    while (p != list1.end() && q != list2.end())
    {
        // 同时遍历，值相同加入交集，不同则小的往后移
        if (*p == *q)
        {
            intersection.push_back(*p);
            p++;
            q++;
        }
        else if (*p < *q)
        {
            p++;
        }
        else
        {
            q++;
        }
    }

    return intersection;
}

// 输出列表
void displayList(my_std::list<int> list)
{
    if (list.size() == 0)
    {
        std::cout << "NULL";
    }
    else
    {
        for (my_std::list<int>::iterator it = list.begin(); it != list.end(); it++)
        {
            std::cout << *it;
            if (it != --list.end())
            {
                std::cout << " ";
            }
        }
    }
}

int main()
{
    // 初始化输入链表
    my_std::list<int> list1 = initList();
    my_std::list<int> list2 = initList();

    // 核心算法：求交集
    my_std::list<int> intersection = getIntersection(list1, list2);

    // 输出结果
    displayList(intersection);

    return 0;
}
