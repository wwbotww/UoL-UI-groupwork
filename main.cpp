#include <QApplication>
#include "pages/home_window.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    HomeWindow window;
    window.show();
    return app.exec();
}