#pragma once
#include <QObject>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QAbstractButton>
#include <QMouseEvent>
#include <QCursor>

struct Node
{
    QString text;                 // 文本
    Node *next;                   // 下一个节点
    QGraphicsEllipseItem *entity; // 圆
};

class MainWindow;
class LinkedList : public QGraphicsView
{
private:
    // 链表数据
    bool isCreated = false; // 是否创建
    Node *head;             // 头指针
    int length;             // 链表长度
    QList<Node *> nodes;    // 节点数组
    char new_node_text;     // 文本

    // 控制信号
    bool readyToInsert = false; // 是否准备插入
    bool readyToDelete = false; // 是否准备删除

    // 成员函数
    QGraphicsEllipseItem *drawNode(int x, int y, QString text);             // 创建节点
    void drawArrow(QGraphicsEllipseItem *start, QGraphicsEllipseItem *end); // 创建箭头

public:
    // 构造函数
    LinkedList(MainWindow *window);

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
    QPushButton *btnCreate;
    QPushButton *btnInsert;
    QPushButton *btnDelete;

    // 初始化按钮
    void initButtons();

    // 按钮点击事件
    void onCreateClicked();
    void onInsertClicked();
    void onDeleteClicked();

    // 鼠标点击事件
    void mousePressEvent(QMouseEvent *event);
};
