#include "pages/fluor_stats.hpp"
#include "dataset.hpp"
#include <QList>
#include <cmath> // For mathematical functions
#include <vector>
#include <utility>

static const double a = 6377563.396;  // OSGB36 Semi-major axis
static const double b = 6356256.909;  // OSGB36 Semi-minor axis
static const double F0 = 0.9996012717; // Scale factor on the central meridian
static const double lat0 = 49 * M_PI / 180; // Latitude of true origin (radians)
static const double lon0 = -2 * M_PI / 180; // Longitude of true origin (radians)
static const double N0 = -100000;          // Northing of true origin
static const double E0 = 400000;           // Easting of true origin
static const double e2 = 1 - (b * b) / (a * a); // Ellipsoid eccentricity squared
static const double n = (a - b) / (a + b);
static const double n2 = n * n;
static const double n3 = n * n * n;

// Convert Easting/Northing (BNG) to Lat/Lng (OSGB36)
std::pair<double, double> bngToLatLng(int E, int N) {
    double lat = lat0;
    double M = 0;
    do {
        lat = (N - N0 - M) / (a * F0) + lat;

        const double sinLat = std::sin(lat);
        const double cosLat = std::cos(lat);
        const double nu = a * F0 / std::sqrt(1 - e2 * sinLat * sinLat);
        const double rho = a * F0 * (1 - e2) / std::pow(1 - e2 * sinLat * sinLat, 1.5);
        const double eta2 = nu / rho - 1;

        const double Ma = (1 + n + (5.0 / 4.0) * n2 + (5.0 / 4.0) * n3) * (lat - lat0);
        const double Mb = (3 * n + 3 * n * n + (21.0 / 8.0) * n3) * std::sin(lat - lat0) * std::cos(lat + lat0);
        const double Mc = ((15.0 / 8.0) * n2 + (15.0 / 8.0) * n3) * std::sin(2 * (lat - lat0)) * std::cos(2 * (lat + lat0));
        const double Md = (35.0 / 24.0) * n3 * std::sin(3 * (lat - lat0)) * std::cos(3 * (lat + lat0));
        M = b * F0 * (Ma - Mb + Mc - Md);
    } while (N - N0 - M >= 0.00001); // Iterate until desired precision is achieved

    const double sinLat = std::sin(lat);
    const double cosLat = std::cos(lat);
    const double tanLat = std::tan(lat);
    const double nu = a * F0 / std::sqrt(1 - e2 * sinLat * sinLat);
    const double rho = a * F0 * (1 - e2) / std::pow(1 - e2 * sinLat * sinLat, 1.5);
    const double eta2 = nu / rho - 1;

    const double secLat = 1.0 / cosLat;
    const double VII = tanLat / (2 * rho * nu);
    const double VIII = tanLat / (24 * rho * nu * nu * nu) * (5 + 3 * tanLat * tanLat + eta2 - 9 * tanLat * tanLat * eta2);
    const double IX = tanLat / (720 * rho * nu * nu * nu * nu * nu) * (61 + 90 * tanLat * tanLat + 45 * tanLat * tanLat * tanLat * tanLat);
    const double X = secLat / nu;
    const double XI = secLat / (6 * nu * nu * nu) * (nu / rho + 2 * tanLat * tanLat);
    const double XII = secLat / (120 * nu * nu * nu * nu * nu) * (5 + 28 * tanLat * tanLat + 24 * tanLat * tanLat * tanLat * tanLat);
    const double XIIA = secLat / (5040 * nu * nu * nu * nu * nu * nu * nu) * (61 + 662 * tanLat * tanLat + 1320 * tanLat * tanLat * tanLat * tanLat + 720 * tanLat * tanLat * tanLat * tanLat * tanLat * tanLat);

    const double dE = E - E0;
    const double latOSGB36 = lat - VII * dE * dE + VIII * dE * dE * dE * dE - IX * dE * dE * dE * dE * dE * dE;
    const double lonOSGB36 = lon0 + X * dE - XI * dE * dE * dE + XII * dE * dE * dE * dE * dE - XIIA * dE * dE * dE * dE * dE * dE * dE;

    // Convert OSGB36 to WGS84 (approximation)
    const double latWGS84 = latOSGB36 + 0.00020; // Simplified shift
    const double lonWGS84 = lonOSGB36 - 0.00006;

    return {latWGS84 * 180 / M_PI, lonWGS84 * 180 / M_PI}; // Convert radians to degrees
}

// 批量转换 BNG 坐标
std::vector<std::pair<double, double>> FluorStats::convertBNGToLatLng(const std::vector<std::pair<int, int>>& bngCoords) {
    std::vector<std::pair<double, double>> latLngCoords;
    for (const auto& coord : bngCoords) {
        latLngCoords.push_back(bngToLatLng(coord.first, coord.second));
    }
    return latLngCoords;
}

QString FluorStats::loadFluorDataAsJSArray(const std::string& filePath) {
    // 加载数据集
    WaterQualityDataset dataset;
    dataset.loadData(filePath);

    // 筛选含有 "fluor" 的记录
    auto filteredRecords = dataset.filterByFluorInDefinition();

    // 提取 BNG 坐标 (easting, northing)
    std::vector<std::pair<int, int>> bngCoords;
    for (const auto& record : filteredRecords) {
        bngCoords.emplace_back(record.getEasting(), record.getNorthing());
    }

    // 转换为经纬度
    auto latLngCoords = FluorStats::convertBNGToLatLng(bngCoords);

    // 转换为 JavaScript 格式的数组字符串
    QStringList locationData;
    for (const auto& coord : latLngCoords) {
        locationData << QString("{lat: %1, lng: %2}").arg(coord.first).arg(coord.second);
    }

    return "[" + locationData.join(",") + "]"; // 返回 JavaScript 数据点数组
}