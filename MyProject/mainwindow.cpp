#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 初始化模块
    initSideBar();
    initMain();
    initBottomBar();

    // 侧边栏+主体
    QWidget *mainWidget = new QWidget;
    win_layout->setContentsMargins(0, 0, 0, 0);
    win_layout->setSpacing(0);
    mainWidget->setLayout(win_layout);

    // 将侧边栏和主体添加到主窗口布局中
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(mainWidget);
    layout->addWidget(bottomBarContainer);

    // 将主窗口布局设置为主窗口的布局
    QWidget *centerWidget = new QWidget;
    centerWidget->setLayout(layout);
    setCentralWidget(centerWidget);

    // test
    //  onClickLinkedList();
}

// 侧边栏部分

void MainWindow::initSideBar()
{
    // 初始化侧边栏
    initNavBar();
    initContent();
    initEntries();
}

void MainWindow::initNavBar()
{
    /* 导航栏 */

    // 包含一个按钮的导航栏
    navbar = new QWidget;

    // 背景颜色和去除圆角
    QString styleSheet1 =
        "QWidget { border-radius: 0px; }"
        "QWidget { background-color: #2c2c2c; }";
    navbar->setStyleSheet(styleSheet1);

    // 创建一个垂直布局
    QVBoxLayout *navbarLayout = new QVBoxLayout;
    navbarLayout->setContentsMargins(0, 10, 0, 0);

    // 创建一个按钮，用来显示侧边栏
    button = new QPushButton;
    button->setCursor(Qt::PointingHandCursor);

    // 图标
    QPixmap pixmap(":/icons/entries.svg"); // 导入按钮的图标

    // 设置图标颜色
    QPixmap newPixmap = pixmap.copy();
    QPainter painter(&newPixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(newPixmap.rect(), QColor("#fff")); // 设置图标颜色为蓝色
    painter.end();

    button->setIcon(QIcon(newPixmap));

    // 添加按钮到布局中
    navbarLayout->addWidget(button);

    // 将布局设置为导航栏的布局
    navbar->setLayout(navbarLayout);

    // 将导航栏添加到布局中
    win_layout->addWidget(navbar);

    // 设置导航栏固定宽度
    navbar->setFixedWidth(50);

    // 设置按钮固定在导航栏的顶部
    navbarLayout->setAlignment(button, Qt::AlignTop);
}

void MainWindow::initContent()
{
    /* 侧边栏 */

    // 创建文件资源管理的侧边栏
    sidebar = new QTreeView;
    sidebar->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止条目被编辑

    // 定义侧边栏点击事件
    connect(sidebar, &QTreeView::doubleClicked, [this](const QModelIndex &index)
            { onItemClicked(index); });

    // 隐藏侧边栏的标题（原生样式）
    sidebar->setHeaderHidden(true);

    // 创建一个模型，用于管理文件资源管理的选项
    model = new QStandardItemModel;

    // 将模型设置为侧边栏的模型
    sidebar->setModel(model);

    // 将侧边栏添加到布局中
    win_layout->addWidget(sidebar);

    // 侧边栏设置固定宽度
    sidebar->setFixedWidth(170);

    // 背景颜色和去除圆角
    QString styleSheet =
        "QWidget { border-radius: 0px; }"
        "QWidget { background-color: #f3f3f3; }";
    sidebar->setStyleSheet(styleSheet);

    // 设置侧边栏的可见性为false
    sidebar->setVisible(true);

    // 为按钮添加点击事件
    connect(button, &QPushButton::clicked, [=]()
            {
        // 切换侧边栏的可见性
        if(sidebar->isVisible())
        {
            sidebar->setVisible(false);
            log->setText("Sidebar Hidden");
        }
        else
        {
            sidebar->setVisible(true);
            log->setText("Sidebar Shown");
        } });
}

void MainWindow::initEntries()
{
    // 导入图标
    QPixmap folder(":/icons/folder1.svg");
    QPixmap file(":/icons/file1.svg");
    sidebar->setIconSize(folder.size());

    /* 一级项目 */

    // 创建两个项目，用于表示数据结构，算法
    QStandardItem *ds = new QStandardItem("Data Structure");
    QStandardItem *alg = new QStandardItem("Algorithm");

    // 图标
    ds->setIcon(QIcon(folder));
    alg->setIcon(QIcon(folder));

    // 将这两个项目添加到模型中
    model->appendRow(ds);
    model->appendRow(alg);

    /* 二级项目 */
    QStandardItem *ll = new QStandardItem("Linked List");
    QStandardItem *t = new QStandardItem("Binary Tree");
    QStandardItem *g = new QStandardItem("Directed Graph");

    QStandardItem *sort = new QStandardItem("Sort");
    QStandardItem *t_alg = new QStandardItem("Tree");
    QStandardItem *g_alg = new QStandardItem("Graph");
    QStandardItem *nn = new QStandardItem("Neural Network");

    // 图标
    ll->setIcon(QIcon(file));
    t->setIcon(QIcon(file));
    g->setIcon(QIcon(file));

    sort->setIcon(QIcon(folder));
    t_alg->setIcon(QIcon(folder));
    g_alg->setIcon(QIcon(folder));
    nn->setIcon(QIcon(file));

    // 数据结构项目添加子项目链表，树，图
    ds->appendRow(ll);
    ds->appendRow(t);
    ds->appendRow(g);

    // 算法项目添加子项目排序，树，图，神经网络
    alg->appendRow(sort);
    alg->appendRow(t_alg);
    alg->appendRow(g_alg);
    alg->appendRow(nn);

    /* 三级项目 */ //////////////////////////////
    QStandardItem *item10 = new QStandardItem("Bubble Sort");
    QStandardItem *item11 = new QStandardItem("Select Sort");
    QStandardItem *item12 = new QStandardItem("Insertion Sort");
    QStandardItem *item18 = new QStandardItem("Shell Sort");
    QStandardItem *item19 = new QStandardItem("Quick Sort");
    ////////////////////////////////////////////

    QStandardItem *item13 = new QStandardItem("Traversal");
    QStandardItem *item14 = new QStandardItem("Huffman");

    QStandardItem *item15 = new QStandardItem("BFS");
    QStandardItem *item16 = new QStandardItem("DFS");
    QStandardItem *item17 = new QStandardItem("Shortest Path");

    // 图标////////////////////////////////////////////
    item10->setIcon(QIcon(file));
    item11->setIcon(QIcon(file));
    item12->setIcon(QIcon(file));
    item18->setIcon(QIcon(file));
    item19->setIcon(QIcon(file));
    ////////////////////////////////////////////

    item13->setIcon(QIcon(file));
    item14->setIcon(QIcon(file));

    item15->setIcon(QIcon(file));
    item16->setIcon(QIcon(file));
    item17->setIcon(QIcon(file));

    // 排序项目////////////////////////////////////////////
    sort->appendRow(item10);
    sort->appendRow(item11);
    sort->appendRow(item12);
    sort->appendRow(item18);
    sort->appendRow(item19);
    ////////////////////////////////////////////

    // 树项目添加子项目遍历，哈夫曼
    t_alg->appendRow(item13);
    t_alg->appendRow(item14);

    // 图项目添加子项目BFS，DFS，最短路径
    g_alg->appendRow(item15);
    g_alg->appendRow(item16);
    g_alg->appendRow(item17);
}

// 条目点击事件
void MainWindow::onItemClicked(const QModelIndex &index)
{
    QStandardItem *item = model->itemFromIndex(index);
    QString text = item->text();

    // 根据条目的文本，切换主体部分的内容
    if (text == "Linked List")
        onClickLinkedList();
    else if (text == "Binary Tree")
        onClickBinaryTree();
    else if (text == "Directed Graph")
        onClickDirectedGraph();
    else if (text == "Bubble Sort")
        onClickBubbleSort();
    else if (text == "Select Sort")
        onClickSelectSort();
    else if (text == "Insertion Sort")
        onClickInsertionSort();
    else if (text == "Shell Sort")
        onClickShellSort();
    else if (text == "Quick Sort")
        onClickQuickSort();
    else if (text == "Traversal")
        onClickTraversal();
    else if (text == "Huffman")
        onClickHuffman();
    else if (text == "BFS")
        onClickBFS();
    else if (text == "DFS")
        onClickDFS();
    else if (text == "Shortest Path")
        onClickShortestPath();
    else if (text == "Neural Network")
        onClickNeuralNetwork();
}

bool MainWindow::createCanvas(items item)
{
    // 若已经创建过，返回
    if (canvasCreated[item])
    {
        view->setScene(scenes[item]);
        return false;
    }

    // 其他为false
    for (int i = 0; i < 12; i++)
        canvasCreated[i] = false;
    canvasCreated[item] = true;

    // 隐藏所有初始界面的主体部分
    titleContainer->hide();
    mainBottomContainer->hide();

    // 创建QGraphView
    if (!view)
    {
        view = new QGraphicsView;
        view->setRenderHint(QPainter::Antialiasing);
    }
    view->setBackgroundBrush(QBrush(QColor(230, 230, 230)));

    // 加入到主体部分
    mainContainer->layout()->addWidget(view);
    mainContainer->layout()->setContentsMargins(0, 0, 0, 0);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 去掉水平滚动条
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // 去掉垂直滚动条
    view->setGeometry(mainContainer->geometry());

    // 创建场景
    if (!scenes[item])
    {
        scenes[item] = new QGraphicsScene();
        scenes[item]->setSceneRect(mainContainer->geometry());
    }

    // 获取场景左上角坐标
    int x = scenes[item]->sceneRect().x();
    int y = scenes[item]->sceneRect().y();

    // 画一个填满view的矩形
    if (!rects[item])
    {
        QPen pen;
        pen.setColor(Qt::black);
        rects[item] = scenes[item]->addRect(x, y, scenes[item]->width() - 2, scenes[item]->height() - 2, pen);
        // 填充颜色
        QBrush brush;
        brush.setColor(Qt::white);
        brush.setStyle(Qt::SolidPattern);
        rects[item]->setBrush(brush);
    }

    // 设置场景
    view->setScene(scenes[item]);
    view->setSceneRect(220, 0, view->width(), view->height());

    return true;
}

void MainWindow::onClickLinkedList()
{
    // 隐藏原有主体部分组件，创建画布，若已存在则不执行
    if (!createCanvas(LinkedList))
        return;

    // 改变status和log
    status->setText("Linked List");
    log->setText("Successfully Entered Linked List Mode");

    // 创建链表
    if (!linkedlist)
        linkedlist = new class LinkedList(this);
}

void MainWindow::onClickBinaryTree()
{
    // 隐藏原有主体部分组件，创建画布，若已存在则不执行
    if (!createCanvas(BinaryTree))
        return;

    // 改变status和log
    status->setText("Binary Tree");
    log->setText("Successfully Entered Binary Tree Mode");
}

void MainWindow::onClickDirectedGraph()
{
    // 隐藏原有主体部分组件，创建画布，若已存在则不执行
    if (!createCanvas(DirectedGraph))
        return;

    // 改变status和log
    status->setText("Directed Graph");
    log->setText("Successfully Entered Directed Graph Mode");
}

void MainWindow::onClickBubbleSort()
{
    // 隐藏原有主体部分组件，创建画布，若已存在则不执行
    if (!createCanvas(BubbleSort))
        return;

    // 改变status和log
    status->setText("Bubble Sort");
    log->setText("Successfully Entered Bubble Sort Mode");

    // 创建
    if (!bubblesort)
        bubblesort = new class BubbleSort(this);
}

void MainWindow::onClickSelectSort()
{
    // 隐藏原有主体部分组件，创建画布，若已存在则不执行
    if (!createCanvas(SelectSort))
        return;

    // 改变status和log
    status->setText("Select Sort");
    log->setText("Successfully Entered Select Sort Mode");

    // 创建
    if (!selectsort)
        selectsort = new class SelectSort(this);
}

void MainWindow::onClickInsertionSort()
{
    // 隐藏原有主体部分组件，创建画布，若已存在则不执行
    if (!createCanvas(InsertionSort))
        return;

    // 改变status和log
    status->setText("Insertion Sort");
    log->setText("Successfully Entered Insertion Sort Mode");

    // 创建
    if (!insertionsort)
        insertionsort = new class InsertionSort(this);
}

void MainWindow::onClickShellSort()
{
    // 隐藏原有主体部分组件，创建画布，若已存在则不执行
    if (!createCanvas(ShellSort))
        return;

    // 改变status和log
    status->setText("Shell Sort");
    log->setText("Successfully Entered Shell Sort Mode");

    // 创建
    if (!shellsort)
        shellsort = new class ShellSort(this);
}

void MainWindow::onClickQuickSort()
{
    // 隐藏原有主体部分组件，创建画布，若已存在则不执行
    if (!createCanvas(QuickSort))
        return;

    // 改变status和log
    status->setText("Insertion Sort");
    log->setText("Successfully Entered Quick Sort Mode");

    // 创建
    if (!quicksort)
        quicksort = new class QuickSort(this);
}

void MainWindow::onClickTraversal()
{
}

void MainWindow::onClickHuffman()
{
}

void MainWindow::onClickBFS()
{
}

void MainWindow::onClickDFS()
{
}

void MainWindow::onClickShortestPath()
{
}

void MainWindow::onClickNeuralNetwork()
{
}

// 主体部分

void MainWindow::initMain()
{
    // 创建用于装载主体部分的容器，和装载File部分和About部分的容器
    mainContainer = new QWidget;
    mainBottomContainer = new QWidget;

    // mainContainer背景颜色
    // mainContainer->setStyleSheet("background-color: #123123;");

    // 初始化标题、文件、关于部分
    initTitle();
    initFiles();
    initAbout();

    // 创建一个垂直布局，用于管理主体部分
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleContainer);
    mainLayout->addWidget(mainBottomContainer);
    mainContainer->setLayout(mainLayout);

    // 主体底部是水平布局，含有文件和关于部分
    QHBoxLayout *mainBottomLayout = new QHBoxLayout;
    mainBottomLayout->addWidget(fileContainer);
    mainBottomLayout->addWidget(aboutContainer);
    mainBottomContainer->setLayout(mainBottomLayout);

    // 将容器添加到布局中
    win_layout->addWidget(mainContainer);
}

