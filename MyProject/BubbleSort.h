#pragma once
#include "sort.h"

class BubbleSort : public Sort
{
public:
    // 构造函数
    BubbleSort(MainWindow *window);

    // 初始化
    void initButtons();
    void initGraphics();

    // 排序函数
    void sort();
    void step();
};
