#include <stdexcept>
#include <sstream>
#include "water_quality.hpp"

using namespace std;

WaterQuality::WaterQuality(
        const string& id, const string& point, const string& pointNotation,
        const string& pointLabel, int easting, int northing, const string& time,
        const string& purpose, const string& determinand, const string& definition,
        const string& notation, const string& unit, const string& materialType,
        bool isComplianceSample, const string& resultQualifier, double result):
        id(id), samplingPoint(point), pointNotation(pointNotation),
        pointLabel(pointLabel), easting(easting), northing(northing),
        sampleTime(time), purpose(purpose), determinand(determinand),
        definition(definition), notation(notation), unit(unit),
        materialType(materialType), isComplianceSample(isComplianceSample),
        resultQualifier(resultQualifier), result(result)
{
    ostringstream error;

    // 校验 ID
    if (id.empty()) {
        error << "ID cannot be empty.";
        throw invalid_argument(error.str());
    }

    // 校验 Sampling Point
    if (pointLabel.empty()) {
        error << "Sampling point label cannot be empty.";
        throw invalid_argument(error.str());
    }

    // 校验 Result
    if (result < 0) {
        error << "Result value cannot be negative: " << result;
        throw out_of_range(error.str());
    }

    // 校验坐标
    if (easting <= 0 || northing <= 0) {
        error << "Invalid coordinates: Easting=" << easting
              << ", Northing=" << northing;
        throw out_of_range(error.str());
    }

    // 校验时间
    if (time.empty()) {
        error << "Sampling time cannot be empty.";
        throw invalid_argument(error.str());
    }

    // 校验单位
    if (unit.empty()) {
        error << "Unit cannot be empty.";
        throw invalid_argument(error.str());
    }
}

ostream& operator<<(ostream& out, const WaterQuality& record) {
    out << "ID:                   " << record.id << "\n"
        << "Sampling Point:       " << record.pointLabel
        << " (" << record.pointNotation << ")" << "\n"
        << "Coordinates:          (" << record.easting << ", " << record.northing << ")\n"
        << "Sampling Time:        " << record.sampleTime << "\n"
        << "Purpose:              " << record.purpose << "\n"
        << "Determinand:          " << record.determinand
        << " [" << record.notation << "] - " << record.definition << "\n"
        << "Result:               " << record.result
        << " " << record.unit;

    if (!record.resultQualifier.empty()) {
        out << " (" << record.resultQualifier << ")";
    }

    out << "\nMaterial Type:        " << record.materialType << "\n"
        << "Compliance Sample:    " << (record.isComplianceSample ? "Yes" : "No") << "\n";

    return out;
}