
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>  // Include for QFileDialog

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the central widget and its layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Add a title
    QLabel *title = new QLabel("Pollutant Overview", this);
    QFont titleFont("Times New Roman", 16, QFont::Bold);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    // Create a horizontal layout for the buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *pollutant1Button = new QPushButton("View Details for Endrin", this);
    connect(pollutant1Button, &QPushButton::clicked, this, [=]() {
        pollutant1 *page = new pollutant1("Endrin", tableHeaders, csvData, this);  // Pass headers and data
        page->exec();
    });
    buttonLayout->addWidget(pollutant1Button);

    QPushButton *pollutant2Button = new QPushButton("View Details for 1,1,2-Trichloroethane", this);
    connect(pollutant2Button, &QPushButton::clicked, this, [=]() {
        pollutant1 *page = new pollutant1("112TCEthan", tableHeaders, csvData, this);  // Pass headers and data
        page->exec();
    });
    buttonLayout->addWidget(pollutant2Button);

    QPushButton *pollutant3Button = new QPushButton("View Details for Chloroform", this);
    connect(pollutant3Button, &QPushButton::clicked, this, [=]() {
        pollutant1 *page = new pollutant1("Chloroform", tableHeaders, csvData, this);  // Pass headers and data
        page->exec();
    });
    buttonLayout->addWidget(pollutant3Button);

    QPushButton *pollutant4Button = new QPushButton("View Details for BOD ATU", this);
    connect(pollutant4Button, &QPushButton::clicked, this, [=]() {
        pollutant1 *page = new pollutant1("BOD ATU", tableHeaders, csvData, this);  // Pass headers and data
        page->exec();
    });
    buttonLayout->addWidget(pollutant4Button);

    // Add the button layout to the main layout
    mainLayout->addLayout(buttonLayout);

    // Create "Load CSV" button
    QPushButton *loadCSVButton = new QPushButton("Load CSV Data", this);
    connect(loadCSVButton, &QPushButton::clicked, this, &MainWindow::loadCSVDialog);
    mainLayout->addWidget(loadCSVButton);

    // Add a search bar
    QLineEdit *searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search pollutants...");
    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::filterPollutants);
    mainLayout->addWidget(searchBar);

    // Add the compliance table
    complianceTable = new QTableWidget(this);
    complianceTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    complianceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    complianceTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    complianceTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mainLayout->addWidget(complianceTable);

    // Set the central widget with the main layout
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadCSVDialog()
{
    // Open a file dialog for CSV file selection
    QString filePath = QFileDialog::getOpenFileName(this, "Open CSV File", "", "CSV Files (*.csv);;All Files (*)");

    if (!filePath.isEmpty()) {
        loadCSVData(filePath);
    }
}

void MainWindow::loadCSVData(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open the file for reading:" << filePath;
        return;
    }

    QTextStream in(&file);
    tableHeaders.clear();
    csvData.clear();
    int row = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList columns = parseCSVLine(line);

        if (row == 0) {
            tableHeaders = columns;
            complianceTable->setColumnCount(columns.size());
            complianceTable->setHorizontalHeaderLabels(columns);
        } else {
            complianceTable->insertRow(row - 1);
            for (int col = 0; col < columns.size(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(columns[col]);
                complianceTable->setItem(row - 1, col, item);
            }
            csvData.append(columns);
        }
        ++row;
    }

    file.close();

    qDebug() << "CSV Data loaded:" << csvData;
}



QStringList MainWindow::parseCSVLine(const QString &line)
{
    QStringList result;
    QString currentField;
    bool insideQuotes = false;

    for (int i = 0; i < line.length(); ++i) {
        QChar currentChar = line[i];

        if (currentChar == '"' && (i == 0 || line[i - 1] != '\\')) {
            // Toggle the insideQuotes flag when encountering an unescaped quote
            insideQuotes = !insideQuotes;
        } else if (currentChar == ',' && !insideQuotes) {
            // If we encounter a comma and we're not inside quotes, it's a field separator
            result.append(currentField.trimmed());
            currentField.clear();
        } else {
            // Otherwise, add the character to the current field
            currentField.append(currentChar);
        }
    }

    // Add the last field
    result.append(currentField.trimmed());

    return result;
}

void MainWindow::filterPollutants(const QString &query)
{
    // Loop through all rows in the table
    for (int row = 0; row < complianceTable->rowCount(); ++row) {
        bool match = false;

        // Check all columns in the row for the query
        for (int col = 0; col < complianceTable->columnCount(); ++col) {
            QTableWidgetItem *item = complianceTable->item(row, col);
            if (item && item->text().contains(query, Qt::CaseInsensitive)) {
                match = true;
                break;  // No need to check further columns if we found a match
            }
        }

        // Show or hide the row based on whether it matches the query
        complianceTable->setRowHidden(row, !match);
    }
}
