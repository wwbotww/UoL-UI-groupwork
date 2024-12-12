#ifndef HOME_WINDOW_HPP
#define HOME_WINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QWidget>
#include "pages/overview_window.hpp"
#include "pages/fluor_window.hpp"
#include "mainwindow.h"

class HomeWindow : public QMainWindow {
Q_OBJECT

public:
    explicit HomeWindow(QWidget* parent = nullptr);
    ~HomeWindow();

private slots:
    void showOverviewPage();
    void showFluorWindow();
    void showPage1();
    void showPage2();
//    void showPage3();
    void showPollutantWindow();

private:
    QWidget* centralWidget;
    QStackedWidget* stackedWidget;

    QPushButton* homeButton;
    QPushButton* fluorButton;
    QPushButton* page1Button;
    QPushButton* page2Button;
//    QPushButton* page3Button;
    QPushButton* pollutantButton;

    OverviewWindow* overviewPage;
    QWidget* fluorPage;
    QWidget* page1;
    QWidget* page2;
//    QWidget* page3;
    QWidget* pollutantPage;

    QVBoxLayout* navLayout;
    QHBoxLayout* mainLayout;
};

#endif // HOME_WINDOW_HPP