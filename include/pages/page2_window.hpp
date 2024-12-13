#ifndef PAGE2_WINDOW_HPP
#define PAGE2_WINDOW_HPP

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPointF>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QChartView>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QString>
#include <QComboBox>
#include <QStackedWidget>
#include "dataset.hpp"

class Page2Window : public QWidget {
Q_OBJECT

public:
    explicit Page2Window(QWidget* parent = nullptr);
    ~Page2Window();
    void loadData();
    // void showToolTip(QPointF point, bool state);
    void createPCBChart(const QString& samplingPoint);
    void attachAxesToSeries(
            QAbstractSeries* series,
            QDateTimeAxis* axisX,
            QValueAxis* axisY) const;
    QScatterSeries* createSeries(const QString& name, const QColor& color) const;

private:
    QLabel* pageLabel;
    QVBoxLayout* layout;
    QComboBox* chartSelector;
    QStackedWidget* chartStack;
    std::vector<WaterQuality> dataPoints;
    std::vector<WaterQuality> filteredData;
    WaterQualityDataset dataset;

private slots:
    void displaySelectedGraph(int index);
    void onPointHovered(const QPointF& point, bool state);
};

#endif // PAGE2_WINDOW_HPP