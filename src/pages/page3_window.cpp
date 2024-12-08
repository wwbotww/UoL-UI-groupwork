#include "pages/page3_window.hpp"

Page3Window::Page3Window(QWidget* parent)
        : QWidget(parent),
          pageLabel(new QLabel(this)),
          layout(new QVBoxLayout(this))
{
    pageLabel->setText("This is Page 3. Display analysis and visualization here.");
    pageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(pageLabel);
    setLayout(layout);
}

Page3Window::~Page3Window() {}