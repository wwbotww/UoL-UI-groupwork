#include "pages/page2_window.hpp"

Page2Window::Page2Window(QWidget* parent)
        : QWidget(parent),
          pageLabel(new QLabel(this)),
          layout(new QVBoxLayout(this))
{
    pageLabel->setText("This is Page 2. Display analysis and visualization here.");
    pageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(pageLabel);
    setLayout(layout);
}

Page2Window::~Page2Window() {}