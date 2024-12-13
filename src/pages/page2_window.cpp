#include "pages/page2_window.hpp"
#include <QPushButton>
#include <QTableWidget>
#include <QDateTime>
#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QComboBox>
#include <QStackedWidget>
#include <QLabel>
#include <QToolTip>
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
    pageLabel->setText(tr("POP (Persistent Organic Pollutants) Data Visualization"));
    pageLabel->setAlignment(Qt::AlignCenter);

    // Chart selector
    chartSelector->addItem("ALL LOCATIONS");
    chartSelector->addItem("NE-49400409 AIRE AT BEAL BRIDGE");
    chartSelector->addItem("NE-49700156 WHARFE ABOVE TADCASTER WEIR");
    chartSelector->addItem("NE-49301624 DON AT A638 NORTH BRIDGE RD - DONCASTER");

    // Add PCB Chart
    // All locations
    createPCBChart("All locations");
    // NE-49400409 AIRE AT BEAL BRIDGE
    createPCBChart("NE-49400409");
    // NE-49700156 WHARFE ABOVE TADCASTER WEIR
    createPCBChart("NE-49700156");
    // NE-49301624 DON AT A638 NORTH BRIDGE RD - DONCASTER
    createPCBChart("NE-49301624");

    connect(chartSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Page2Window::displaySelectedGraph);

    layout->addWidget(pageLabel);
    layout->addWidget(chartSelector);
    layout->addWidget(chartStack);
    setLayout(layout);
}

Page2Window::~Page2Window() {}

void Page2Window::loadData() {
    WaterQualityDataset dataset;
    dataset.loadData(std::string(PROJECT_SOURCE_DIR) + "/data/water_quality.csv");
    auto filteredData = dataset.filterForPOPs();
}

void Page2Window::attachAxesToSeries(
        QAbstractSeries* series,
        QDateTimeAxis* axisX,
        QValueAxis* axisY) const
{
    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

QScatterSeries* Page2Window::createSeries(const QString& name, const QColor& color) const {
    QScatterSeries* series = new QScatterSeries();
    series->setName(name);
    series->setColor(color);
    connect(series, &QScatterSeries::hovered, this, &Page2Window::onPointHovered);
    return series;
}

void Page2Window::createPCBChart(const QString& samplingPoint)
{
    // Load data
    WaterQualityDataset dataset;
    dataset.loadData(std::string(PROJECT_SOURCE_DIR) + "/data/water_quality.csv");
    auto filteredData = dataset.filterForPOPs();

    // Filter data for the specific sampling point
    std::vector<WaterQuality> samplingPointData;
    for (const auto& record : filteredData) {
        if (QString::fromStdString(record.getPointNotation()).trimmed().compare(samplingPoint.trimmed(), Qt::CaseInsensitive) == 0) {
            samplingPointData.push_back(record);
        } else if (samplingPoint == "All locations") {
            samplingPointData.push_back(record);
        }
    }

    // Create chart
    QChart *chart = new QChart();
    chart->setTitle(samplingPoint);

    // Colours to ensure all colours are unique
    QVector<QColor> colors = {
            Qt::red, Qt::green, Qt::blue, Qt::cyan, Qt::magenta,
            Qt::yellow, Qt::gray, Qt::darkRed, Qt::darkGreen, Qt::darkBlue
    };

    // determinands
    QStringList determinands = {
            "PCB Con 028", "PCB Con 052", "PCB Con 101", "PCB Con 105",
            "PCB Con 118", "PCB Con 138", "PCB Con 153", "PCB Con 156",
            "PCB Con 180", "PCB Total"
    };

    QMap<QString, QScatterSeries*> seriesMap;
    for (int i = 0; i < determinands.size(); ++i) {
        const QString& determinand = determinands[i];
        QColor color = colors[i % colors.size()];
        QScatterSeries* series = createSeries(determinand, color);
        chart->addSeries(series);
        seriesMap[determinand] = series;
    }

    qint64 minTimestamp = std::numeric_limits<qint64>::max();
    qint64 maxTimestamp = std::numeric_limits<qint64>::lowest();
    qreal minY = std::numeric_limits<qreal>::max();
    qreal maxY = std::numeric_limits<qreal>::lowest();

    // Append records to according series
    dataPoints.clear();
    for (const WaterQuality& record : samplingPointData)
    {
        QString determinand = QString::fromStdString(record.getDeterminand());
        if (seriesMap.contains(determinand)) {
            std::string dateTimeString = record.getSampleTime();
            QString qdateTimeString = QString::fromStdString(dateTimeString);
            QDateTime dateTime = QDateTime::fromString(qdateTimeString, Qt::ISODate);
            qint64 msecs = dateTime.toMSecsSinceEpoch();
            qreal result = record.getResult();

            minTimestamp = std::min(minTimestamp, msecs);
            maxTimestamp = std::max(maxTimestamp, msecs);
            minY = std::min(minY, result);
            maxY = std::max(maxY, result);
            seriesMap[determinand]->append(static_cast<qreal>(msecs), result);
            dataPoints.push_back(record);
        }
    }

    // Set dynamic X-axis
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTitleText(tr("Date Time"));
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(minTimestamp), QDateTime::fromMSecsSinceEpoch(maxTimestamp));
    chart->addAxis(axisX, Qt::AlignBottom);

    // Set dynamic Y-axis
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(minY, maxY*1.1);
    axisY->setTitleText(tr("PCB Level ug/l"));
    chart->addAxis(axisY, Qt::AlignLeft);

    // Attach Axes
    for (QScatterSeries* series : seriesMap) {
        attachAxesToSeries(series, axisX, axisY);
    }

    // Create chart View
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartStack->addWidget(chartView);
}

void Page2Window::displaySelectedGraph(int index)
{
    // Set the new current index in the chart stack
    chartStack->setCurrentIndex(index);

    // Handle hover signals for the new chart
    QChartView* currentChartView = qobject_cast<QChartView*>(chartStack->currentWidget());
    if (!currentChartView) return;

    QChart* currentChart = currentChartView->chart();
    if (!currentChart) return;

    // Disconnect previous hover signals and connect the new ones
    for (QAbstractSeries* series : currentChart->series()) {
        if (auto* scatterSeries = qobject_cast<QScatterSeries*>(series)) {
            disconnect(scatterSeries, nullptr, this, nullptr); // Disconnect any previous signals
            connect(scatterSeries, &QScatterSeries::hovered, this, &Page2Window::onPointHovered);
        }
    }
}

void Page2Window::onPointHovered(const QPointF& point, bool state) {
    if (state) {
        // Retrieve compliance status from the associated record
        QString determinand = "Unavailable";
        bool isCompliant = false;
        for (const WaterQuality& record : dataPoints) {
            if (record.getResult() == point.y()) {
                determinand = QString::fromStdString(record.getDeterminand());
                isCompliant = record.isCompliance();
                break;
            }
        }
        // Set tool tips
        QString complianceText = isCompliant ? "Compliant" : "Non-Compliant";
        QString tooltipText = QString("Determinand: %1\nValue: %2\nStatus: %3")
                .arg(determinand)
                .arg(point.y())
                .arg(complianceText);
        QToolTip::showText(QCursor::pos(), tooltipText);
    } else {
        QToolTip::hideText();
    }
}