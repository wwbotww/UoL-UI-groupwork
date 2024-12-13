#include "pages/page1_window.hpp"
#include "dataset.hpp"
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QCategoryAxis>
#include <QVBoxLayout>

//constructor
Page1Window::Page1Window(QWidget* parent)
        : QWidget(parent),
          pageLabel(new QLabel(this)),
          layout(new QVBoxLayout(this)),
          litterTable(new QTableWidget(this)),
          chartView(new QChartView(this)),
          filterComboBox(new QComboBox(this))

{
    dataset.loadData(std::string(PROJECT_SOURCE_DIR) + "/data/water_quality.csv");

    filterComboBox->addItem("All locations");
    filterComboBox->addItem("Location A");
    filterComboBox->addItem("Location B");

    layout->addWidget(filterComboBox);
    layout->addWidget(litterTable);
    layout->addWidget(chartView);

    loadData();
}

Page1Window::~Page1Window() {}

// Load data into the table and chart
void Page1Window::loadData() {
    // Filter and summarize data
    auto summarizedData = dataset.summarizeLitterByLocation();

    // Populate the table
    createTable(summarizedData);

    // Populate the chart
    createChart(summarizedData);
}

// Create the table
void Page1Window::createTable(const std::map<std::string, double> &data) {
    litterTable->clear();
    litterTable->setRowCount(data.size());
    litterTable->setColumnCount(2);
    litterTable->setHorizontalHeaderLabels({"Location", "Litter Level"});

    int row = 0;
    for (const auto &entry : data) {
        litterTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(entry.first)));
        litterTable->setItem(row, 1, new QTableWidgetItem(QString::number(entry.second)));
        row++;
    }
}

// Create the chart
void Page1Window::createChart(const std::map<std::string, double> &data) {
    QBarSeries *series = new QBarSeries();

    for (const auto &entry : data) {
        QBarSet *set = new QBarSet(QString::fromStdString(entry.first));
        *set << entry.second;
        series->append(set);
    }

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("Litter Levels by Location"));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QCategoryAxis *axisX = new QCategoryAxis();
    for (const auto &entry : data) {
        axisX->append(QString::fromStdString(entry.first), series->barSets().indexOf(series->barSets().last()));
    }
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setTitleText(tr("Litter Level"));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView->setChart(chart);
}

// Update the dashboard based on selected filters
void Page1Window::updateDashboard() {
    std::string selectedFilter = filterComboBox->currentText().toStdString();

    std::map<std::string, double> filteredData;

    if (selectedFilter == "All Locations") {
        filteredData = dataset.summarizeLitterByLocation();
    } else {
        auto filteredRecords = dataset.filterByLocationOrLitter(selectedFilter, "");
        for (const auto &record : filteredRecords) {
            filteredData[record.getSamplingPoint()] += record.getResult();
        }
    }

    createTable(filteredData);
    createChart(filteredData);
}

void Page1Window::updateTranslations() {
    chart->setTitle(tr("Litter Levels by Location"));
    axisY->setTitleText(tr("Litter Level"));
}