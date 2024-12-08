#include "pages/home_window.hpp"

HomeWindow::HomeWindow(QWidget* parent)
        : QMainWindow(parent),
          centralWidget(new QWidget(this)),
          stackedWidget(new QStackedWidget(this))
{
    // Create navigation buttons
    homeButton = new QPushButton("Home");
    fluorButton = new QPushButton("Fluor Data");
    page1Button = new QPushButton("Page 1");
    page2Button = new QPushButton("Page 2");
    page3Button = new QPushButton("Page 3");

    // Layout for navigation bar
    navLayout = new QVBoxLayout();
    navLayout->addWidget(homeButton);
    navLayout->addWidget(fluorButton);
    navLayout->addWidget(page1Button);
    navLayout->addWidget(page2Button);
    navLayout->addWidget(page3Button);
    navLayout->addStretch();

    QWidget* navBar = new QWidget(this);
    navBar->setLayout(navLayout);
    navBar->setFixedWidth(120);
    navBar->setStyleSheet("background-color: #2c3e50;");

    // Create the pages
    homePage = new QWidget(this);
    QVBoxLayout* homeLayout = new QVBoxLayout(homePage);
    QLabel* homeLabel = new QLabel("Welcome to the Home Page! This is the main page of the application.");
    homeLabel->setAlignment(Qt::AlignCenter);
    homeLayout->addWidget(homeLabel);

    fluorPage = new FluorWindow();
    page1 = new Page1Window();
    page2 = new Page2Window();
    page3 = new Page3Window();

    // Add pages to QStackedWidget
    stackedWidget->addWidget(homePage); // **第一个页面：HomePage**
    stackedWidget->addWidget(fluorPage); // **第二个页面：FluorWindow**
    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
    stackedWidget->addWidget(page3);

    // 显示默认页面为HomePage
    stackedWidget->setCurrentWidget(homePage); // **默认页面改为HomePage**

    // Main layout
    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(navBar);
    mainLayout->addWidget(stackedWidget);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(homeButton, &QPushButton::clicked, this, &HomeWindow::showHomePage);
    connect(fluorButton, &QPushButton::clicked, this, &HomeWindow::showFluorWindow);
    connect(page1Button, &QPushButton::clicked, this, &HomeWindow::showPage1);
    connect(page2Button, &QPushButton::clicked, this, &HomeWindow::showPage2);
    connect(page3Button, &QPushButton::clicked, this, &HomeWindow::showPage3);

    setWindowTitle("Home - Navigation");
    resize(800, 600);
}

HomeWindow::~HomeWindow() {}

void HomeWindow::showHomePage() {
    stackedWidget->setCurrentWidget(homePage);
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