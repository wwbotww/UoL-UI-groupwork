#include <iostream>
#include "dataset.hpp"

int main() {
    WaterQualityDataset dataset;

    try {
        // Loading CSV data
        dataset.loadData("/Users/young/Desktop/UoL-UI-groupwork/data/water_quality.csv");

        // Filtering data of determinand.definition which contains "fluor"
        auto filteredRecords = dataset.filterByFluorInDefinition();

        // 输出筛选结果
        std::cout << "Records containing 'fluor' in definition:\n";
        for (const auto& record : filteredRecords) {
            std::cout << record << "\n";  // Print outcome
        }

        if (filteredRecords.empty()) {
            std::cout << "No records found containing 'fluor' in definition.\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}