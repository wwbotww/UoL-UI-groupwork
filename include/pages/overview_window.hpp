#ifndef OVERVIEW_WINDOW_HPP
#define OVERVIEW_WINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWebEngineView>
#include <QFile>

class OverviewWindow : public QWidget {
Q_OBJECT

public:
    explicit OverviewWindow(QWidget* parent = nullptr);

    ~OverviewWindow() override = default;

signals:
    void showFluorPage(); // 点击 Fluor 模块的按钮信号
    void showPage1();
    void showPage2();
    void showPage3();

private slots:
    void displayFluorDataOnMap(); // 在地图上显示 FluorPage 的数据点

    void displayPage1DataOnMap();

    void displayPage2DataOnMap();

    void displayPage3DataOnMap();

private:
    QWebEngineView* mapView; // 地图视图
    QLabel* fluorDataLabel;
    QPushButton* fluorDataButton;

    QString fluorDataPoints; // FluorPage 数据点的 JavaScript 数据

    QLabel *page1DataLabel;     // 显示 Page1 数据条目的标签
    QPushButton *page1DataButton; // 加载 Page1 数据的按钮

    QLabel *page2DataLabel;     // 显示 Page2 数据条目的标签
    QPushButton *page2DataButton; // 加载 Page2 数据的按钮

    QLabel *page3DataLabel;     // 显示 Page3 数据条目的标签
    QPushButton *page3DataButton; // 加载 Page3 数据的按钮
};

#endif // OVERVIEW_WINDOW_HPP