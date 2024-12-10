#ifndef PAGE1_WINDOW_HPP
#define PAGE1_WINDOW_HPP

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class Page1Window : public QWidget {
Q_OBJECT

public:
    explicit Page1Window(QWidget* parent = nullptr);
    ~Page1Window();

private:
    QLabel* pageLabel;
    QVBoxLayout* layout;
};

#endif // PAGE1_WINDOW_HPP