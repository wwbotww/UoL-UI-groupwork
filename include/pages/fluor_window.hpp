#ifndef FLUOR_WINDOW_HPP
#define FLUOR_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QWebEngineView>

class FluorWindow : public QWidget
{
Q_OBJECT

public:
    explicit FluorWindow(QWidget* parent = nullptr);
    ~FluorWindow();

private:
    QVBoxLayout* layout;         // 主布局
    QWebEngineView* webView;     // 地图的 Web 视图

    void loadFluorData();        // 加载并显示 Fluor 数据的函数
};

#endif // FLUOR_WINDOW_HPP