#ifndef PAGE1_WINDOW_HPP
#define PAGE1_WINDOW_HPP

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QChartView>
#include <QValueAxis>
#include <map>
#include <string>
#include <vector>
#include "dataset.hpp"

QT_BEGIN_NAMESPACE
class QPushButton;
class QComboBox;
QT_END_NAMESPACE

class Page1Window : public QWidget {
Q_OBJECT

public:
    //constructor
    explicit Page1Window(QWidget* parent = nullptr);
    //Destructor
    ~Page1Window();
    void updateTranslations();

private slots:
    //slot to update the displayed data based on filters
    void updateDashboard();

private:
    //ui elements
    QLabel* pageLabel;
    QVBoxLayout* layout;
    QTableWidget* litterTable;
    QChartView* chartView;
    QComboBox* filterComboBox;
    QPushButton* refreshButton;

    QChart *chart;
    QValueAxis *axisY;

    WaterQualityDataset dataset;
    void loadData();
    void createTable(const std::map<std::string, double> &data);
    void createChart(const std::map<std::string, double> &data);

};

#endif // PAGE1_WINDOW_HPP
