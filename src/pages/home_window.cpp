#include "pages/home_window.hpp"
#include "pages/overview_window.hpp"

HomeWindow::HomeWindow(QWidget* parent)
        : QMainWindow(parent),
          centralWidget(new QWidget(this)),
          stackedWidget(new QStackedWidget(this)) {
    // 创建导航按钮
    homeButton = new QPushButton("Overview");
    fluorButton = new QPushButton("Fluor Data");
    page1Button = new QPushButton("Page 1");
    page2Button = new QPushButton("Page 2");
    page3Button = new QPushButton("Page 3");

    // 导航栏布局
    navLayout = new QVBoxLayout();
    navLayout->addWidget(homeButton); // 概览按钮
    navLayout->addWidget(fluorButton);
    navLayout->addWidget(page1Button);
    navLayout->addWidget(page2Button);
    navLayout->addWidget(page3Button);
    navLayout->addStretch();

    QWidget* navBar = new QWidget(this);
    navBar->setLayout(navLayout);
    navBar->setFixedWidth(120);
    navBar->setStyleSheet("background-color: #2c3e50;");

    // 页面定义
    overviewPage = new OverviewWindow(this);
    connect(overviewPage, &OverviewWindow::showFluorPage, this, &HomeWindow::showFluorWindow);
    connect(overviewPage, &OverviewWindow::showPage1, this, &HomeWindow::showPage1);
    connect(overviewPage, &OverviewWindow::showPage2, this, &HomeWindow::showPage2);
    connect(overviewPage, &OverviewWindow::showPage3, this, &HomeWindow::showPage3);

    fluorPage = new FluorWindow(this);
    page1 = new QWidget(this); // 如果有自定义窗口，可以替换为 Page1Window
    page2 = new QWidget(this); // 如果有自定义窗口，可以替换为 Page2Window
    page3 = new QWidget(this); // 如果有自定义窗口，可以替换为 Page3Window

    // 将页面添加到 QStackedWidget
    stackedWidget->addWidget(overviewPage); // 概览页面
    stackedWidget->addWidget(fluorPage);    // Fluor 页面
    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
    stackedWidget->addWidget(page3);

    // 默认显示概览页面
    stackedWidget->setCurrentWidget(overviewPage);

    // 布局管理
    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(navBar);
    mainLayout->addWidget(stackedWidget);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // 连接导航按钮的信号与插槽
    connect(homeButton, &QPushButton::clicked, this, &HomeWindow::showOverviewPage);
    connect(fluorButton, &QPushButton::clicked, this, &HomeWindow::showFluorWindow);
    connect(page1Button, &QPushButton::clicked, this, &HomeWindow::showPage1);
    connect(page2Button, &QPushButton::clicked, this, &HomeWindow::showPage2);
    connect(page3Button, &QPushButton::clicked, this, &HomeWindow::showPage3);

    setWindowTitle("Home - Navigation");
    resize(800, 600);
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

void HomeWindow::showPage3() {
    stackedWidget->setCurrentWidget(page3);
}