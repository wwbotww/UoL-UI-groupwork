#include "pages/home_window.hpp"
#include "pages/overview_window.hpp"

HomeWindow::HomeWindow(QWidget* parent)
        : QMainWindow(parent),
          centralWidget(new QWidget(this)),
          stackedWidget(new QStackedWidget(this)) {
    // Create navigation buttons
    homeButton = new QPushButton("Overview");
    fluorButton = new QPushButton("Fluor Data");
    page1Button = new QPushButton("Page 1");
    page2Button = new QPushButton("POP Data");
    page3Button = new QPushButton("Page 3");

    // Navigation bar layout
    navLayout = new QVBoxLayout();
    navLayout->addWidget(homeButton); // Overview button
    navLayout->addWidget(fluorButton);
    navLayout->addWidget(page1Button);
    navLayout->addWidget(page2Button);
    navLayout->addWidget(page3Button);
    navLayout->addStretch();

    QWidget* navBar = new QWidget(this);
    navBar->setLayout(navLayout);
    navBar->setFixedWidth(120);
    navBar->setStyleSheet("background-color: #2c3e50;");

    // Page definitions
    overviewPage = new OverviewWindow(this);
    connect(overviewPage, &OverviewWindow::showFluorPage, this, &HomeWindow::showFluorWindow);
    connect(overviewPage, &OverviewWindow::showPage1, this, &HomeWindow::showPage1);
    connect(overviewPage, &OverviewWindow::showPage2, this, &HomeWindow::showPage2);
    connect(overviewPage, &OverviewWindow::showPage3, this, &HomeWindow::showPage3);

    fluorPage = new FluorWindow(this);
    page1 = new QWidget(this); // Replace with Page1Window if there is a custom window
    page2 = new QWidget(this); // Replace with Page2Window if there is a custom window
    page3 = new QWidget(this); // Replace with Page3Window if there is a custom window

    // Add pages to QStackedWidget
    stackedWidget->addWidget(overviewPage); // Overview page
    stackedWidget->addWidget(fluorPage);    // Fluor page
    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
    stackedWidget->addWidget(page3);

    // Set default page to Overview
    stackedWidget->setCurrentWidget(overviewPage);

    // Layout management
    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(navBar);
    mainLayout->addWidget(stackedWidget);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect navigation button signals to slots
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