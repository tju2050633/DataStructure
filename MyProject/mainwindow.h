#include <QMainWindow>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeView>
#include <QLabel>
#include <QPushButton>
#include <QStandardItemModel>
#include <QSplitter>
#include <QStackedWidget>
#include <QMessageBox>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>

// 条目
#include "LinkedList.h"
#include "BubbleSort.h"
#include "SelectSort.h"
#include "InsertSort.h"
#include "ShellSort.h"
#include "QuickSort.h"

#define AUTO_SLEEP 50
#define RESET_SLEEP 10

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 构造函数
    MainWindow(QWidget *parent = nullptr);

    // 侧边栏部分
    void initSideBar();
    void initNavBar();
    void initContent();
    void initEntries();

    // 条目点击事件
    enum items
    {
        LinkedList,
        BinaryTree,
        DirectedGraph,
        BubbleSort,
        SelectSort,
        InsertionSort,
        ShellSort,
        QuickSort,
        Traversal,
        Huffman,
        BFS,
        DFS,
        ShortestPath,
        NeuralNetwork
    };
    void onItemClicked(const QModelIndex &index);
    bool createCanvas(items item);
    void onClickLinkedList();
    void onClickBinaryTree();
    void onClickDirectedGraph();
    //
    void onClickBubbleSort();
    void onClickSelectSort();
    void onClickInsertionSort();
    void onClickShellSort();
    void onClickQuickSort();
    //
    void onClickTraversal();
    void onClickHuffman();
    void onClickBFS();
    void onClickDFS();
    void onClickShortestPath();
    void onClickNeuralNetwork();

    // 主体部分
    void initMain();
    void initTitle();
    void initFiles();
    void initStart();
    void initRecently();
    void initAbout();
    void about();

    // 底部栏部分
    void initBottomBar();
    void initSettings();
    void initStatus();
    void initLog();

    // 布局
    QHBoxLayout *win_layout = new QHBoxLayout; // 主窗口布局
    QVBoxLayout *layout = new QVBoxLayout;     // 主窗口+底部栏布局

    // 侧边栏部分
    QTreeView *sidebar = nullptr;        // 侧边栏
    QWidget *navbar = nullptr;           // 导航栏
    QPushButton *button = nullptr;       // 导航栏按钮
    QStandardItemModel *model = nullptr; // 侧边栏模型

    // 画布
    bool canvasCreated[14] = {false};
    QGraphicsView *view = nullptr;
    QGraphicsScene *scenes[14] = {nullptr};
    QGraphicsRectItem *rects[14] = {nullptr};
    
    // 数据结构
    class LinkedList *linkedlist = nullptr;

    class BubbleSort *bubblesort = nullptr;
    class SelectSort *selectsort = nullptr;
    class InsertionSort *insertionsort = nullptr;
    class ShellSort *shellsort = nullptr;
    class QuickSort *quicksort = nullptr;


    // 主体部分
    QWidget *mainContainer = nullptr;       // 主体
    QWidget *mainBottomContainer = nullptr; // 主体底部

    // 标题部分
    QWidget *titleContainer = nullptr; // 标题容器

    // 文件部分
    QWidget *fileContainer = nullptr;     // 文件
    QWidget *startContainer = nullptr;    // 开始
    QWidget *recentlyContainer = nullptr; // 最近打开

    // 关于部分
    QWidget *aboutContainer = nullptr; // 关于

    // 底部栏部分
    QWidget *bottomBarContainer = nullptr; // 底部栏
    QPushButton *settings = nullptr;       // 设置按钮
    QLabel *status = nullptr;              // 状态栏
    QLabel *log = nullptr;                 // 输出栏
};
