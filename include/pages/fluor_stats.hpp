#ifndef FLUOR_STATS_HPP
#define FLUOR_STATS_HPP

#include <vector>
#include <string>
#include "water_quality.hpp"

class FluorStats {
public:
    explicit FluorStats(const std::vector<WaterQuality>& data);

    // Calculate total count of fluor-based compounds
    int countFluorCompounds() const;

    // Get a list of all fluor compound names
    std::vector<std::string> getFluorCompoundNames() const;

private:
    std::vector<WaterQuality> fluorData;
};

#endif // FLUOR_STATS_HPP