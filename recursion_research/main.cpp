#include <iostream>
#include "bi_tree.h"
#include "my_stl.h"
#include <time.h>

using namespace std;

#define REPEAT 20

// 斐波那契数列递归算法
int rec_Fibonacci(int n)
{
    if (n == 1 || n == 2)
        return 1;
    else
        return rec_Fibonacci(n - 1) + rec_Fibonacci(n - 2);
}

// 斐波那契数列非递归算法
int unrec_Fibonacci(int n)
{
    int a = 1, b = 1, c = 1;
    for (int i = 3; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

// 阶乘递归算法
int rec_factorial(int n)
{
    if (n == 1)
        return 1;
    else
        return n * rec_factorial(n - 1);
}

// 阶乘非递归算法
int unrec_factorial(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++)
        result *= i;
    return result;
}

// 幂运算递归算法
int rec_power(int x, int n)
{
    if (n == 0)
        return 1;
    else
        return x * rec_power(x, n - 1);
}

// 幂运算非递归算法
int unrec_power(int x, int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++)
        result *= x;
    return result;
}

// 快速排序递归算法
void rec_quickSort(int *arr, int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = right, pivot = arr[left];
    while (i < j)
    {
        while (i < j && arr[j] >= pivot)
            j--;
        if (i < j)
            arr[i++] = arr[j];
        while (i < j && arr[i] <= pivot)
            i++;
        if (i < j)
            arr[j--] = arr[i];
    }
    arr[i] = pivot;
    rec_quickSort(arr, left, i - 1);
    rec_quickSort(arr, i + 1, right);
}

// 快速排序非递归算法
void unrec_quickSort(int *arr, int left, int right)
{
    my_std::stack<int> s;
    s.push(left);
    s.push(right);
    while (!s.empty())
    {
        int r = s.top();
        s.pop();
        int l = s.top();
        s.pop();
        int i = l, j = r, pivot = arr[l];
        while (i < j)
        {
            while (i < j && arr[j] >= pivot)
                j--;
            if (i < j)
                arr[i++] = arr[j];
            while (i < j && arr[i] <= pivot)
                i++;
            if (i < j)
                arr[j--] = arr[i];
        }
        arr[i] = pivot;
        if (i - 1 > l)
        {
            s.push(l);
            s.push(i - 1);
        }
        if (i + 1 < r)
        {
            s.push(i + 1);
            s.push(r);
        }
    }
}

