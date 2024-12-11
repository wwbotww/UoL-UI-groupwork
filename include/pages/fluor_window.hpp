#ifndef FLUOR_WINDOW_HPP
#define FLUOR_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QChartView>
#include <QComboBox>
#include <QScatterSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include "dataset.hpp"

class FluorWindow : public QWidget {
Q_OBJECT

public:
    explicit FluorWindow(QWidget* parent = nullptr);
    ~FluorWindow();

private slots:
    void onStationSelected(const QString& selectedStation); // 监测站选择事件

private:
    void loadDataAndDrawChart(); // 加载数据并绘制图表
    void populateStationSelector(); // 填充站点选择器
    void drawChartForStation(const QString& selectedStation); // 为指定站点绘制图表

    QVBoxLayout* layout;
    QChartView* chartView;
    QChart* chart;
    QComboBox* stationSelector; // 监测站选择器
    WaterQualityDataset dataset;
    std::vector<WaterQuality> fluorData; // 筛选出的 Fluor 数据
};

#endif // FLUOR_WINDOW_HPP