void MainWindow::initTitle()
{
    /* Title */

    // 主标题和副标题，装在一个容器内，固定在窗口中部靠上

    // 创建一个容器
    titleContainer = new QWidget;

    // 标题部分占窗口高度的1/3
    titleContainer->setFixedHeight(height() / 3);

    // 创建一个垂直布局
    QVBoxLayout *titleLayout = new QVBoxLayout;

    // 创建一个标签，用来显示title和subtitle
    QLabel *title = new QLabel("Visual Nodes");
    QLabel *subtitle = new QLabel("Visualized Data Structure and Algorithm, Vivid Learning");

    // 设置标签的对齐方式
    title->setAlignment(Qt::AlignLeft);
    subtitle->setAlignment(Qt::AlignLeft);

    // 设置标签的字体
    QFont font;
    font.setPointSize(40);
    font.setBold(true);
    font.setFamily("Microsoft YaHei");
    title->setFont(font);
    font.setPointSize(16);
    font.setFamily("Microsoft YaHei");
    subtitle->setFont(font);

    // 字体颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText, "#333");
    title->setPalette(pa);
    subtitle->setPalette(pa);

    // 将标签添加到布局中
    titleLayout->addWidget(title);
    titleLayout->addWidget(subtitle);

    // 将布局添加到容器中
    titleContainer->setLayout(titleLayout);

    // 设置容器的对齐方式
    titleLayout->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
}

