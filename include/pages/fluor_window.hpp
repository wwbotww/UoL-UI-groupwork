#ifndef FLUOR_WINDOW_HPP
#define FLUOR_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QWebEngineView>

class FluorWindow : public QWidget {
Q_OBJECT

public:
    explicit FluorWindow(QWidget* parent = nullptr);
    ~FluorWindow();

    void loadFluorData();

private:
    QVBoxLayout* layout;
    QLabel* statsLabel;         // 统计数据部分
    QWebEngineView* webView;    // Google 地图部分
};

#endif // FLUOR_WINDOW_HPP