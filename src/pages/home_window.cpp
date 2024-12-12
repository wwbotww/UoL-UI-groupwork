#include "pages/home_window.hpp"
#include "pages/overview_window.hpp"
#include "pages/page2_window.hpp"
#include "pages/page1_window.hpp"
#include "mainwindow.h"

HomeWindow::HomeWindow(QWidget* parent)
        : QMainWindow(parent),
          centralWidget(new QWidget(this)),
          stackedWidget(new QStackedWidget(this))
{
    // 创建导航按钮
    homeButton = new QPushButton("Overview");
    fluorButton = new QPushButton("Fluor Data");
    page1Button = new QPushButton("Litter Data");
    page2Button = new QPushButton("POP Data");
//    page3Button = new QPushButton("Page 3");
    pollutantButton = new QPushButton("Pollutant");

    // 按钮样式表
    QString buttonStyle = R"(
        QPushButton {
            background-color: #34495e;
            color: white;
            border: none;
            font-size: 18px;
            padding: 10px;
            text-align: center;
        }
        QPushButton:hover {
            background-color: #1abc9c;
        }
        QPushButton:pressed {
            background-color: #16a085;
        }
    )";

    // 将样式表应用到每个按钮
    homeButton->setStyleSheet(buttonStyle);
    fluorButton->setStyleSheet(buttonStyle);
    page1Button->setStyleSheet(buttonStyle);
    page2Button->setStyleSheet(buttonStyle);
//    page3Button->setStyleSheet(buttonStyle);
    pollutantButton->setStyleSheet(buttonStyle);

    // 设置按钮大小策略，使其均匀分布
    homeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    fluorButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    page1Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    page2Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    page3Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pollutantButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 创建导航栏布局
    navLayout = new QVBoxLayout();
    navLayout->addWidget(homeButton);
    navLayout->addWidget(fluorButton);
    navLayout->addWidget(page1Button);
    navLayout->addWidget(page2Button);
//    navLayout->addWidget(page3Button);
    navLayout->addWidget(pollutantButton);

    // 确保按钮均匀填满导航栏的高度
    navLayout->setSpacing(10);
    navLayout->setContentsMargins(0, 0, 0, 0); // 去除导航栏的外边距

    // 创建导航栏部件并应用布局
    QWidget* navBar = new QWidget(this);
    navBar->setLayout(navLayout);
    navBar->setFixedWidth(150); // 增大导航栏宽度以便按钮显示更大
    navBar->setStyleSheet(R"(
        QWidget {
            background-color: #2c3e50;
        }
    )");

    // 页面定义
    overviewPage = new OverviewWindow(this);
    connect(overviewPage, &OverviewWindow::showFluorPage, this, &HomeWindow::showFluorWindow);
    connect(overviewPage, &OverviewWindow::showPage1, this, &HomeWindow::showPage1);
    connect(overviewPage, &OverviewWindow::showPage2, this, &HomeWindow::showPage2);
//    connect(overviewPage, &OverviewWindow::showPage3, this, &HomeWindow::showPage3);
    connect(overviewPage, &OverviewWindow::showPage3, this, &HomeWindow::showPollutantWindow);

    fluorPage = new FluorWindow(this);
    page1 = new Page1Window(this);
    page2 = new Page2Window(this);
//    page3 = new QWidget(this);
    pollutantPage = new MainWindow(this);

    // 将页面添加到 QStackedWidget
    stackedWidget->addWidget(overviewPage);
    stackedWidget->addWidget(fluorPage);
    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
//    stackedWidget->addWidget(page3);
    stackedWidget->addWidget(pollutantPage);

    // 默认显示页面
    stackedWidget->setCurrentWidget(overviewPage);

    // 布局管理
    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(navBar);
    mainLayout->addWidget(stackedWidget);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // 连接导航按钮信号与槽函数
    connect(homeButton, &QPushButton::clicked, this, &HomeWindow::showOverviewPage);
    connect(fluorButton, &QPushButton::clicked, this, &HomeWindow::showFluorWindow);
    connect(page1Button, &QPushButton::clicked, this, &HomeWindow::showPage1);
    connect(page2Button, &QPushButton::clicked, this, &HomeWindow::showPage2);
//    connect(page3Button, &QPushButton::clicked, this, &HomeWindow::showPage3);
    connect(pollutantButton, &QPushButton::clicked, this, &HomeWindow::showPollutantWindow);

    setWindowTitle("Water Quality Monitor");
    resize(1000, 700);
}

HomeWindow::~HomeWindow() {}

void HomeWindow::showOverviewPage() {
    stackedWidget->setCurrentWidget(overviewPage);
}

void HomeWindow::showFluorWindow() {
    stackedWidget->setCurrentWidget(fluorPage);
}

void HomeWindow::showPage1() {
    stackedWidget->setCurrentWidget(page1);
}

void HomeWindow::showPage2() {
    stackedWidget->setCurrentWidget(page2);
}

//void HomeWindow::showPage3() {
//    stackedWidget->setCurrentWidget(page3);
//}

void HomeWindow::showPollutantWindow() {
    stackedWidget->setCurrentWidget(pollutantPage);
}