int main()
{
    clock_t start;
    clock_t end;
    // 斐波那契数列
    if (0)
    {
        cout << "===============================================================\n";
        cout << "**                       " << "斐波那契数列" << "                        **\n";
        cout << "===============================================================\n";
        printf("%-15s%-20s%-19s%s\n", "index", "递归时间(ms)", "非递归时间(ms)", "比值");

        // 不同数据规模
        int test_index[5] = {5, 10, 20, 30, 40};

        for(int i = 0; i < 5; i++)
        {
            // 测试的索引
            int index= test_index[i];

            // 递归算法
            start = clock();
            for (int j = 0; j < REPEAT; j++)
            {
                rec_Fibonacci(index);
            }
            end = clock();
            long double rec_time = (long double)(end - start) / CLOCKS_PER_SEC * 1000 / REPEAT;


            // 非递归算法
            start = clock();
            for (int j = 0; j < REPEAT; j++)
            {
                unrec_Fibonacci(index);
            }
            end = clock();
            long double unrec_time = (long double)(end - start) / CLOCKS_PER_SEC * 1000 / REPEAT;

            float ratio = rec_time / unrec_time;

            // 打印
            printf("%-15d%-16Lg%-15Lg%.2f\n", index, rec_time, unrec_time, ratio);
        }
    }

    // 阶乘
    if (0)
    {
        cout << "===============================================================\n";
        cout << "**                           " << "阶乘" << "                            **\n";
        cout << "===============================================================\n";
        printf("%-18s%-20s%-20s%s\n", "阶乘数", "递归时间(ms)", "非递归时间(ms)", "比值");

        // 不同数据规模
        int test_n[5] = {10, 20, 30, 40, 50};

        for(int i = 0; i < 5; i++)
        {
            // 测试的阶乘数
            int n = test_n[i];

            // 递归算法
            start = clock();
            for (int j = 0; j < REPEAT; j++)
            {
                rec_factorial(n);
            }
            end = clock();
            long double rec_time = (long double)(end - start) / CLOCKS_PER_SEC * 1000 / REPEAT;

            // 非递归算法
            start = clock();
            for (int j = 0; j < REPEAT; j++)
            {
                unrec_factorial(n);
            }
            end = clock();
            long double unrec_time = (long double)(end - start) / CLOCKS_PER_SEC * 1000 / REPEAT;

            float ratio = rec_time / unrec_time;

            // 打印
            printf("%-15d%-16Lg%-15Lg%.2f\n", n, rec_time, unrec_time, ratio);
        }
    }

    // 幂运算
    if (0)
    {
        cout << "===============================================================\n";
        cout << "**                           " << "幂运算" << "                          **\n";
        cout << "===============================================================\n";
        printf("%-17s%-20s%-20s%s\n", "指数", "递归时间(ms)", "非递归时间(ms)", "比值");

        // 不同数据规模
        int test_n[5] = {10, 20, 30, 40, 50};

        for(int i = 0; i < 5; i++)
        {
            // 测试的底数和指数
            int x = 2;
            int n = test_n[i];

            // 递归算法
            start = clock();
            for (int j = 0; j < REPEAT; j++)
            {
                rec_power(x, n);
            }
            end = clock();
            long double rec_time = (long double)(end - start) / CLOCKS_PER_SEC * 1000 / REPEAT;

            // 非递归算法
            start = clock();
            for (int j = 0; j < REPEAT; j++)
            {
                unrec_power(x, n);
            }
            end = clock();
            long double unrec_time = (long double)(end - start) / CLOCKS_PER_SEC * 1000 / REPEAT;

            float ratio = rec_time / unrec_time;

            // 打印
            printf("%-15d%-16Lg%-15Lg%.2f\n", n, rec_time, unrec_time, ratio);
        }
    }

    // 二叉树的后序遍历
    if (0)
    {
        cout << "===============================================================\n";
        cout << "**                          " << "后序遍历" << "                         **\n";
        cout << "===============================================================\n";
        printf("%-19s%-20s%-20s%s\n", "结点个数", "递归时间(ms)", "非递归时间(ms)", "比值");

        // 不同数据规模
        int test_n[5] = {10, 100, 1000, 10000, 100000};

        for(int i = 0; i < 5; i++)
        {
            // 测试的节点数
            int n = test_n[i];

            // 生成树
            BiTree T;
            T.createBiTree(n);  // n个节点

            // 递归算法
            start = clock();
            for (int j = 0; j < REPEAT; j++)
            {
                T.rec_PostOrder();
            }
            end = clock();
            long double rec_time = (long double)(end - start) / CLOCKS_PER_SEC * 1000 / REPEAT;

            // 非递归算法
            start = clock();
            for (int j = 0; j < REPEAT; j++)
            {
                T.unrec_PostOrder();
            }
            end = clock();
            long double unrec_time = (long double)(end - start) / CLOCKS_PER_SEC * 1000 / REPEAT;

            float ratio = rec_time / unrec_time;

            // 打印
            printf("%-15d%-16Lg%-15Lg%.2f\n", n, rec_time, unrec_time, ratio);
        }
    }

    // 快速排序
    if (0)
    {
        cout << "===============================================================\n";
        cout << "**                          " << "快速排序" << "                         **\n";
        cout << "===============================================================\n";
        printf("%-19s%-20s%-20s%s\n", "列表长度", "递归时间(ms)", "非递归时间(ms)", "比值");

        // 不同数据规模
        int test_n[5] = {5, 10, 100, 1000, 10000};

        for(int i = 0; i < 5; i++)
        {
            // 测试的列表长度
            int n = test_n[i];

            // 生成数组
            int *arr = new int[n];
            for (int j = 0; j < n; j++)
            {
                arr[j] = rand() % 100;
            }

            // 递归算法
            start = clock();
            for (int j = 0; j < REPEAT; j++)
            {
                rec_quickSort(arr, 0, n - 1);
            }
            end = clock();
            long double rec_time = (long double)(end - start) / CLOCKS_PER_SEC * 1000 / REPEAT;

            // 非递归算法
            start = clock();
            for (int j = 0; j < REPEAT; j++)
            {
                unrec_quickSort(arr, 0, n - 1);
            }
            end = clock();
            long double unrec_time = (long double)(end - start) / CLOCKS_PER_SEC * 1000 / REPEAT;

            float ratio = rec_time / unrec_time;

            // 打印
            printf("%-15d%-16Lg%-15Lg%.2f\n", n, rec_time, unrec_time, ratio);
        }
    }

    return 0;
}