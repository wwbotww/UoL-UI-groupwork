#include "pages/overview_window.hpp"
#include "pages/fluor_stats.hpp"

OverviewWindow::OverviewWindow(QWidget* parent)
        : QWidget(parent),
          mapView(new QWebEngineView(this)) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // 地图部分
    mapView->setMinimumHeight(300);
    QFile file(":/html/map.html"); // 加载 Google Maps 的 HTML
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open map.html";
        return;
    }

    QString html = file.readAll();
    html.replace("/*DATA_POINTS*/", "[]"); // 初始加载时为空数组
    mapView->setHtml(html); // 在页面加载时加载 Google Maps
    file.close();

    mainLayout->addWidget(mapView);

    // 下半部分布局
    QWidget* bottomSection = new QWidget(this);
    QGridLayout* gridLayout = new QGridLayout(bottomSection);

    // Fluor 模块
    QWidget* fluorWidget = new QWidget(this);
    QVBoxLayout* fluorLayout = new QVBoxLayout(fluorWidget);
    fluorDataButton = new QPushButton("Show Fluor Data on Map", this);
    fluorLayout->addWidget(fluorDataButton);
    connect(fluorDataButton, &QPushButton::clicked, this, &OverviewWindow::displayFluorDataOnMap);
    gridLayout->addWidget(fluorWidget, 0, 0);

    // Page1 模块
    QWidget* page1Widget = new QWidget(this);
    QVBoxLayout* page1Layout = new QVBoxLayout(page1Widget);
    QPushButton* page1Button = new QPushButton("Show Page1 Data", this);
    page1Layout->addWidget(page1Button);
    connect(page1Button, &QPushButton::clicked, this, &OverviewWindow::displayPage1DataOnMap);
    gridLayout->addWidget(page1Widget, 0, 1);

    // Page2 模块
    QWidget* page2Widget = new QWidget(this);
    QVBoxLayout* page2Layout = new QVBoxLayout(page2Widget);
    QPushButton* page2Button = new QPushButton("Show Page2 Data", this);
    page2Layout->addWidget(page2Button);
    connect(page2Button, &QPushButton::clicked, this, &OverviewWindow::displayPage2DataOnMap);
    gridLayout->addWidget(page2Widget, 1, 0);

    // Page3 模块
    QWidget* page3Widget = new QWidget(this);
    QVBoxLayout* page3Layout = new QVBoxLayout(page3Widget);
    QPushButton* page3Button = new QPushButton("Show Page3 Data", this);
    page3Layout->addWidget(page3Button);
    connect(page3Button, &QPushButton::clicked, this, &OverviewWindow::displayPage3DataOnMap);
    gridLayout->addWidget(page3Widget, 1, 1);

    bottomSection->setLayout(gridLayout);
    mainLayout->addWidget(bottomSection);
    setLayout(mainLayout);
}

void OverviewWindow::displayFluorDataOnMap() {
    QString jsArray = FluorStats::loadFluorDataAsJSArray("../data/water_quality.csv");
    mapView->page()->runJavaScript(QString("updateMarkers(%1)").arg(jsArray));
}

void OverviewWindow::displayPage1DataOnMap() {
    // 这里使用Page1的数据加载逻辑（待补充数据处理逻辑）
    mapView->page()->runJavaScript("updateMarkers([])");
}

void OverviewWindow::displayPage2DataOnMap() {
    // 这里使用Page2的数据加载逻辑（待补充数据处理逻辑）
    mapView->page()->runJavaScript("updateMarkers([])");
}

void OverviewWindow::displayPage3DataOnMap() {
    // 这里使用Page3的数据加载逻辑（待补充数据处理逻辑）
    mapView->page()->runJavaScript("updateMarkers([])");
}
