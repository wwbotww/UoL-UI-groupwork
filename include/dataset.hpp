#pragma once

#include <vector>
#include <string>
#include "water_quality.hpp"

class WaterQualityDataset {
public:
    void loadData(const std::string& filename);

    // Filtering data of determinand.definition which contains "fluor"
    std::vector<WaterQuality> filterByFluorInDefinition() const;

    // Filtering For POPs
    std::vector<WaterQuality> filterForPOPs() const;
    
    const std::vector<WaterQuality>& getData() const { return data; }

//    std::vector<WaterQuality> filterForLitter() const;
//    std::map<std::string, double> summarizeLitterByLocation() const;
//    std::map<std::string, bool> checkComplianceWithEUStandards() const;
//    std::vector<WaterQuality> filterByLocationOrLitter(const std::string& location, const std::string& litterType) const;


private:
    std::vector<WaterQuality> data;

};
