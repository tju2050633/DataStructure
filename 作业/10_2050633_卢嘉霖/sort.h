#pragma once
#include <cstdlib>
#include <time.h>
#include <cstring>

//记录排序比较次数和交换次数
struct info
{
    long long move;
    long long compare;
    info() : move(0), compare(0) {}
};

// 交换函数
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// 1.冒泡排序
void BubbleSort(int *array, int num, info &info)
{
    bool flag = true;
    for (int i = num - 1; i >= 0 && flag; --i)
    {
        flag = false;
        for (int j = 0; j < i; ++j)
        {
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
                info.move += 3;
                flag = true;
            }
            info.compare++;
        }
    }
}

// 2.选择排序
void SelectSort(int *array, int num, info &info)
{
    for (int i = 0; i < num; ++i)
    {
        int min = i;
        for (int j = i + 1; j < num; ++j)
        {
            if (array[j] < array[min])
                min = j;
            info.compare++;
        }
        if (min != i)
        {
            swap(array[i], array[min]);
            info.move += 3;
        }
    }
}

// 3.直接插入排序
void StraightInsertionSort(int *array, int num, info &info)
{
    for (int i = 1; i < num; i++)
    {
        int temp = array[i];
        info.move++;
        int j = i;
        while (j > 0 && (info.compare++, temp < array[j - 1]))
        {
            array[j] = array[j - 1];
            info.move++;
            j--;
        }
        array[j] = temp;
        info.move++;
    }
}

// 4.希尔排序
void ShellSort(int *array, int num, info &info)
{
    int gap = 1;
    while (gap < num / 3)
        gap = 3 * gap + 1;
    while (gap)
    {
        for (int i = gap; i < num; i++)
        {
            int temp = array[i];
            info.move++;
            int j = i;
            while (j >= gap && (info.compare++, temp < array[j - gap]))
            {
                array[j] = array[j - gap];
                info.move++;
                j -= gap;
            }
            array[j] = temp;
            info.move++;
        }
        gap /= 3;
    }
}

// 5.快速排序
void q_sort(int *array, int low, int high, info &info)
{
    if (high - low < 2)
        return;
    int i = low, j = high - 1;
    int mid = (i + j) / 2, k = i;
    if (array[mid] < array[k])
        k = mid;
    if (array[j] < array[k])
        k = j;
    if (k != j)
        swap(array[k], array[j]);
    if (array[mid] < array[i])
        swap(array[mid], array[i]);

    int pivot = array[i];
    while (i != j)
    {
        while (i < j && (++info.compare, array[j] >= pivot))
            j--;
        array[i] = array[j];
        ++info.move;
        while (i < j && (++info.compare, array[i] <= pivot))
            i++;
        array[j] = array[i];
        ++info.move;
    }
    array[i] = pivot;
    ++info.move;
    q_sort(array, low, i, info);
    q_sort(array, i + 1, high, info);
}

void QuickSort(int *array, int num, info &info)
{
    q_sort(array, 0, num, info);
}

// 6.堆排序
void fixHeap(int *heap, int end, int i, info &info)
{
    int child = 2 * i + 1;
    while (child < end)
    {
        if (child + 1 < end)
        {
            info.compare++;
            if (heap[child] < heap[child + 1])
                child++;
        }
        info.compare++;
        if (heap[i] > heap[child])
            break;
        swap(heap[i], heap[child]);
        info.move += 3;
        i = child;
        child = 2 * i + 1;
    }
}

void HeapSort(int *array, int num, info &info)
{
    for (int i = (num - 2) / 2; i >= 0; i--)
        fixHeap(array, num, i, info);

    for (int i = num - 1; i >= 1; i--)
    {
        swap(array[i], array[0]);
        info.move += 3;
        fixHeap(array, i, 0, info);
    }
}

// 7.归并排序
void merge(int *array, int low, int mid, int high, int *temp, info &info)
{
    for (int k = low; k < high; k++)
    {
        temp[k] = array[k];
        ++info.move;
    }
    int i = low, j = mid;
    for (int k = low; k < high; k++)
    {
        if (i >= mid)
            array[k] = temp[j++];
        else if (j >= high)
            array[k] = temp[i++];
        else
        {
            ++info.compare;
            if (temp[j] < temp[i])
                array[k] = temp[j++];
            else
                array[k] = temp[i++];
        }
        ++info.move;
    }
}

void m_sort(int *array, int low, int high, int *temp, info &info)
{
    if (high - low <= 1)
        return;
    int mid = (low + high) / 2;
    m_sort(array, low, mid, temp, info);
    m_sort(array, mid, high, temp, info);
    merge(array, low, mid, high, temp, info);
}

void mergeSort(int *array, int num, info &info)
{
    int *temp = new int[num];
    m_sort(array, 0, num, temp, info);
    delete[] temp;
}

// 8.基数排序
const int radix = 16;

int getDigitBase16(int x, int d)
{
    return x >> (d << 2) & 0xF;
}

void _MSDRadixSort(int *array, int low, int high, int d, info &info)
{
    const int n = high - low;
    if (n <= 1 || d < 0)
        return;
    int *aux = new int[n];
    int *count = new int[radix];
    memset(count, 0, radix * sizeof(int));
    for (int i = low; i < high; i++)
        count[getDigitBase16(array[i], d)]++;
    for (int i = 1; i < radix; i++)
        count[i] += count[i - 1]; //前缀和
    for (int i = low; i < high; i++)
        aux[--count[getDigitBase16(array[i], d)]] = array[i];
    memcpy(array + low, aux, n * sizeof(int));
    info.move += 2 * n; //
    for (int i = 0; i < radix; i++)
    {
        _MSDRadixSort(array, low + count[i],
                      low + (i == radix - 1 ? n : count[i + 1]), d - 1,
                      info); //递归
    }
    delete[] count;
    delete[] aux;
}

void MSDRadixSort(int *array, int num, info &info)
{
    int max = -1000000000, maxd = -1;
    for (int i = 0; i < num; i++)
        if (array[i] > max)
            max = array[i];
    while (max)
    {
        max >>= 4;
        maxd++;
    }
    _MSDRadixSort(array, 0, num, maxd, info);
}