#ifndef HOME_WINDOW_HPP
#define HOME_WINDOW_HPP

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <QLabel>

#include "fluor_window.hpp"
#include "page1_window.hpp"
#include "page2_window.hpp"
#include "page3_window.hpp"

class HomeWindow : public QMainWindow {
Q_OBJECT

public:
    explicit HomeWindow(QWidget* parent = nullptr);
    ~HomeWindow();

private slots:
    void showHomePage();
    void showFluorWindow();
    void showPage1();
    void showPage2();
    void showPage3();

private:
    QVBoxLayout* navLayout;
    QHBoxLayout* mainLayout;

    QWidget* centralWidget;
    QStackedWidget* stackedWidget;

    QPushButton* homeButton;
    QPushButton* fluorButton;
    QPushButton* page1Button;
    QPushButton* page2Button;
    QPushButton* page3Button;

    QWidget* homePage;
    FluorWindow* fluorPage;
    Page1Window* page1;
    Page2Window* page2;
    Page3Window* page3;
};

#endif // HOME_WINDOW_HPP