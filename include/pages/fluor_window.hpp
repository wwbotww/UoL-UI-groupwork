#ifndef FLUOR_WINDOW_HPP
#define FLUOR_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "dataset.hpp"

class FluorWindow : public QWidget {
Q_OBJECT

public:
    explicit FluorWindow(QWidget* parent = nullptr);
    ~FluorWindow();

private:
    QLabel* statsLabel;
    QVBoxLayout* layout;

    void loadFluorData();
};

#endif // FLUOR_WINDOW_HPP