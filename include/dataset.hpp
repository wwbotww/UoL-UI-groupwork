#pragma once

#include <vector>
#include <string>
#include "water_quality.hpp"

class WaterQualityDataset {
public:
    void loadData(const std::string& filename);

    // Filtering data of determinand.definition which contains "fluor"
    std::vector<WaterQuality> filterByFluorInDefinition() const;

    const std::vector<WaterQuality>& getData() const { return data; }

private:
    std::vector<WaterQuality> data;
};
