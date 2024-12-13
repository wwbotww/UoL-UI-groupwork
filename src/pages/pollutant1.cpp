#include "pages/pollutant1.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>
#include <iostream>
#include <QtCharts>
#include <QDateTime>

pollutant1::pollutant1(const QString &pollutantName, const QStringList &headers,
                       const QList<QStringList> &data, QWidget *parent)
        : QDialog(parent), tableHeaders(headers)
{
    // Initialize the main layout as a horizontal layout
    mainLayout = new QHBoxLayout(this);
    setLayout(mainLayout);

    // Set the window title or any other initialization
    setWindowTitle("Pollutant Details for " + pollutantName);

    // Setup the table and chart
    setupTable(pollutantName, data);
    resize(1500, 800); // Adjust the size for better visualization
}

void pollutant1::setupTable(const QString &pollutantName, const QList<QStringList> &data)
{
    // Create a table for pollutant data
    pollutantTable = new QTableWidget(this);

    // Relevant headers
    QStringList relevantHeaders = {"determinand.label", "sample.sampleDateTime", "result", "determinand.unit.label"};
    QVector<int> relevantColumns;

    for (const QString &header : relevantHeaders) {
        int index = tableHeaders.indexOf(header);
        if (index != -1) {
            relevantColumns.append(index);
        }
    }

    if (relevantColumns.size() != relevantHeaders.size()) {
        qWarning() << "Some relevant headers were not found.";
        return;
    }

    pollutantTable->setColumnCount(relevantColumns.size());
    pollutantTable->setHorizontalHeaderLabels(relevantHeaders);

    QLineSeries *lineSeries = new QLineSeries();
    lineSeries->setName("Trend Line");

    QVector<QPair<qint64, double>> sortedPoints;

    double maxY = std::numeric_limits<double>::lowest();
    double minY = 0.0; // Always start the y-axis at 0
    qint64 minX = LLONG_MAX;
    qint64 maxX = LLONG_MIN;

    int row = 0;

    for (const QStringList &columns : data) {
        if (columns.isEmpty()) continue;

        int labelIndex = relevantColumns[0]; // "determinand.label"
        int dateIndex = relevantColumns[1]; // "sample.sampleDateTime"
        int resultIndex = relevantColumns[2]; // "result"

        if (columns[labelIndex].trimmed().compare(pollutantName, Qt::CaseInsensitive) == 0) {
            pollutantTable->insertRow(row);

            // Populate the table
            for (int colIndex = 0; colIndex < relevantColumns.size(); ++colIndex) {
                int column = relevantColumns[colIndex];
                QTableWidgetItem *item = new QTableWidgetItem(columns[column]);
                pollutantTable->setItem(row, colIndex, item);
            }
            ++row;

            // Add data to the graph
            QDateTime dateTime = QDateTime::fromString(columns[dateIndex], Qt::ISODate);
            bool ok;
            double result = columns[resultIndex].toDouble(&ok);

            if (ok && dateTime.isValid()) {
                qint64 timestamp = dateTime.toMSecsSinceEpoch();

                // Collect points for sorting
                sortedPoints.append(qMakePair(timestamp, result));

                // Track min and max values
                maxY = std::max(maxY, result);
                minX = std::min(minX, timestamp);
                maxX = std::max(maxX, timestamp);
            }
        }
    }

    if (sortedPoints.isEmpty()) {
        QTableWidgetItem *noDataItem = new QTableWidgetItem("No data available for this pollutant.");
        pollutantTable->insertRow(0);
        pollutantTable->setItem(0, 0, noDataItem);
        pollutantTable->setSpan(0, 0, 1, relevantColumns.size());
        return;
    }

    // Sort the points by timestamp
    std::sort(sortedPoints.begin(), sortedPoints.end(), [](const QPair<qint64, double> &a, const QPair<qint64, double> &b) {
        return a.first < b.first;
    });

    // Determine thresholds based on overall pollutant data
    double total = 0.0;
    double maxResult = std::numeric_limits<double>::lowest();
    int count = 0;

    for (const auto &point : sortedPoints) {
        double result = point.second;
        total += result;
        maxResult = std::max(maxResult, result);
        ++count;
    }

    double average = total / count;
    double warningThreshold = average * 1.5; // 50% above average for warning
    double dangerThreshold = maxResult * 0.8; // 80% of max value for danger

    QScatterSeries *normalSeries = new QScatterSeries();
    normalSeries->setMarkerSize(7);
    normalSeries->setName("Normal Levels");
    normalSeries->setColor(Qt::green); // Normal: green

    QScatterSeries *warningSeries = new QScatterSeries();
    warningSeries->setMarkerSize(7);
    warningSeries->setName("Warning Levels");
    warningSeries->setColor(QColor(255, 204, 0)); // Darker yellow (Hex: #FFCC00)


    QScatterSeries *dangerSeries = new QScatterSeries();
    dangerSeries->setMarkerSize(7);
    dangerSeries->setName("Danger Levels");
    dangerSeries->setColor(Qt::red); // Danger: red

    for (const auto &point : sortedPoints) {
        qint64 timestamp = point.first;
        double result = point.second;

        if (result < warningThreshold) {
            normalSeries->append(timestamp, result);
        } else if (result < dangerThreshold) {
            warningSeries->append(timestamp, result);
        } else {
            dangerSeries->append(timestamp, result);
        }

        lineSeries->append(timestamp, result); // Line series remains as is
    }

    // Adding horizontal lines for thresholds
    QLineSeries *warningLine = new QLineSeries();
    warningLine->setName("Warning Threshold");
    warningLine->append(minX, warningThreshold);
    warningLine->append(maxX, warningThreshold);
    warningLine->setColor(QColor(255, 204, 0)); // Darker yellow (Hex: #FFCC00)
    // Color to match warning series

    QLineSeries *dangerLine = new QLineSeries();
    dangerLine->setName("Danger Threshold");
    dangerLine->append(minX, dangerThreshold);
    dangerLine->append(maxX, dangerThreshold);
    dangerLine->setColor(Qt::red); // Color to match danger series

    // Adjust x and y axes
    QDateTime earliestDate = QDateTime::fromMSecsSinceEpoch(minX).addDays(-7); // Extend range before earliest date
    QDateTime latestDate = QDateTime::fromMSecsSinceEpoch(maxX).addDays(7);   // Extend range after latest date
    double adjustedMaxY = maxY * 1.2; // Extend y-axis to 120% of the max value

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(normalSeries);
    chart->addSeries(warningSeries);
    chart->addSeries(dangerSeries);
    chart->addSeries(lineSeries);
    chart->addSeries(warningLine);
    chart->addSeries(dangerLine);
    chart->setTitle("Pollutant Data Over Time");
    chart->legend()->setVisible(true);

    // Set up the x-axis
    QDateTimeAxis *xAxis = new QDateTimeAxis();
    xAxis->setFormat("yyyy-MM-dd");
    xAxis->setTitleText("Date");
    xAxis->setRange(earliestDate, latestDate);
    xAxis->setTickCount(10);
    chart->addAxis(xAxis, Qt::AlignBottom);
    normalSeries->attachAxis(xAxis);
    warningSeries->attachAxis(xAxis);
    dangerSeries->attachAxis(xAxis);
    lineSeries->attachAxis(xAxis);
    warningLine->attachAxis(xAxis);
    dangerLine->attachAxis(xAxis);

    // Set up the y-axis
    QValueAxis *yAxis = new QValueAxis();
    yAxis->setTitleText("Result");
    yAxis->setRange(minY, adjustedMaxY); // Start from 0 and extend beyond max
    chart->addAxis(yAxis, Qt::AlignLeft);
    normalSeries->attachAxis(yAxis);
    warningSeries->attachAxis(yAxis);
    dangerSeries->attachAxis(yAxis);
    lineSeries->attachAxis(yAxis);
    warningLine->attachAxis(yAxis);
    dangerLine->attachAxis(yAxis);

    // Create the chart view and add it to the layout
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Create a horizontal layout for the table and chart
    QHBoxLayout *tableChartLayout = new QHBoxLayout();

    // Add the table and chart view to the horizontal layout
    tableChartLayout->addWidget(pollutantTable);
    tableChartLayout->addWidget(chartView);

    // Set stretch factors: the chart takes up 70%, and the table takes up 30%
    tableChartLayout->setStretchFactor(pollutantTable, 3);
    tableChartLayout->setStretchFactor(chartView, 7);

    // Add the horizontal layout to the main layout
    mainLayout->addLayout(tableChartLayout);
}
