#include "pages/fluor_window.hpp"

// Constructor
FluorWindow::FluorWindow(const FluorStats& stats, QWidget* parent)
        : QMainWindow(parent), statsLabel(new QLabel(this)), layout(new QVBoxLayout) {
    // Create a central widget and set layout
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Display fluor compound statistics
    QString statsText = QString("Number of fluor-based compounds: %1")
            .arg(stats.countFluorCompounds());
    statsLabel->setText(statsText);
    layout->addWidget(statsLabel);

    // Set window title and size
    setWindowTitle("Fluor Compound Statistics");
    resize(400, 300);
}

// Destructor implementation
FluorWindow::~FluorWindow() {}