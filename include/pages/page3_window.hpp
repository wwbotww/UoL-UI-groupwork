#ifndef PAGE3_WINDOW_HPP
#define PAGE3_WINDOW_HPP

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class Page3Window : public QWidget {
Q_OBJECT

public:
    explicit Page3Window(QWidget* parent = nullptr);
    ~Page3Window();

private:
    QLabel* pageLabel;
    QVBoxLayout* layout;
};

#endif // PAGE3_WINDOW_HPP