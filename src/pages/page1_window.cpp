#include "pages/page1_window.hpp"

Page1Window::Page1Window(QWidget* parent)
        : QWidget(parent),
          pageLabel(new QLabel(this)),
          layout(new QVBoxLayout(this))
{
    pageLabel->setText("This is Page 1. Display analysis and visualization here.");
    pageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(pageLabel);
    setLayout(layout);
}

Page1Window::~Page1Window() {}