void MainWindow::initFiles()
{
    fileContainer = new QWidget;

    initStart();
    initRecently();

    // 文件是垂直布局，含有Start和Recently两个部分
    QVBoxLayout *fileLayout = new QVBoxLayout;
    fileLayout->addWidget(startContainer);
    fileLayout->addWidget(recentlyContainer);
    fileContainer->setLayout(fileLayout);
}

void MainWindow::initStart()
{
    // start是垂直布局，含有Start标签和Create链接、Open链接
    startContainer = new QWidget;

    // start部分占窗口高度的1/3
    startContainer->setFixedHeight(fileContainer->height() / 3);

    // 设置背景颜色
    // startContainer->setStyleSheet("background-color: #aaa;");

    // 创建一个垂直布局
    QVBoxLayout *startLayout = new QVBoxLayout;

    // 创建一个标签，用来显示Start
    QLabel *start = new QLabel("Start");

    // 标签样式
    QString styleSheet1 =
        "QLabel { color: #333; }"
        "QLabel { font-size: 20px; }"
        "QLabel { font-weight: bold; }"
        "QLabel { font-family: Microsoft YaHei; }";
    start->setStyleSheet(styleSheet1);

    // 图标
    QPixmap createIcon(":/icons/file1.svg");
    QPixmap openIcon(":/icons/open.png");

    createIcon = createIcon.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    openIcon = openIcon.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 创建链接
    QPushButton *create = new QPushButton;
    QPushButton *open = new QPushButton;

    // 设置图标颜色
    QPixmap newPixmap1 = createIcon.copy();
    QPixmap newPixmap2 = openIcon.copy();
    QPainter painter1(&newPixmap1);
    QPainter painter2(&newPixmap2);
    painter1.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter2.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter1.fillRect(newPixmap1.rect(), QColor("#0D6AB2"));
    painter2.fillRect(newPixmap2.rect(), QColor("#0D6AB2"));
    painter1.end();
    painter2.end();

    // 加入图标
    create->setIcon(QIcon(newPixmap1));
    open->setIcon(QIcon(newPixmap2));

    // 加入文字
    create->setText("New File...");
    open->setText("Open File...");

    // 链接样式
    QString styleSheet2 =
        "QPushButton { color: #0D6AB2; }"
        "QPushButton { font-size: 16px; }"
        "QPushButton { border: none; }"
        "QPushButton { background-color: transparent; }";
    create->setStyleSheet(styleSheet2);
    open->setStyleSheet(styleSheet2);

    // 鼠标悬停时的样式
    create->setCursor(Qt::PointingHandCursor);
    open->setCursor(Qt::PointingHandCursor);

    // 添加到布局中
    startLayout->addWidget(start);
    startLayout->addWidget(create);
    startLayout->addWidget(open);

    // 靠左
    startLayout->setAlignment(Qt::AlignLeft);

    // 将布局添加到容器中
    startContainer->setLayout(startLayout);
}

