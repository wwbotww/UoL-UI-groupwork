#include "pages/fluor_window.hpp"

FluorWindow::FluorWindow(QWidget* parent)
        : QWidget(parent),
          statsLabel(new QLabel(this)),
          layout(new QVBoxLayout(this))
{
    layout->addWidget(statsLabel);
    setLayout(layout);

    loadFluorData();
}

FluorWindow::~FluorWindow() {}

void FluorWindow::loadFluorData() {
    WaterQualityDataset dataset;
    dataset.loadData("../data/water_quality.csv");
    auto filteredRecords = dataset.filterByFluorInDefinition();
    int fluorCount = static_cast<int>(filteredRecords.size());

    QString statsText = QString("Number of fluor-based compounds: %1").arg(fluorCount);
    statsLabel->setText(statsText);
}