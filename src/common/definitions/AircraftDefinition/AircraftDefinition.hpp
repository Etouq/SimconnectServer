#ifndef __AIRCRAFT_DEFINITION_HPP__
#define __AIRCRAFT_DEFINITION_HPP__

#include "common/TypeEnums.hpp"
#include "../GaugeDefinition/GaugeDefinition.hpp"

#include <QDebug>
#include <QList>



struct AircraftConfig;

namespace definitions
{

// definition containing all parameters used to display engine data of an aircraft
struct AircraftDefinition
{
    AircraftType type = AircraftType::INVALID;

    QString name = "";

    GaugeDefinition firstGauge;
    GaugeDefinition secondGauge;
    GaugeDefinition thirdGauge;
    GaugeDefinition fourthGauge;

    GaugeDefinition fuelQtyGauge;
    GaugeDefinition fuelFlowGauge;
    GaugeDefinition oilTempGauge;
    GaugeDefinition secondaryTempGauge;
    GaugeDefinition oilPressGauge;

    SwitchingGaugeType gauge1Type = SwitchingGaugeType::NONE;
    SwitchingGaugeType gauge2Type = SwitchingGaugeType::NONE;
    SwitchingGaugeType gauge3Type = SwitchingGaugeType::NONE;
    SwitchingGaugeType gauge4Type = SwitchingGaugeType::NONE;

    // never more than 1 of the switching gauges are a temperature type
    TemperatureGaugeType engineTempType = TemperatureGaugeType::ITT;

    double maxPower = 1;
    double maxTorque = 1;

    bool hasApu = false;

    bool hasFlaps = false;
    bool hasSpoilers = false;

    bool hasElevatorTrim = false;
    bool hasRudderTrim = false;
    bool hasAileronTrim = false;

    bool hasSecondaryTempGauge = false;
    TemperatureGaugeType secondaryTempType = TemperatureGaugeType::EGT;


    uint8_t numEngines = 1;
    bool singleTank = false;

    float lowLimit = 0;
    float flapsBegin = 0;
    float flapsEnd = 0;
    float greenBegin = 0;
    float greenEnd = 0;
    float yellowBegin = 0;
    float yellowEnd = 0;
    float redBegin = 0;
    float redEnd = 0;
    float highLimit = 0;

    bool noColors = false;
    bool hasLowLimit = true;
    bool hasFlapsSpeed = true;
    bool hasGreenSpeed = true;
    bool hasYellowSpeed = true;
    bool hasRedSpeed = true;
    bool hasHighLimit = true;

    bool dynamicBarberpole = false;

    QList<ReferenceSpeed> refSpeedDefaults = { { 85, "R" }, { 100, "X" }, { 124, "Y" }, { 85, "AP" } };

    QByteArray toBinary() const;

    AircraftConfig toConfig() const;

    bool fuelQtyByWeight() const;
    bool fuelFlowByWeight() const;

    static AircraftDefinition fromBinary(QIODevice &data, FileVersion version)
    {
        switch (version)
        {
            case FileVersion::V1:
                return fromBinaryV1(data, version);
            case FileVersion::V2:
                return fromBinaryV2(data, version);
            case FileVersion::V3:
                return fromBinaryV3(data, version);
            default:
                return AircraftDefinition();
        }
    }

    uint8_t numGauges() const
    {
        if (gauge3Type == SwitchingGaugeType::NONE)
            return 2;  // always at least 2, and no NONE gauges in between defined gauges
        if (gauge4Type == SwitchingGaugeType::NONE)
            return 3;

        return 4;
    }

private:

    static AircraftDefinition fromBinaryV1(QIODevice &data, FileVersion version);
    static AircraftDefinition fromBinaryV2(QIODevice &data, FileVersion version);
    static AircraftDefinition fromBinaryV3(QIODevice &data, FileVersion version);
};

}  // namespace definitions

#endif  // __AIRCRAFT_DEFINITION_HPP__