#include <QApplication>
#include <QTranslator>
#include "pages/home_window.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 加载系统默认语言
    QTranslator translator;
    QString locale = QLocale::system().name();
    qDebug() << "System Language:" << locale;

    HomeWindow window;
    window.show();
    return app.exec();
}