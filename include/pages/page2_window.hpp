#ifndef PAGE2_WINDOW_HPP
#define PAGE2_WINDOW_HPP

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class Page2Window : public QWidget {
Q_OBJECT

public:
    explicit Page2Window(QWidget* parent = nullptr);
    ~Page2Window();

private:
    QLabel* pageLabel;
    QVBoxLayout* layout;
};

#endif // PAGE2_WINDOW_HPP