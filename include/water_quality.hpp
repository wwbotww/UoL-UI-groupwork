#pragma once

#include <string>
#include <iostream>

class WaterQuality {
public:
    WaterQuality(
            const std::string& id, const std::string& samplingPoint,
            const std::string& pointNotation, const std::string& pointLabel,
            int easting, int northing, const std::string& sampleTime,
            const std::string& purpose, const std::string& determinand,
            const std::string& definition, const std::string& notation,
            const std::string& unit, const std::string& materialType,
            bool isComplianceSample, const std::string& resultQualifier, double result
    );

    // Getter methods
    std::string getId() const { return id; }
    std::string getSamplingPoint() const { return samplingPoint; }
    std::string getPointNotation() const { return pointNotation; }
    std::string getPointLabel() const { return pointLabel; }
    int getEasting() const { return easting; }
    int getNorthing() const { return northing; }
    std::string getSampleTime() const { return sampleTime; }
    std::string getPurpose() const { return purpose; }
    std::string getDeterminand() const { return determinand; }
    std::string getDefinition() const { return definition; }
    std::string getNotation() const { return notation; }
    std::string getUnit() const { return unit; }
    std::string getMaterialType() const { return materialType; }
    bool isCompliance() const { return isComplianceSample; }
    std::string getResultQualifier() const { return resultQualifier; }
    double getResult() const { return result; }

private:
    std::string id;
    std::string samplingPoint;
    std::string pointNotation;
    std::string pointLabel;
    int easting;
    int northing;
    std::string sampleTime;
    std::string purpose;
    std::string determinand;
    std::string definition;
    std::string notation;
    std::string unit;
    std::string materialType;
    bool isComplianceSample;
    std::string resultQualifier;
    double result;
};

std::ostream& operator<<(std::ostream&, const WaterQuality&);