void MainWindow::initRecently()
{
    // 和start一样
    recentlyContainer = new QWidget;

    // 设置背景颜色
    // recentlyContainer->setStyleSheet("background-color: #ccc;");

    // 创建一个垂直布局
    QVBoxLayout *recentlyLayout = new QVBoxLayout;

    // 创建一个标签，用来显示Start
    QLabel *recently = new QLabel("Recently Opened");

    // 标签样式
    QString styleSheet1 =
        "QLabel { color: #333; }"
        "QLabel { font-size: 20px; }"
        "QLabel { font-weight: bold; }"
        "QLabel { font-family: Microsoft YaHei; }";
    recently->setStyleSheet(styleSheet1);

    // 放在容器左上角
    recentlyLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // 添加到布局中
    recentlyLayout->addWidget(recently);

    recentlyContainer->setLayout(recentlyLayout);
}

void MainWindow::initAbout()
{
    /* About */
    aboutContainer = new QWidget;

    // 设置背景颜色
    // aboutContainer->setStyleSheet("background-color: #999;");

    // About按钮，圆角固定大小
    QPushButton *aboutButton = new QPushButton("About Us");
    aboutButton->setFixedSize(100, 60);
    QString styleSheet =
        "QPushButton { border-radius: 10px; }"
        "QPushButton { border: 1px solid black; }"
        "QPushButton { font-size: 20px; }"
        "QPushButton { background-color: #fff; }";
    aboutButton->setStyleSheet(styleSheet);
    aboutButton->setCursor(Qt::PointingHandCursor);

    // 创建一个垂直布局
    QVBoxLayout *aboutLayout = new QVBoxLayout;
    aboutLayout->setContentsMargins(0, 0, 0, 0);
    aboutLayout->addWidget(aboutButton, 0, Qt::AlignCenter);
    aboutContainer->setLayout(aboutLayout);

    // about按钮的点击事件，弹出一个对话框
    QString name = "Visual Nodes\n";
    QString version = "Version : 1.0.0\n";
    QString author = "Authors : Lu Jialin & Wang Hao\n";
    QString reliance = "Reliance : Qt 5.9.9 & Visual Studio Code\n";
    QString date = "Release Date : 2022.12.20\n";
    QString github = "GitHub : https://github.com/tju2050633\n";
    QString thanks = "Special Thanks : GitHub Copilot & ChatGPT\n";

    QString aboutText = name + version + author + reliance + date + github + thanks;

    connect(aboutButton, &QPushButton::clicked, this, [=]()
            { 
                QMessageBox::about(this, "About Us", aboutText);
                status->setText("About Us"); });
}

