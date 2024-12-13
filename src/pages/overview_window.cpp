#include "pages/overview_window.hpp"
#include "pages/fluor_stats.hpp"
#include <iostream>

OverviewWindow::OverviewWindow(QWidget* parent)
        : QWidget(parent),
          mapView(new QWebEngineView(this)) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Map section
    mapView->setMinimumHeight(300);

    QFile file(":/html/map.html"); // Load Google Maps HTML
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open map.html";
        return;
    }
    QString html = file.readAll();
    html.replace("/*DATA_POINTS*/", "[]"); // Empty array on initial load
    mapView->setHtml(html); // Load Google Maps when the page is displayed
    file.close();

    mainLayout->addWidget(mapView);

    // Bottom layout section
    QWidget* bottomSection = new QWidget(this);
    QGridLayout* gridLayout = new QGridLayout(bottomSection);

    // Fluor module
    QWidget* fluorWidget = new QWidget(this);
    QVBoxLayout* fluorLayout = new QVBoxLayout(fluorWidget);
    fluorDataButton = new QPushButton(tr("Show Fluor Data on Map"), this);
    fluorLayout->addWidget(fluorDataButton);
    connect(fluorDataButton, &QPushButton::clicked, this, &OverviewWindow::displayFluorDataOnMap);
    gridLayout->addWidget(fluorWidget, 0, 0);

    // Page1 module
    QWidget* page1Widget = new QWidget(this);
    QVBoxLayout* page1Layout = new QVBoxLayout(page1Widget);
    page1Button = new QPushButton(tr("Show Litter Data on Map"), this);
    page1Layout->addWidget(page1Button);
    connect(page1Button, &QPushButton::clicked, this, &OverviewWindow::displayPage1DataOnMap);
    gridLayout->addWidget(page1Widget, 0, 1);

    // Page2 module
    QWidget* page2Widget = new QWidget(this);
    QVBoxLayout* page2Layout = new QVBoxLayout(page2Widget);
    page2Button = new QPushButton(tr("Show POPs Data on Map"), this);
    page2Layout->addWidget(page2Button);
    connect(page2Button, &QPushButton::clicked, this, &OverviewWindow::displayPage2DataOnMap);
    gridLayout->addWidget(page2Widget, 1, 0);

    // Page3 module
    QWidget* page3Widget = new QWidget(this);
    QVBoxLayout* page3Layout = new QVBoxLayout(page3Widget);
    page3Button = new QPushButton(tr("Show Page3 Data"), this);
    page3Layout->addWidget(page3Button);
    connect(page3Button, &QPushButton::clicked, this, &OverviewWindow::displayPage3DataOnMap);
    gridLayout->addWidget(page3Widget, 1, 1);

    bottomSection->setLayout(gridLayout);
    mainLayout->addWidget(bottomSection);
    setLayout(mainLayout);
}

void OverviewWindow::displayFluorDataOnMap() {
    QString jsArray = FluorStats::loadFluorDataAsJSArray(std::string(PROJECT_SOURCE_DIR) + "/data/water_quality.csv");
    mapView->page()->runJavaScript(QString("updateMarkers(%1)").arg(jsArray));
}

void OverviewWindow::displayPage1DataOnMap() {
    QString jsArray = FluorStats::loadLitterDataAsJSArray(std::string(PROJECT_SOURCE_DIR) + "/data/water_quality.csv");
    mapView->page()->runJavaScript(QString("updateMarkers(%1)").arg(jsArray));
}

void OverviewWindow::displayPage2DataOnMap() {
    QString jsArray = FluorStats::loadPOPDataAsJSArray(std::string(PROJECT_SOURCE_DIR) + "/data/water_quality.csv");
    mapView->page()->runJavaScript(QString("updateMarkers(%1)").arg(jsArray));
}

void OverviewWindow::displayPage3DataOnMap() {
    // Load logic for Page3 data (data processing logic to be added)
    mapView->page()->runJavaScript("updateMarkers([])");
}

void OverviewWindow::updateTranslations() {
    fluorDataButton->setText(tr("Show Fluor Data on Map"));
    page1Button->setText(tr("Show Litter Data on Map"));
    page2Button->setText(tr("Show POPs Data on Map"));
    page3Button->setText(tr("Show Page3 Data"));
}