#include "mainwindow.h"
#include "sort.h"

void Sort::onResetClicked()
{
    if (running)
    {
        return;
    }
    if (!sorted)
    {
        // log
        window->log->setText("Not Sorted");
        return;
    }
    if (last || next)
    {
        // log
        window->log->setText("Please Complete Steps");
        return;
    }
    // log
    window->log->setText("Successfully Reset");

    // 全部矩形恢复原色
    for (int i = 0; i < data.size(); i++)
    {
        rects[i]->setOpacity(1);
    }

    steps.clear();

    reset = true;
    last = false;
    _auto = false;
    next = false;
    sort();
}

void Sort::onLastStepClicked()
{
    if (running)
    {
        return;
    }
    if (steps.isEmpty())
    {
        // log
        window->log->setText("No Last Step");
        return;
    }
    // log
    window->log->setText("Last Step");

    reset = false;
    last = true;
    _auto = false;
    next = false;

    step();
}

void Sort::onAutoClicked()
{
    if (running)
    {
        return;
    }
    if (sorted)
    {
        // log
        window->log->setText("Already Sorted");
        return;
    }
    if (last || next)
    {
        // log
        window->log->setText("Please Complete Steps");
        return;
    }
    // log
    window->log->setText("Auto");

    reset = false;
    last = false;
    _auto = true;
    next = false;
    sort();
}

void Sort::onNextStepClicked()
{
    if (running)
    {
        return;
    }
    if (sorted)
    {
        // log
        window->log->setText("No Next Step");
        return;
    }
    // log
    window->log->setText("Next Step");

    reset = false;
    last = false;
    _auto = false;
    next = true;

    step();
}

void Sort::swap_animation(int i, int j)
{
    int i_x1 = rects[i]->x();
    int j_x1 = rects[j]->x();
    int i_x2 = texts[i]->x();
    int j_x2 = texts[j]->x();

    // 交换动画
    running = true;
    for (int k = 0; k < 10; k++)
    {
        rects[i]->moveBy((j_x1 - i_x1) / 10, 0);
        rects[j]->moveBy((i_x1 - j_x1) / 10, 0);
        texts[i]->moveBy((j_x2 - i_x2) / 10, 0);
        texts[j]->moveBy((i_x2 - j_x2) / 10, 0);
        if(!_auto)
        {
            QThread::msleep(RESET_SLEEP);
        }
        else
        {
            QThread::msleep(AUTO_SLEEP);
        }
        QCoreApplication::processEvents();
    }
    running = false;

    // 交换矩形指针
    QGraphicsRectItem *tempRect = rects[i];
    rects[i] = rects[j];
    rects[j] = tempRect;

    // 交换文字指针
    QGraphicsTextItem *tempText = texts[i];
    texts[i] = texts[j];
    texts[j] = tempText;
}
