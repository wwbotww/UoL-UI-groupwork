#ifndef FLUOR_STATS_HPP
#define FLUOR_STATS_HPP

#include <vector>
#include <QString>
#include <utility> // for std::pair

class FluorStats {
public:
    // 静态方法：转换 BNG 坐标为经纬度
    static std::vector<std::pair<double, double>> convertBNGToLatLng(const std::vector<std::pair<int, int>>& bngCoords);

    // 新方法：加载 Fluor 数据并返回 JavaScript 格式的经纬度数据点
    static QString loadFluorDataAsJSArray(const std::string& filePath);
    static QString loadPOPDataAsJSArray(const std::string& filePath);
    static QString loadLitterDataAsJSArray(const std::string& filePath);
    };

#endif // FLUOR_STATS_HPP