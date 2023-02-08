#include <iostream>
#include "my_stl.h"

int GetInt(int low = INT_MIN, int high = INT_MAX)
{
    int number;
    while (true)
    {
        std::cin >> number;
        if (!std::cin || number < low || number > high)
        {
            std::cout << "输入非法，请重新输入!" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        else
        {
            break;
        }
    }
    return number;
}

class MyList
{
private:
    my_std::vector<int> _list;

public:
    MyList(int size);

    int GetMinCost();
    void Insert(int value);
};

MyList::MyList(int size)
{
    for (int i = 0; i < size; i++)
    {
        _list.push_back(GetInt(1));
    }
}

int MyList::GetMinCost()
{
    int cost = 0;
    // 从小到大排序，即为依次切割长度
    _list.sort();

    // 从小到大依次合成，将合成后的结果插入并保持有序
    while (_list.size() > 1)
    {
        int sum = _list[0] + _list[1];
        cost += sum;
        _list.erase(_list.begin(), _list.begin() + 2); // 移除前两个元素

        Insert(sum);
    }

    return cost;
}

void MyList::Insert(int value)
{
    // 插入并保持有序
    for (my_std::vector<int>::iterator it = _list.begin();; it++)
    {
        if (*it > value || it == _list.end())
        {
            _list.insert(it, value);
            break;
        }
    }
}

int main()
{
    int number = GetInt(2, 10000);
    MyList l(number);
    std::cout << l.GetMinCost() << std::endl;

    return 0;
}