#include <stdexcept>
#include <sstream>
#include "water_quality.hpp"

using namespace std;

WaterQuality::WaterQuality(
        const string& id, const string& samplingPoint, const string& pointNotation,
        const string& pointLabel, int easting, int northing, const string& sampleTime,
        const string& purpose, const string& determinand, const string& definition,
        const string& notation, const string& unit, const string& materialType,
        bool isComplianceSample, const string& resultQualifier, double result)
        :
        id(id), samplingPoint(samplingPoint), pointNotation(pointNotation),
        pointLabel(pointLabel), easting(easting), northing(northing),
        sampleTime(sampleTime), purpose(purpose), determinand(determinand),
        definition(definition), notation(notation), unit(unit),
        materialType(materialType), isComplianceSample(isComplianceSample),
        resultQualifier(resultQualifier), result(result)
{
    ostringstream error;

    if (easting <= 0 || northing <= 0) {
        error << "Invalid coordinates: Easting=" << easting
              << ", Northing=" << northing;
        throw out_of_range(error.str());
    }
}

ostream& operator<<(ostream& out, const WaterQuality& record) {
    out << "ID:                   " << record.getId() << "\n"
        << "Sampling Point:       " << record.getSamplingPoint()
        << " (" << record.getPointNotation() << ")" << "\n"
        << "Coordinates:          (" << record.getEasting() << ", " << record.getNorthing() << ")\n"
        << "Sampling Time:        " << record.getSampleTime() << "\n"
        << "Purpose:              " << record.getPurpose() << "\n"
        << "Determinand:          " << record.getDeterminand()
        << " [" << record.getNotation() << "] - " << record.getDefinition() << "\n"
        << "Result:               " << record.getResult()
        << " " << record.getUnit();

    if (!record.getResultQualifier().empty()) {
        out << " (" << record.getResultQualifier() << ")";
    }

    out << "\nMaterial Type:        " << record.getMaterialType() << "\n"
        << "Compliance Sample:    " << (record.isCompliance() ? "Yes" : "No") << "\n";

    return out;
}