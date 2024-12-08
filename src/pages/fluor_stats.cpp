#include "pages/fluor_stats.hpp"

FluorStats::FluorStats(const std::vector<WaterQuality>& data) {
    // Filter data to only include fluor-based compounds
    for (const auto& record : data) {
        if (record.getDefinition().find("fluor") != std::string::npos ||
            record.getDefinition().find("Fluor") != std::string::npos) {
            fluorData.push_back(record);
        }
    }
}

int FluorStats::countFluorCompounds() const {
    return static_cast<int>(fluorData.size());
}

std::vector<std::string> FluorStats::getFluorCompoundNames() const {
    std::vector<std::string> names;
    for (const auto& record : fluorData) {
        names.push_back(record.getDeterminand());
    }
    return names;
}