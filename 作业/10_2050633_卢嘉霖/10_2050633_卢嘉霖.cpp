#include "sort.h"
#include <iostream>
#include <algorithm>

void Welcome()
{
    std::cout << "**                    排序算法比较                    **\n";
    std::cout << "========================================================\n";
    std::cout << "**                  1 --- 冒泡排序                    **\n";
    std::cout << "**                  2 --- 选择排序                    **\n";
    std::cout << "**                  3 --- 直接插入排序                **\n";
    std::cout << "**                  5 --- 希尔排序                    **\n";
    std::cout << "**                  6 --- 快速排序                    **\n";
    std::cout << "**                  7 --- 归并排序                    **\n";
    std::cout << "**                  8 --- 基数排序                    **\n";
    std::cout << "**                  9 --- 退出程序                    **\n";
    std::cout << "========================================================\n";
}

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

void ShowSortInfo(const char *sequence_type, int *array, int num, void (*sortfunc)(int *, int, info &))
{
    // 产生副本
    int *copy = new int[num];
    memcpy(copy, array, num * sizeof(int));

    // 排序，计时
    info info;
    clock_t start = clock();
    sortfunc(copy, num, info);

    // 输出结果
    printf("%-15s", sequence_type);
    printf("\t%10gms", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
    printf("\t%15lld", info.compare);
    printf("\t%15lld\n", info.move);

    delete[] copy;
}

// 生成随机序列
void GenerateRandomArray(int *arrays, int num)
{
    for (int i = 0; i < num; ++i)
        arrays[i] = rand() % num;
}

// 生成升序序列
void GenerateAscendingArray(int *arrays, int num)
{
    for (int i = 0; i < num; ++i)
        arrays[i] = i;
}

// 生成降序序列
void GenerateDescendingArray(int *arrays, int num)
{
    for (int i = 0; i < num; ++i)
        arrays[i] = num - i;
}

// 生成近乎有序序列
void GenerateNearlyAscendArray(int *arrays, int num)
{
    for (int i = 0; i < num; ++i)
        arrays[i] = i;
    for (int i = 0; i < num / 10; ++i)
        std::swap(arrays[rand() % num], arrays[rand() % num]);
}

// 生成大量重复序列
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
    std::cout << "序列类型                时间           比较次数        移动次数\n";
    GenerateRandomArray(array, num);
    ShowSortInfo("完全随机序列", array, num, func);

    GenerateAscendingArray(array, num);
    ShowSortInfo("严格升序序列", array, num, func);

    GenerateDescendingArray(array, num);
    ShowSortInfo("严格降序序列", array, num, func);

    GenerateNearlyAscendArray(array, num);
    ShowSortInfo("近乎有序序列", array, num, func);

    GenerateManySameArray(array, num);
    ShowSortInfo("大量重复序列", array, num, func);
}

int main()
{
    Welcome();

    srand((unsigned int)time(NULL));
    int *array;
    int num = GetInt("请输入要产生的随机数的个数：", 1, 100000);
    array = new int[num];

    char option;
    while (true)
    {
        option = GetInt("\n请选择排序算法：", 1, 9);
        switch (option)
        {
        case 1:
            ShowTable("冒泡排序", array, num, BubbleSort);
            break;
        case 2:
            ShowTable("选择排序", array, num, SelectSort);
            break;
        case 3:
            ShowTable("直接插入排序", array, num, StraightInsertionSort);
            break;
        case 4:
            ShowTable("希尔排序", array, num, ShellSort);
            break;
        case 5:
            ShowTable("快速排序", array, num, QuickSort);
            break;
        case 6:
            ShowTable("堆排序", array, num, HeapSort);
            break;
        case 7:
            ShowTable("归并排序", array, num, mergeSort);
            break;
        case 8:
            ShowTable("基数排序", array, num, MSDRadixSort);
            break;
        case 9:
            delete[] array;
            return 0;
        default:
            std::cout << "输入错误，请重新输入" << std::endl;
            break;
        }
    }

    return 0;
}