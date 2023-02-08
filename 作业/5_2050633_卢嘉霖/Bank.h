#pragma once
#include <iostream>
#include "my_stl.h"

class Bank
{
private:
    my_std::vector<int> Input;
    my_std::vector<int> Output;
    int N; //��������������
    int t; //��ʾ����ҵ���ʱ��
    int p; //��ָ�룬��ʾA����
    int q; //��ָ�룬��ʾB����
    int i; //�����������

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

void Bank::GetInput() //��ȡ����������
{
    while (true)
    {
        std::cin >> N;
        if (!std::cin || N < 1 || N > 1000)
        {
            std::cout << "����������������룡\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        else
            break;
    }

    Input = my_std::vector<int>(N);
    Output = my_std::vector<int>(N);

    for (int i = 0; i < N; i++) //��ȡ��������
    {
        while (true)
        {
            std::cin >> Input[i];
            if (!std::cin || Input[i] < 1)
            {
                std::cout << "����������������룡\n";
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
        t++; // t����ʱ��

        for (; p < N && !isOdd(Input[p]); p++) //�ҵ���һ������
        {
        }

        if (p != N)
            Output[i++] = Input[p++]; // A���ڴ�����ϣ��������������������

        if (isOdd(t)) //����ʱ�̣�B���ڲ�����
        {
            continue;
        }

        for (; q < N && !isEven(Input[q]); q++) //�ҵ���һ��ż��
        {
        }

        if (q != N)
            Output[i++] = Input[q++]; // B���ڴ�����ϣ��������������������
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