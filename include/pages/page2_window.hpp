#ifndef PAGE2_WINDOW_HPP
#define PAGE2_WINDOW_HPP

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPointF>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
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

private:
    QLabel* pageLabel;
    QVBoxLayout* layout;
    QComboBox* chartSelector;
    QStackedWidget* chartStack;
    std::vector<WaterQuality> filteredData;
    WaterQualityDataset dataset;

private slots:
    void displaySelectedGraph(int index); // Slot for handling dropdown selection
};

#endif // PAGE2_WINDOW_HPP