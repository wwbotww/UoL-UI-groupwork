#include "pages/page2_window.hpp"
#include <QPushButton>
#include <QTableWidget>
#include <QDateTime>
#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QComboBox>
#include <QStackedWidget>
#include <QLabel>
#include "pages/page2_window.hpp"

// Debug purposes
// #include <QDebug>

Page2Window::Page2Window(QWidget* parent)
        : QWidget(parent),
          pageLabel(new QLabel(this)),
          layout(new QVBoxLayout(this)),
          chartSelector(new QComboBox(this)),
          chartStack(new QStackedWidget(this))
{
    pageLabel->setText("POP (Persistent Organic Pollutants) Data Visualization");
    pageLabel->setAlignment(Qt::AlignCenter);

    // Chart selector
    chartSelector->addItem("NE-49400409 AIRE AT BEAL BRIDGE");
    chartSelector->addItem("NE-49700156 WHARFE ABOVE TADCASTER WEIR");
    chartSelector->addItem("NE-49301624 DON AT A638 NORTH BRIDGE RD - DONCASTER");

    // Connect dropdown selection to change graph
    connect(chartSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Page2Window::displaySelectedGraph);
    
    // Add PCB Chart
        // NE-49400409 AIRE AT BEAL BRIDGE
    createPCBChart("NE-49400409");
        // NE-49700156 WHARFE ABOVE TADCASTER WEIR
    createPCBChart("NE-49700156");
        // NE-49301624 DON AT A638 NORTH BRIDGE RD - DONCASTER
    createPCBChart("NE-49301624");

    layout->addWidget(pageLabel);
    layout->addWidget(chartSelector);
    layout->addWidget(chartStack);
    setLayout(layout);
}

Page2Window::~Page2Window() {}

void Page2Window::loadData() {
  WaterQualityDataset dataset;
  dataset.loadData("../data/water_quality.csv");
  auto filteredData = dataset.filterForPOPs();
}

void Page2Window::createPCBChart(const QString& samplingPoint)
{   
    // Load data
    WaterQualityDataset dataset;
    dataset.loadData("../data/water_quality.csv");
    auto filteredData = dataset.filterForPOPs();

    // Filter data for the specific sampling point
    std::vector<WaterQuality> samplingPointData;
    for (const auto& record : filteredData) {
        // Debuggig
        //QString recordPoint = QString::fromStdString(record.getPointNotation()).trimmed();
        //QString expectedPoint = samplingPoint.trimmed();
            
        //qDebug() << "Record Sampling Point:" << recordPoint;
        //qDebug() << "Expected Sampling Point:" << expectedPoint;

        if (QString::fromStdString(record.getPointNotation()).trimmed().compare(samplingPoint.trimmed(), Qt::CaseInsensitive) == 0) {
            samplingPointData.push_back(record);
        }
    }

    // Create chart
    QChart *chart = new QChart();
    chart->setTitle(samplingPoint);

    // Create Series
    QLineSeries *PCB028 = new QLineSeries();
    PCB028->setName("PCB Con 028");
    QLineSeries *PCB101 = new QLineSeries();
    PCB101->setName("PCB Con 101");
    QLineSeries *PCB118 = new QLineSeries();
    PCB118->setName("PCB Con 118");
    QLineSeries *PCB138 = new QLineSeries();
    PCB138->setName("PCB Con 138");
    QLineSeries *PCB180 = new QLineSeries();
    PCB180->setName("PCB Con 180");

    // Add series to chart
    chart->addSeries(PCB028);
    chart->addSeries(PCB101);
    chart->addSeries(PCB118);
    chart->addSeries(PCB138);
    chart->addSeries(PCB180);

    qint64 minTimestamp = std::numeric_limits<qint64>::max();
    qint64 maxTimestamp = std::numeric_limits<qint64>::lowest();
    qreal minY = std::numeric_limits<qreal>::max();
    qreal maxY = std::numeric_limits<qreal>::lowest();

    // Append records to according series
    for (const WaterQuality& record : samplingPointData)
    {   
        std::string dateTimeString = record.getSampleTime();
        QString qdateTimeString = QString::fromStdString(dateTimeString);
        QDateTime dateTime = QDateTime::fromString(qdateTimeString, Qt::ISODate);
        qint64 msecs = dateTime.toMSecsSinceEpoch();
        qreal result = record.getResult();

        minTimestamp = std::min(minTimestamp, msecs);
        maxTimestamp = std::max(maxTimestamp, msecs);
        minY = std::min(minY, result);
        maxY = std::max(maxY, result);

        if (record.getDeterminand() == "PCB Con 028") {
            PCB028->append(static_cast<qreal>(msecs), record.getResult());
            //qDebug() << "Record:" << QString::fromStdString(record.getSampleTime()) << "Determinand:" << QString::fromStdString(record.getDeterminand()) << "Result:" << QString::number(record.getResult());
        } else if (record.getDeterminand() == "PCB Con 101") {
            PCB101->append(static_cast<qreal>(msecs), record.getResult());
            //qDebug() << "Record:" << QString::fromStdString(record.getSampleTime()) << "Determinand:" << QString::fromStdString(record.getDeterminand()) << "Result:" << QString::number(record.getResult());
        } else if (record.getDeterminand() == "PCB Con 118") {
            PCB118->append(static_cast<qreal>(msecs), record.getResult());
            //qDebug() << "Record:" << QString::fromStdString(record.getSampleTime()) << "Determinand:" << QString::fromStdString(record.getDeterminand()) << "Result:" << QString::number(record.getResult());
        } else if (record.getDeterminand() == "PCB Con 138") {
            PCB138->append(static_cast<qreal>(msecs), record.getResult());
            //qDebug() << "Record:" << QString::fromStdString(record.getSampleTime()) << "Determinand:" << QString::fromStdString(record.getDeterminand()) << "Result:" << QString::number(record.getResult());
        } else if (record.getDeterminand() == "PCB Con 180") {
            PCB180->append(static_cast<qreal>(msecs), record.getResult());
            //qDebug() << "Record:" << QString::fromStdString(record.getSampleTime()) << "Determinand:" << QString::fromStdString(record.getDeterminand()) << "Result:" << QString::number(record.getResult());
        }
    }

    // Set dynamic X-axis
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTitleText("Date Time");
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(minTimestamp), QDateTime::fromMSecsSinceEpoch(maxTimestamp));
    chart->addAxis(axisX, Qt::AlignBottom);

    // Set dynamic Y-axis
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(minY, maxY);
    axisY->setTitleText("POP Level");
    chart->addAxis(axisY, Qt::AlignLeft);

    // Attach Series to Axes
    PCB028->attachAxis(axisX);
    PCB028->attachAxis(axisY);

    PCB101->attachAxis(axisX);
    PCB101->attachAxis(axisY);

    PCB118->attachAxis(axisX);
    PCB118->attachAxis(axisY);

    PCB138->attachAxis(axisX);
    PCB138->attachAxis(axisY);

    PCB180->attachAxis(axisX);
    PCB180->attachAxis(axisY);

    // Create chart View
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartStack->addWidget(chartView);
}

void Page2Window::displaySelectedGraph(int index)
{
    // Change the currently visible chart
    chartStack->setCurrentIndex(index);
}