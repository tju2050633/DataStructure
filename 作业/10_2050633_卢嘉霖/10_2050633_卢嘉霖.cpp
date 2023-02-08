#include "sort.h"
#include <iostream>
#include <algorithm>

void Welcome()
{
    std::cout << "**                    �����㷨�Ƚ�                    **\n";
    std::cout << "========================================================\n";
    std::cout << "**                  1 --- ð������                    **\n";
    std::cout << "**                  2 --- ѡ������                    **\n";
    std::cout << "**                  3 --- ֱ�Ӳ�������                **\n";
    std::cout << "**                  5 --- ϣ������                    **\n";
    std::cout << "**                  6 --- ��������                    **\n";
    std::cout << "**                  7 --- �鲢����                    **\n";
    std::cout << "**                  8 --- ��������                    **\n";
    std::cout << "**                  9 --- �˳�����                    **\n";
    std::cout << "========================================================\n";
}

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

void ShowSortInfo(const char *sequence_type, int *array, int num, void (*sortfunc)(int *, int, info &))
{
    // ��������
    int *copy = new int[num];
    memcpy(copy, array, num * sizeof(int));

    // ���򣬼�ʱ
    info info;
    clock_t start = clock();
    sortfunc(copy, num, info);

    // ������
    printf("%-15s", sequence_type);
    printf("\t%10gms", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
    printf("\t%15lld", info.compare);
    printf("\t%15lld\n", info.move);

    delete[] copy;
}

// �����������
void GenerateRandomArray(int *arrays, int num)
{
    for (int i = 0; i < num; ++i)
        arrays[i] = rand() % num;
}

// ������������
void GenerateAscendingArray(int *arrays, int num)
{
    for (int i = 0; i < num; ++i)
        arrays[i] = i;
}

// ���ɽ�������
void GenerateDescendingArray(int *arrays, int num)
{
    for (int i = 0; i < num; ++i)
        arrays[i] = num - i;
}

// ���ɽ�����������
void GenerateNearlyAscendArray(int *arrays, int num)
{
    for (int i = 0; i < num; ++i)
        arrays[i] = i;
    for (int i = 0; i < num / 10; ++i)
        std::swap(arrays[rand() % num], arrays[rand() % num]);
}

// ���ɴ����ظ�����
void GenerateManySameArray(int *arrays, int num)
{
    for (int i = 0; i < num; ++i)
        arrays[i] = rand() % 10;
}

void ShowTable(const char *algorithm, int *array, int num, void (*func)(int *, int, info &))
{
    std::cout << "===============================================================\n";
    std::cout << "**                         " << algorithm << "                          **\n";
    std::cout << "===============================================================\n";
    std::cout << "��������                ʱ��           �Ƚϴ���        �ƶ�����\n";
    GenerateRandomArray(array, num);
    ShowSortInfo("��ȫ�������", array, num, func);

    GenerateAscendingArray(array, num);
    ShowSortInfo("�ϸ���������", array, num, func);

    GenerateDescendingArray(array, num);
    ShowSortInfo("�ϸ�������", array, num, func);

    GenerateNearlyAscendArray(array, num);
    ShowSortInfo("������������", array, num, func);

    GenerateManySameArray(array, num);
    ShowSortInfo("�����ظ�����", array, num, func);
}

int main()
{
    Welcome();

    srand((unsigned int)time(NULL));
    int *array;
    int num = GetInt("������Ҫ������������ĸ�����", 1, 100000);
    array = new int[num];

    char option;
    while (true)
    {
        option = GetInt("\n��ѡ�������㷨��", 1, 9);
        switch (option)
        {
        case 1:
            ShowTable("ð������", array, num, BubbleSort);
            break;
        case 2:
            ShowTable("ѡ������", array, num, SelectSort);
            break;
        case 3:
            ShowTable("ֱ�Ӳ�������", array, num, StraightInsertionSort);
            break;
        case 4:
            ShowTable("ϣ������", array, num, ShellSort);
            break;
        case 5:
            ShowTable("��������", array, num, QuickSort);
            break;
        case 6:
            ShowTable("������", array, num, HeapSort);
            break;
        case 7:
            ShowTable("�鲢����", array, num, mergeSort);
            break;
        case 8:
            ShowTable("��������", array, num, MSDRadixSort);
            break;
        case 9:
            delete[] array;
            return 0;
        default:
            std::cout << "�����������������" << std::endl;
            break;
        }
    }

    return 0;
}