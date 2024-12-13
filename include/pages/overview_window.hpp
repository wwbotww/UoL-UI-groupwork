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
    void updateTranslations();

    ~OverviewWindow() override = default;

signals:
    void showFluorPage();
    void showPage1();
    void showPage2();
    void showPage3();

private slots:
    void displayFluorDataOnMap(); // Display data points for FluorPage on the map

    void displayPage1DataOnMap(); // Display data points for Page1 on the map

    void displayPage2DataOnMap(); // Display data points for Page2 on the map

    void displayPage3DataOnMap(); // Display data points for Page3 on the map

private:
    QWebEngineView* mapView; // Map view
    QLabel* fluorDataLabel;
    QPushButton* fluorDataButton;
    QPushButton* page1Button;
    QPushButton* page2Button;
    QPushButton* page3Button;

    QString fluorDataPoints; // JavaScript data points for FluorPage

    QLabel *page1DataLabel;     // Label to display data entries for Page1
    QPushButton *page1DataButton; // Button to load data for Page1

    QLabel *page2DataLabel;     // Label to display data entries for Page2
    QPushButton *page2DataButton; // Button to load data for Page2

    QLabel *page3DataLabel;     // Label to display data entries for Page3
    QPushButton *page3DataButton; // Button to load data for Page3
};

#endif // OVERVIEW_WINDOW_HPP