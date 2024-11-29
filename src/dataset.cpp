#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "dataset.hpp"
#include "csv.hpp"

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