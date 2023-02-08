#include "InsertSort.h"
#include "mainwindow.h"

InsertionSort::InsertionSort(MainWindow *window)
{
    // 设置上级组件指针
    this->window = window;
    this->view = window->view;
    this->scene = window->scenes[MainWindow::InsertionSort];
    this->rect = window->rects[MainWindow::InsertionSort];

    // 设置原点坐标
    orig_x = scene->sceneRect().x();
    orig_y = scene->sceneRect().y();
    width = scene->sceneRect().width();
    height = scene->sceneRect().height();

    // 初始化
    current_state = data;
    initButtons();
    initGraphics();
}

void InsertionSort::initButtons()
{
    // 初始化按钮
    this->btnReset = new QPushButton("Reset");
    this->btnLastStep = new QPushButton("Last Step");
    this->btnAuto = new QPushButton("Auto");
    this->btnNextStep = new QPushButton("Next Step");

    btnReset->setCursor(Qt::PointingHandCursor);
    btnLastStep->setCursor(Qt::PointingHandCursor);
    btnAuto->setCursor(Qt::PointingHandCursor);
    btnNextStep->setCursor(Qt::PointingHandCursor);

    // 按钮点击事件
    connect(this->btnReset, &QPushButton::clicked, this, &InsertionSort::onResetClicked);
    connect(this->btnLastStep, &QPushButton::clicked, this, &InsertionSort::onLastStepClicked);
    connect(this->btnAuto, &QPushButton::clicked, this, &InsertionSort::onAutoClicked);
    connect(this->btnNextStep, &QPushButton::clicked, this, &InsertionSort::onNextStepClicked);

    // 设置按钮位置靠下，均匀分布
    QWidget *buttonContainer = new QWidget;
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonContainer->setLayout(buttonLayout);
    buttonLayout->addWidget(this->btnReset);
    buttonLayout->addWidget(this->btnLastStep);
    buttonLayout->addWidget(this->btnAuto);
    buttonLayout->addWidget(this->btnNextStep);

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

    btnReset->setStyleSheet(styleSheet);
    btnLastStep->setStyleSheet(styleSheet);
    btnAuto->setStyleSheet(styleSheet);
    btnNextStep->setStyleSheet(styleSheet);

    btnReset->setFixedWidth(150);
    btnLastStep->setFixedWidth(150);
    btnAuto->setFixedWidth(150);
    btnNextStep->setFixedWidth(150);
}

void InsertionSort::initGraphics()
{
    for (int i = 0; i < data.size(); i++)
    {
        // 矩形
        QGraphicsRectItem *rect = new QGraphicsRectItem();
        rects.push_back(rect);
        rects[i]->setRect(0, 0, 40, data[i] * 30);
        rects[i]->setX(orig_x + 100 + i * 50);
        rects[i]->setY(orig_y + 450 - data[i] * 30);
        rects[i]->setBrush(colors[i]);
        scene->addItem(rects[i]);

        // 文字
        QGraphicsTextItem *text = new QGraphicsTextItem();
        texts.push_back(text);
        texts[i]->setPlainText(QString::number(data[i]));
        texts[i]->setPos(orig_x + 100 + i * 50 + 20, orig_y + 450);
        texts[i]->setDefaultTextColor(Qt::black);
        scene->addItem(texts[i]);
    }
}

void InsertionSort::sort()
{
    // 插入排序
    int i, j;
    QList<int> tempData = data;

    // 对应矩形画两个箭头
    QPainterPath path1;
    path1.moveTo(0, 0);
    path1.lineTo(0, 50);
    path1.lineTo(10, 40);
    path1.moveTo(0, 50);
    path1.lineTo(-10, 40);
    QPainterPath path2;
    path2.moveTo(0, 0);
    path2.lineTo(0, 50);
    path2.lineTo(10, 40);
    path2.moveTo(0, 50);
    path2.lineTo(-10, 40);

    QGraphicsPathItem *arrow1 = new QGraphicsPathItem(path1);
    QGraphicsPathItem *arrow2 = new QGraphicsPathItem(path2);
    arrow1->setPos(rects[0]->x() + 20, 90);
    arrow2->setPos(rects[0]->x() + 20, 90);

    if (!reset)
    {
        scene->addItem(arrow1);
        scene->addItem(arrow2);
    }

    // 插入排序
    for (i = 1; i < tempData.size(); i++)
    {
        int temp = tempData[i];
        int j = i - 1;
        while (j >= 0 && tempData[j] > temp)
        {
            arrow1->setPos(rects[j]->x() + 20, 90);
            arrow2->setPos(rects[j + 1]->x() + 20, 90);
            running = true;
            if (reset)
            {
                QThread::msleep(RESET_SLEEP);
            }
            else
            {
                QThread::msleep(AUTO_SLEEP);
            }
            QCoreApplication::processEvents();
            running = false;
            tempData[j + 1] = tempData[j];

            // 交换矩形位置
            swap_animation(j + 1, j);

            j--;
        }
        tempData[j + 1] = temp;
    }

    // 移除箭头
    if (!reset)
    {
        scene->removeItem(arrow1);
        scene->removeItem(arrow2);
    }

    if (!sorted)
        sorted = true;
    else
        sorted = false;
}

void InsertionSort::step()
{
    if (last)
    {
        // log
        window->log->setText("Last Step Executed");

        sorted = false;

        QPair<int, int> last_step = steps.pop();

        int temp = current_state[last_step.first];
        current_state[last_step.first] = current_state[last_step.second];
        current_state[last_step.second] = temp;

        // 交换矩形位置
        swap_animation(last_step.first, last_step.second);

        // 判定完全退回
        if (current_state == data)
        {
            last = false;
        }
    }
    else if (next)
    {
        // log
        window->log->setText("Next Step Executed");

        int i, j;
        QList<int> tempData = data;
        bool flag = false;
        // 插入排序
        for (i = 1; i < tempData.size(); i++)
        {
            int temp = tempData[i];
            for (j = i - 1; j >= 0 && tempData[j] > temp; j--)
            {
                if (tempData == current_state)
                {
                    flag = true;
                }

                tempData[j + 1] = tempData[j];
                if (j == 0 || tempData[j - 1] <= temp)
                {
                    tempData[j] = temp;
                }

                if (flag)
                {
                    // 更新状态
                    current_state[j + 1] = current_state[j];
                    steps.push(QPair<int, int>(j, j + 1));
                    if (j == 0 || tempData[j - 1] <= temp)
                    {
                        current_state[j] = temp;
                    }

                    // 交换矩形位置
                    swap_animation(j, j + 1);

                    // 判定排序完成
                    QList<int> sorted_list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
                    if (current_state == sorted_list)
                    {
                        sorted = true;
                        next = false;
                    }

                    return;
                }
            }
        }
    }
}
