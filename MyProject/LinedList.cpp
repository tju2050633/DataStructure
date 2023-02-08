#include "mainwindow.h"
#include "LinkedList.h"

LinkedList::LinkedList(MainWindow *window)
{
    // 设置上级组件指针
    this->window = window;
    this->view = window->view;
    this->scene = window->scenes[MainWindow::LinkedList];
    this->rect = window->rects[MainWindow::LinkedList];

    // 设置原点坐标
    orig_x = scene->sceneRect().x();
    orig_y = scene->sceneRect().y();
    width = scene->sceneRect().width();
    height = scene->sceneRect().height();

    // 初始化
    initButtons();
    new_node_text = 'A';

    // 设置rect的鼠标点击事件

}

void LinkedList::initButtons()
{
    // 初始化按钮
    this->btnCreate = new QPushButton("Create List");
    this->btnInsert = new QPushButton("Insert Node");
    this->btnDelete = new QPushButton("Delete Node");
    btnCreate->setCursor(Qt::PointingHandCursor);
    btnInsert->setCursor(Qt::PointingHandCursor);
    btnDelete->setCursor(Qt::PointingHandCursor);

    // 按钮点击事件
    connect(this->btnCreate, &QPushButton::clicked, this, &LinkedList::onCreateClicked);
    connect(this->btnInsert, &QPushButton::clicked, this, &LinkedList::onInsertClicked);
    connect(this->btnDelete, &QPushButton::clicked, this, &LinkedList::onDeleteClicked);

    // 设置按钮位置靠下，均匀分布
    QWidget *buttonContainer = new QWidget;
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonContainer->setLayout(buttonLayout);
    buttonLayout->addWidget(this->btnCreate);
    buttonLayout->addWidget(this->btnInsert);
    buttonLayout->addWidget(this->btnDelete);

    // 按钮位置
    buttonContainer->setGeometry(orig_x, orig_y + height - 50, width, 50);

    // 透明背景
    buttonContainer->setStyleSheet("background-color:transparent;");

    // 添加到场景
    scene->addWidget(buttonContainer);

    // 按钮样式，宽度50px
    QString styleSheet =
        "QPushButton { border-radius: 5px; }"
        "QPushButton { border: 1px solid black; }"
        "QPushButton { font-size: 20px; }"
        "QPushButton { background-color: #fff; }";
    btnCreate->setStyleSheet(styleSheet);
    btnInsert->setStyleSheet(styleSheet);
    btnDelete->setStyleSheet(styleSheet);
    btnCreate->setFixedWidth(150);
    btnInsert->setFixedWidth(150);
    btnDelete->setFixedWidth(150);
}

void LinkedList::mousePressEvent(QMouseEvent *event)
{
    // log
    window->log->setText("Mouse Pressed");

    if (readyToInsert)
    {
        // 插入节点
        length++;
        Node *node = new Node;
        nodes.append(node);
        node->text = QString(new_node_text++);
        node->next = nullptr;
        node->entity = drawNode(event->x(), event->y(), node->text);

        readyToDelete = true;
    }
    else if (readyToDelete)
    {
        // 删除节点
    }
}

void LinkedList::onCreateClicked()
{
    if (isCreated)
    {
        window->log->setText("List Already Exists");
        return;
    }
    isCreated = true;

    // log
    window->log->setText("Successfully Created List");

    // 创建头节点
    length = 0;
    head = new Node;
    head->text = "Head";
    head->next = nullptr;
    head->entity = drawNode(orig_x + 100, orig_y + 100, head->text);
}

void LinkedList::onInsertClicked()
{
    // log
    window->log->setText("Click on the position to insert");

    // 鼠标样式
    rect->setCursor(Qt::PointingHandCursor);

    // 准备点击插入
    readyToInsert = true;
}

void LinkedList::onDeleteClicked()
{
    // log
    window->log->setText("Click on the node to delete");
}

QGraphicsEllipseItem *LinkedList::drawNode(int x, int y, QString text)
{
    // 画圆
    QGraphicsEllipseItem *entity = new QGraphicsEllipseItem;
    entity->setRect(0, 0, 50, 50);
    entity->setPos(x, y);
    entity->setBrush(QBrush(Qt::white));
    scene->addItem(entity);

    // 设置圆的文字
    QGraphicsTextItem *str = new QGraphicsTextItem;
    str->setPlainText(text);
    str->setPos(x + 5, y + 13);
    scene->addItem(str);

    return entity;
}

void LinkedList::drawArrow(QGraphicsEllipseItem *start, QGraphicsEllipseItem *end)
{
    // 画线
    QGraphicsLineItem *line = new QGraphicsLineItem;
    line->setLine(start->x(), start->y(), end->x(), end->y());
    scene->addItem(line);
    line->setZValue(-1); // 使箭头在圆的下面

    // 画箭头
    QGraphicsPolygonItem *arrow = new QGraphicsPolygonItem;
    QPolygonF polygon;
    polygon << QPointF(end->x(), end->y()) << QPointF(end->x() - 10, end->y() + 15) << QPointF(end->x() - 10, end->y() + 35);
    arrow->setPolygon(polygon);
    scene->addItem(arrow);
}
