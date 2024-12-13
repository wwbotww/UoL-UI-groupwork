#ifndef POLLUTANT1_H
#define POLLUTANT1_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>  // Include for layout
#include <QHBoxLayout>
#include <QDateEdit>

class pollutant1 : public QDialog
{
    Q_OBJECT

public:
    explicit pollutant1(const QString &pollutantName, const QStringList &headers,
                        const QList<QStringList> &data, QWidget *parent = nullptr);
    void setupTable(const QString &pollutantName, const QList<QStringList> &data);
    void filterByDate();
    void createChartWithFilteredData(const QVector<QPair<qint64, double>> &filteredPoints);

private:
    QTableWidget *pollutantTable;
    QHBoxLayout *mainLayout;  // Declare layout for the dialog
    QStringList tableHeaders;
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    QPushButton *filterButton;
};

#endif // POLLUTANT1_H
