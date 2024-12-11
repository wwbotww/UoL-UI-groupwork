#include "pages/fluor_window.hpp"
#include <QtCharts/QScatterSeries>
#include <QDateTime>
#include <QFile>
#include <QDebug>

FluorWindow::FluorWindow(QWidget* parent)
        : QWidget(parent),
          layout(new QVBoxLayout(this)),
          chartView(new QChartView(this)),
          chart(new QChart()),
          stationSelector(new QComboBox(this)) // 1. 创建站点选择器
{
    setLayout(layout);

    // 2. 添加站点选择器
    layout->addWidget(stationSelector);
    layout->addWidget(chartView);

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 3. 连接站点选择器的信号到槽函数
    connect(stationSelector, &QComboBox::currentTextChanged, this, &FluorWindow::onStationSelected);

    // 加载数据并绘制图表
    loadDataAndDrawChart();
}

FluorWindow::~FluorWindow() {}

void FluorWindow::loadDataAndDrawChart() {
    try {
        dataset.loadData(std::string(PROJECT_SOURCE_DIR) + "/data/water_quality.csv");
    } catch (const std::exception& e) {
        qWarning() << "failed load data: " << e.what();
        return;
    }

    // 1. 筛选含有 "fluor" 的数据
    fluorData = dataset.filterByFluorInDefinition();
    if (fluorData.empty()) {
        qWarning() << "no 'fluor' related data";
        return;
    }

    // 2. 获取所有监测站名称 (samplingPoint.label) 并将其添加到 QComboBox
    populateStationSelector();

    // 3. 加载和显示**所有监测站的**数据
    drawChartForStation("All Sites");
}

void FluorWindow::populateStationSelector() {
    // 1. 清除之前的站点数据
    stationSelector->clear();

    // 2. 提取所有唯一的 samplingPoint.label
    QSet<QString> stationSet;
    for (const auto& record : fluorData) {
        stationSet.insert(QString::fromStdString(record.getPointLabel()));
    }

    // 3. 添加 "All Sites" 选项
    stationSelector->addItem("All Sites");

    // 4. 将每个唯一的监测站名称添加到选择器
    for (const QString& station : stationSet) {
        stationSelector->addItem(station);
    }
}

void FluorWindow::drawChartForStation(const QString& selectedStation) {
    // 1. 清空图表的所有系列
    chart->removeAllSeries();

    // 2. 移除旧的轴
    QList<QAbstractAxis*> axes = chart->axes();
    for (QAbstractAxis* axis : axes) {
        chart->removeAxis(axis);
    }

    // 3. 创建散点系列 (QScatterSeries) 不同颜色的散点系列
    QScatterSeries* greenSeries = new QScatterSeries();
    QScatterSeries* yellowSeries = new QScatterSeries();
    QScatterSeries* redSeries = new QScatterSeries();

    greenSeries->setName("Low (< 0.03 µg/L)");
    yellowSeries->setName("Medium (0.03 - 0.6 µg/L)");
    redSeries->setName("High (>= 0.6 µg/L)");

    greenSeries->setColor(QColor(Qt::green));
    yellowSeries->setColor(QColor(Qt::yellow));
    redSeries->setColor(QColor(Qt::red));

    greenSeries->setMarkerSize(8.0);
    yellowSeries->setMarkerSize(8.0);
    redSeries->setMarkerSize(8.0);

    QDateTimeAxis* xAxis = new QDateTimeAxis();
    QValueAxis* yAxis = new QValueAxis();

    xAxis->setFormat("yyyy-MM-dd");
    xAxis->setTitleText("Sample Date");
    yAxis->setTitleText("Result (µg/L)");

    yAxis->setRange(0, 1); // Y轴范围

    // 4. 选择属于该监测站的 Fluor 数据
    for (const auto& record : fluorData) {
        if (selectedStation != "All Sites" &&
            selectedStation != QString::fromStdString(record.getPointLabel())) {
            continue;
        }

        QDateTime dateTime = QDateTime::fromString(
                QString::fromStdString(record.getSampleTime()),
                "yyyy-MM-ddTHH:mm:ss" // 修改为正确的时间格式
        );
        if (!dateTime.isValid()) {
            qWarning() << "cant read time data: " << QString::fromStdString(record.getSampleTime());
            continue; // 跳过无法解析的记录
        }

        double resultValue = record.getResult();
        QPointF point(dateTime.toMSecsSinceEpoch(), resultValue);

        if (resultValue < 0.2) {
            greenSeries->append(point);
        } else if (resultValue >= 0.2 && resultValue < 0.6) {
            yellowSeries->append(point);
        } else {
            redSeries->append(point);
        }
    }

    // 5. 配置图表
    chart->addSeries(greenSeries);
    chart->addSeries(yellowSeries);
    chart->addSeries(redSeries);

    chart->setTitle(QString("Time Series of Fluorinated Compounds (%1)").arg(selectedStation));
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->addAxis(xAxis, Qt::AlignBottom);
    chart->addAxis(yAxis, Qt::AlignLeft);

    greenSeries->attachAxis(xAxis);
    greenSeries->attachAxis(yAxis);

    yellowSeries->attachAxis(xAxis);
    yellowSeries->attachAxis(yAxis);

    redSeries->attachAxis(xAxis);
    redSeries->attachAxis(yAxis);
}

void FluorWindow::onStationSelected(const QString& selectedStation) {
    drawChartForStation(selectedStation);
}