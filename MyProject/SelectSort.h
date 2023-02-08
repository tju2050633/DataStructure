#pragma once
#include "sort.h"

class SelectSort : public Sort
{
public:
    // 构造函数
    SelectSort(MainWindow *window);

    // 初始化
    void initButtons();
    void initGraphics();

    // 排序函数
    void sort();
    void step();
};
