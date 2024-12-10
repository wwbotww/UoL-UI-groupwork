#include "pages/fluor_window.hpp"
#include "dataset.hpp"
#include "pages/fluor_stats.hpp"
#include <QFile>
#include <QDebug>

FluorWindow::FluorWindow(QWidget* parent)
        : QWidget(parent),
          webView(new QWebEngineView(this)),
          layout(new QVBoxLayout(this))
{
    layout->addWidget(webView);    // 地图部分
    setLayout(layout);

    loadFluorData();
}

FluorWindow::~FluorWindow() {}

void FluorWindow::loadFluorData() {
    WaterQualityDataset dataset;
    dataset.loadData("../data/water_quality.csv");

    auto filteredRecords = dataset.filterByFluorInDefinition();
    std::vector<std::pair<int, int>> bngCoords;
    for (const auto& record : filteredRecords) {
        bngCoords.emplace_back(record.getEasting(), record.getNorthing());
    }

    // 转换为 Google Maps 可用的经纬度
    auto latLngCoords = FluorStats::convertBNGToLatLng(bngCoords);

    QStringList locationData;
    for (const auto& coord : latLngCoords) {
        locationData << QString("{lat: %1, lng: %2}").arg(coord.first).arg(coord.second);
    }
    QString jsArray = "[" + locationData.join(",") + "]";

    QFile file(":/html/map.html");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open HTML file.";
        return;
    }

    QString html = file.readAll();
    html.replace("/*DATA_POINTS*/", jsArray);
    webView->setHtml(html);
    file.close();
}