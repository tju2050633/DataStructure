#pragma once
#include <iostream>
#include "my_stl.h"

class Bank
{
private:
    my_std::vector<int> Input;
    my_std::vector<int> Output;
    int N; //输入正整数个数
    int t; //表示处理业务的时刻
    int p; //快指针，表示A窗口
    int q; //慢指针，表示B窗口
    int i; //输出数组索引

public:
    Bank();
    void GetInput();
    void GetOutput();
    void DisplayOutput() const;

    bool isOdd(int num) const;
    bool isEven(int num) const;
};

Bank::Bank()
{
    N = 0;
    t = 0;
    p = 0;
    q = 0;
    i = 0;
}

void Bank::GetInput() //获取输入正整数
{
    while (true)
    {
        std::cin >> N;
        if (!std::cin || N < 1 || N > 1000)
        {
            std::cout << "输入错误，请重新输入！\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        else
            break;
    }

    Input = my_std::vector<int>(N);
    Output = my_std::vector<int>(N);

    for (int i = 0; i < N; i++) //获取数组内容
    {
        while (true)
        {
            std::cin >> Input[i];
            if (!std::cin || Input[i] < 1)
            {
                std::cout << "输入错误，请重新输入！\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            else
                break;
        }
    }
}

void Bank::GetOutput()
{
    while (p < N || q < N)
    {
        t++; // t代表时刻

        for (; p < N && !isOdd(Input[p]); p++) //找到下一个奇数
        {
        }

        if (p != N)
            Output[i++] = Input[p++]; // A窗口处理完毕，将处理结果放入输出数组

        if (isOdd(t)) //奇数时刻，B窗口不处理
        {
            continue;
        }

        for (; q < N && !isEven(Input[q]); q++) //找到下一个偶数
        {
        }

        if (q != N)
            Output[i++] = Input[q++]; // B窗口处理完毕，将处理结果放入输出数组
    }
}

void Bank::DisplayOutput() const
{
    for (int i = 0; i < N; i++)
    {
        std::cout << Output[i];
        if (i != N - 1)
            std::cout << " ";
    }
}

bool Bank::isOdd(int num) const
{
    return num % 2;
}

bool Bank::isEven(int num) const
{
    return !isOdd(num);
}