// 底部栏部分

void MainWindow::initBottomBar()
{
    bottomBarContainer = new QWidget;

    // 高度
    bottomBarContainer->setFixedHeight(20);

    // 设置背景颜色和去除圆角
    bottomBarContainer->setStyleSheet("background-color: #117ACC; border-radius: 0px;");

    // 创建一个水平布局
    QHBoxLayout *bottomBarLayout = new QHBoxLayout;
    bottomBarLayout->setContentsMargins(0, 0, 0, 0);

    // 初始化底部栏组件
    initSettings();
    initStatus();
    initLog();

    // 添加底部栏组件
    bottomBarLayout->addWidget(settings);
    bottomBarLayout->addWidget(status);
    bottomBarLayout->addWidget(log);

    // 设置底部栏布局
    bottomBarContainer->setLayout(bottomBarLayout);
}

void MainWindow::initSettings()
{
    // 设置按钮
    settings = new QPushButton;
    settings->setFixedSize(60, 60);
    settings->setCursor(Qt::PointingHandCursor);

    // 图标
    QPixmap pixmap(":/icons/gear1.svg"); // 导入按钮的图标

    // 设置图标颜色
    QPixmap newPixmap = pixmap.copy();
    QPainter painter(&newPixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(newPixmap.rect(), QColor("#fff"));
    painter.end();

    settings->setIcon(QIcon(newPixmap));

    // 高度为底部栏高度
    settings->setFixedHeight(bottomBarContainer->height());

    // 设置按钮的点击事件，弹出一个对话框
    connect(settings, &QPushButton::clicked, this, [=]()
            { QMessageBox::about(this, "Settings", "Settings is not available now.");
              status->setText("Settings"); });
}

void MainWindow::initStatus()
{
    // 状态栏
    status = new QLabel("Home Page");

    // 标签样式
    QString styleSheet1 =
        "QLabel { color: #fff; }"
        "QLabel { font-size: 10px; }"
        "QLabel { font-weight: bold; }"
        "QLabel { font-family: Microsoft YaHei; }";
    status->setStyleSheet(styleSheet1);
}

void MainWindow::initLog()
{
    // 输出栏
    log = new QLabel("LOG");

    // 宽度为底部栏宽度的一半
    log->setFixedWidth(bottomBarContainer->width() / 2);

    // 标签样式
    QString styleSheet1 =
        "QLabel { color: #fff; }"
        "QLabel { font-size: 10px; }"
        "QLabel { font-weight: bold; }"
        "QLabel { font-family: Microsoft YaHei; }";
    log->setStyleSheet(styleSheet1);

    // 靠右
    log->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
}
