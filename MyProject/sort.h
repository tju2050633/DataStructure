#pragma once
#include <QObject>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QStandardItemModel>
#include <QAbstractButton>
#include <QMouseEvent>
#include <QCursor>
#include <QTime>
#include <QAbstractAnimation>
#include <QAnimationGroup>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>
#include <QPainter>
#include <QPair>
#include <QStack>

class MainWindow;
class Sort : public QGraphicsView
{
public:
    // 排序数组数据
    QList<int> data = {10, 5, 3, 7, 2, 9, 4, 8, 6, 1};
    QList<int> current_state;
    QStack<QPair<int, int>> steps;
    QList<QBrush> colors = {
        QBrush(Qt::red),
        QBrush(Qt::green),
        QBrush(Qt::blue),
        QBrush(Qt::cyan),
        QBrush(Qt::magenta),
        QBrush(Qt::yellow),
        QBrush(Qt::darkRed),
        QBrush(Qt::darkGreen),
        QBrush(Qt::darkBlue),
        QBrush(Qt::darkCyan)};
    QList<QGraphicsRectItem *> rects;
    QList<QGraphicsTextItem *> texts;

    // 坐标
    int orig_x = 0;
    int orig_y = 0;
    int width = 0;
    int height = 0;

    // 上级组件指针
    MainWindow *window;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;

    // 按钮
    QPushButton *btnReset;
    QPushButton *btnLastStep;
    QPushButton *btnAuto;
    QPushButton *btnNextStep;

    // 按钮点击事件
    void onResetClicked();
    void onLastStepClicked();
    void onAutoClicked();
    void onNextStepClicked();

    // 排序函数
    bool reset;
    bool last;
    bool _auto;
    bool next;
    bool sorted = false;
    bool running = false;
    virtual void sort() = 0;
    virtual void step() = 0;
    void swap_animation(int i, int j);
};
