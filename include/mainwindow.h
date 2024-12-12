#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCharts>
#include <QtCore>
#include <QtGui>
#include <QLineEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QToolTip>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QDebug>
#include <QFileDialog>
#include <QVector>
#include "pollutant1.h"  // Include the correct header

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadCSVDialog();
    void loadCSVData(const QString &filePath);

private:
    Ui::MainWindow *ui;
    QTableWidget *complianceTable;
    QStringList tableHeaders;   // Declare tableHeaders to store column headers
    QList<QStringList> csvData; // Stores the loaded CSV data (each row is a QStringList)


    void filterPollutants(const QString &query);
    QStringList parseCSVLine(const QString &line);
};

#endif // MAINWINDOW_H
