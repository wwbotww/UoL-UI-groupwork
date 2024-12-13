#include "pages/home_window.hpp"
#include "pages/overview_window.hpp"
#include "pages/page2_window.hpp"
#include "pages/page1_window.hpp"
#include "pages/fluor_window.hpp"
#include "pages/mainwindow.h"
#include <QTranslator>
#include <QLocale>
#include <QComboBox>

HomeWindow::HomeWindow(QWidget* parent)
        : QMainWindow(parent),
          centralWidget(new QWidget(this)),
          stackedWidget(new QStackedWidget(this)),
          languageSelector(new QComboBox(this)) // 创建语言选择器
{
    // 创建导航按钮
    homeButton = new QPushButton(tr("Overview"));
    fluorButton = new QPushButton(tr("Fluor Data"));
    page1Button = new QPushButton(tr("Litter Data"));
    page2Button = new QPushButton(tr("POP Data"));
    pollutantButton = new QPushButton(tr("Pollutant"));

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
    pollutantButton->setStyleSheet(buttonStyle);

    // 设置按钮大小策略，使其均匀分布
    homeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    fluorButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    page1Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    page2Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pollutantButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 创建导航栏布局
    navLayout = new QVBoxLayout();

    // 语言选择器
    languageSelector->addItem("English", "en_US"); // 默认语言
    languageSelector->addItem("中文", "zh_CN"); // 中文语言选项
    languageSelector->setStyleSheet(R"(
        QComboBox {
            background-color: #34495e;
            color: white;
            border: 1px solid white;
            font-size: 16px;
            padding: 5px;
        }
        QComboBox::drop-down {
            border: none;
        }
        QComboBox QAbstractItemView {
            background-color: #34495e;
            color: white;
            selection-background-color: #1abc9c;
        }
    )");

    // 连接语言选择器的信号槽
    connect(languageSelector, &QComboBox::currentTextChanged, this, &HomeWindow::onLanguageSelected);

    // 将按钮和语言选择器添加到导航栏
    navLayout->addWidget(languageSelector);
    navLayout->addWidget(homeButton);
    navLayout->addWidget(fluorButton);
    navLayout->addWidget(page1Button);
    navLayout->addWidget(page2Button);
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
    connect(overviewPage, &OverviewWindow::showPage3, this, &HomeWindow::showPollutantWindow);

    fluorPage = new FluorWindow(this);
    page1 = new Page1Window(this);
    page2 = new Page2Window(this);
    pollutantPage = new MainWindow(this);

    // 将页面添加到 QStackedWidget
    stackedWidget->addWidget(overviewPage);
    stackedWidget->addWidget(fluorPage);
    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
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
    connect(pollutantButton, &QPushButton::clicked, this, &HomeWindow::showPollutantWindow);

    setWindowTitle(tr("Water Quality Monitor"));
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

void HomeWindow::showPollutantWindow() {
    stackedWidget->setCurrentWidget(pollutantPage);
}

void HomeWindow::onLanguageSelected(const QString& language) {
    QString languageCode = languageSelector->currentData().toString();
    switchLanguage(languageCode);
}

void HomeWindow::switchLanguage(const QString& languageCode) {
    static QTranslator translator;
    qApp->removeTranslator(&translator); // 移除之前的语言

    if (translator.load(":/translations/" + languageCode + ".qm")) {
        qApp->installTranslator(&translator);
    }

    // 重新加载 HomeWindow UI
    homeButton->setText(tr("Overview"));
    fluorButton->setText(tr("Fluor Data"));
    page1Button->setText(tr("Litter Data"));
    page2Button->setText(tr("POP Data"));
    pollutantButton->setText(tr("Pollutant"));
    languageSelector->setItemText(0, tr("English"));
    languageSelector->setItemText(1, tr("中文"));
    setWindowTitle(tr("Water Quality Monitor"));

    // 重新加载每个页面的翻译
    overviewPage->OverviewWindow::updateTranslations();
//    fluorPage->updateTranslations();
//    page1->updateTranslations();
//    page2->updateTranslations();
//    pollutantPage->updateTranslations();
}