#include "pages/page1_window.hpp"
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QVBoxLayout>

using namespace QtCharts;

//constructor
Page1Window::Page1Window(QWidget* parent)
        : QWidget(parent),
          pageLabel(new QLabel(this)),
          layout(new QVBoxLayout(this)),
          litterTable(new QTableWidget(this)),
          chartView(new QChartView(this)),
          filterComboBox(new QComboBox(this)),
          refreshButton(new QPushButton("Refresh", this))
          
{
    pageLabel->setText("This is Page 1. Display analysis and visualization here.");
    pageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(pageLabel);
    setLayout(layout);
}

Page1Window::~Page1Window() {}
