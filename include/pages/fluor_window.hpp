#ifndef FLUOR_WINDOW_HPP
#define FLUOR_WINDOW_HPP

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include "fluor_stats.hpp"

class FluorWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit FluorWindow(const FluorStats& stats, QWidget* parent = nullptr);
    ~FluorWindow() override;  // Declare destructor

private:
    QLabel* statsLabel;  // Label to display basic stats
    QVBoxLayout* layout; // Layout for the window
};

#endif // FLUOR_WINDOW_HPP