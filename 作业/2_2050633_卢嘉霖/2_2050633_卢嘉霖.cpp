#include <iostream>
#include "my_stl.h"

// ��ʼ������
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

// �󽻼�
my_std::list<int> getIntersection(const my_std::list<int> &list1, const my_std::list<int> &list2)
{
    my_std::list<int> intersection;
    my_std::list<int>::iterator p = list1.begin();
    my_std::list<int>::iterator q = list2.begin();

    while (p != list1.end() && q != list2.end())
    {
        // ͬʱ������ֵ��ͬ���뽻������ͬ��С��������
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

// ����б�
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
    // ��ʼ����������
    my_std::list<int> list1 = initList();
    my_std::list<int> list2 = initList();

    // �����㷨���󽻼�
    my_std::list<int> intersection = getIntersection(list1, list2);

    // ������
    displayList(intersection);

    return 0;
}
