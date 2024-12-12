#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "dataset.hpp"
#include "csv.hpp"
#include <map>
#include <vector>

using namespace std;

void WaterQualityDataset::loadData(const std::string& filename) {
    csv::CSVReader reader(filename);

    data.clear();

    for (const auto& row : reader) {
        try {
            // Checking if it's empty
            if (row["@id"].is_null() ||
                row["sample.samplingPoint"].is_null() ||
                row["sample.samplingPoint.notation"].is_null() ||
                row["sample.samplingPoint.label"].is_null() ||
                row["sample.samplingPoint.easting"].is_null() ||
                row["sample.samplingPoint.northing"].is_null() ||
                row["sample.sampleDateTime"].is_null() ||
                row["sample.purpose.label"].is_null() ||
                row["determinand.label"].is_null() ||
                row["determinand.definition"].is_null() ||
                row["determinand.notation"].is_null() ||
                row["determinand.unit.label"].is_null() ||
                row["sample.sampledMaterialType.label"].is_null() ||
                row["sample.isComplianceSample"].is_null() ||
                row["result"].is_null()) {
                cerr << "Skipping row due to null values: " << endl;
                continue;  // Skip
            }

            bool isComplianceSample = false;
            string complianceSampleStr = row["sample.isComplianceSample"].get<>();
            if (complianceSampleStr == "TRUE" || complianceSampleStr == "true") {
                isComplianceSample = true;
            } else if (complianceSampleStr == "FALSE" || complianceSampleStr == "false") {
                isComplianceSample = false;
            } else {
                cerr << "Invalid boolean value in sample.isComplianceSample: " << complianceSampleStr << endl;
                continue;
            }

            WaterQuality record(
                    row["@id"].get<>(),
                    row["sample.samplingPoint"].get<>(),
                    row["sample.samplingPoint.notation"].get<>(),
                    row["sample.samplingPoint.label"].get<>(),
                    row["sample.samplingPoint.easting"].get<int>(),
                    row["sample.samplingPoint.northing"].get<int>(),
                    row["sample.sampleDateTime"].get<>(),
                    row["sample.purpose.label"].get<>(),
                    row["determinand.label"].get<>(),
                    row["determinand.definition"].get<>(),
                    row["determinand.notation"].get<>(),
                    row["determinand.unit.label"].get<>(),
                    row["sample.sampledMaterialType.label"].get<>(),
                    isComplianceSample,
                    row["resultQualifier.notation"].is_null() ? "" : row["resultQualifier.notation"].get<>(),
                    row["result"].get<double>()
            );

            data.push_back(record);
        } catch (const std::exception& e) {
            cerr << "Error loading row: " << e.what() << endl;
        }
    }
}

std::vector<WaterQuality> WaterQualityDataset::filterByFluorInDefinition() const {
    std::vector<WaterQuality> result;
    copy_if(data.begin(), data.end(), back_inserter(result),
            [](const WaterQuality& record) {
                return record.getDefinition().find("fluor") != std::string::npos ||
                       record.getDefinition().find("Fluor") != std::string::npos;
    });
    return result;
}

// Filter for POPs
std::vector<WaterQuality> WaterQualityDataset::filterForPOPs() const {
    std::vector<WaterQuality> result;
    copy_if(data.begin(), data.end(), back_inserter(result),
            [](const WaterQuality& record) {
                return record.getDeterminand().find("PCB") != std::string::npos;
            });
    return result;
}

//Functions for environmental litter indicator

//filtering dataset for visible litter pollutants

std::vector<WaterQuality> WaterQualityDataset::filterForLitter() const {
    std::vector<WaterQuality> result;
    copy_if(data.begin(), data.end(), back_inserter(result),
            [](const WaterQuality& record) {
                string definition = record.getDefinition();
                return definition.find("plastic") != std::string::npos ||
                       definition.find("debris") != std::string::npos ||
                       definition.find("litter") != std::string::npos;

    });
    return result;
}

//generating a summary for litter levels by sampling point
std::map<std::string, double> WaterQualityDataset::summarizeLitterByLocation() const {
    std::map<std::string, double> litterSummary;
    for (const auto& record : filterForLitter()) {
        double result = record.getResult();
        litterSummary[record.getSamplingPoint()] += result; // Aggregate litter levels
    }
    return litterSummary;
}

//generate compliance indicators for litter adherence to EU standards

std::map<std::string, bool> WaterQualityDataset::checkComplianceWithEUStandards() const {
    std::map<std::string, bool> compliance;
    for (const auto& record : filterForLitter()) {
        // Example compliance condition: result must be below 0.1 for visible litter
        bool isCompliant = record.getResult() < 0.1;
        compliance[record.getSamplingPoint()] = isCompliant;
    }
    return compliance;
}

//filtering data by location or type of litter
std::vector<WaterQuality> WaterQualityDataset::filterByLocationOrLitter(const std::string& location, const std::string& litterType) const {
    std::vector<WaterQuality> result;
    copy_if(data.begin(), data.end(), back_inserter(result),
            [&location, &litterType](const WaterQuality& record) {
                return record.getSamplingPoint().find(location) != std::string::npos &&
                       record.getDefinition().find(litterType) != std::string::npos;
            });
    return result;
}