#include "pages/page1_window.hpp"
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QVBoxLayout>

using namespace QtCharts;

//constructor
Page1Window::Page1Window(QWidget* parent)
        : QWidget(parent),
          pageLabel(new QLabel(this)),
          layout(new QVBoxLayout(this)),
          litterTable(new QTableWidget(this)),
          chartView(new QChartView(this)),
          filterComboBox(new QComboBox(this)),
          refreshButton(new QPushButton("Refresh", this))
          
{
    dataset.loadData("data/water_quality.csv");

    filterComboBox->addItem("All locations");
    filterComboBox->addItem("Location A");
    filterComboBox->addItem("Location B");

    layout->addWidget(filterComboBox);
    layout->addWidget(refreshButton);
    layout->addWidget(litterTable);
    layout->addWidget(chartView);
 
    // Connect signals and slots
    connect(refreshButton, &QPushButton::clicked, this, &LitterDashboard::updateDashboard);

    
    pageLabel->setText("This is Page 1. Display analysis and visualization here.");
    pageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(pageLabel);
    setLayout(layout);

    updateDashboard();
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

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Litter Levels by Location");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QCategoryAxis *axisX = new QCategoryAxis();
    for (const auto &entry : data) {
        axisX->append(QString::fromStdString(entry.first), series->barSets().indexOf(series->barSets().last()));
    }
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Litter Level");
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
