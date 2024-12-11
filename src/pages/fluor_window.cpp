#include "pages/fluor_window.hpp"
#include "dataset.hpp"
#include "pages/fluor_stats.hpp"
#include <QFile>
#include <QDebug>
#include <QDir>

FluorWindow::FluorWindow(QWidget* parent)
        : QWidget(parent),
          webView(new QWebEngineView(this)),
          layout(new QVBoxLayout(this))
{
    layout->addWidget(webView);    // 地图部分
    setLayout(layout);

    // 加载 Fluor 数据
    loadFluorData();
}

FluorWindow::~FluorWindow() {}

void FluorWindow::loadFluorData() {
    // 检查当前工作目录
    QString currentDir = QDir::currentPath();
    qDebug() << "当前工作目录为:" << currentDir;

    // 构建 CSV 文件路径
    QString relativePath = "../data/water_quality.csv";
    QString absolutePath = QDir(currentDir).absoluteFilePath(relativePath);
    qDebug() << "CSV 文件的相对路径为:" << relativePath;
    qDebug() << "CSV 文件的绝对路径为:" << absolutePath;

    // 检查 CSV 文件是否存在
    if (!QFile::exists(absolutePath)) {
        qWarning() << "❌ CSV 文件不存在，路径为:" << absolutePath;
        return;
    } else {
        qDebug() << "✅ CSV 文件存在，路径为:" << absolutePath;
    }

    // 生成地图的 HTML 文件
    QFile file(":/html/map.html");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "❌ 无法打开 HTML 文件: :/html/map.html";
        return;
    }

    QString html = file.readAll();
    file.close();

    // 加载 Fluor 数据点
    QString jsArray = FluorStats::loadFluorDataAsJSArray(absolutePath.toStdString());
    if (jsArray.isEmpty()) {
        qWarning() << "❌ 没有加载到任何数据点";
    } else {
        qDebug() << "✅ 成功加载到数据点: " << jsArray;
    }

    // 将数据点嵌入 HTML 中
    html.replace("/*DATA_POINTS*/", jsArray); // 替换占位符
    webView->setHtml(html); // 在 QWebEngineView 中加载 HTML
    qDebug() << "✅ 地图已经加载，数据点已嵌入";
}