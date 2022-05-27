#ifndef __AIRCRAFT_CONFIG_HPP__
#define __AIRCRAFT_CONFIG_HPP__

#include "common/dataIdentifiers.hpp"

struct AircraftConfig
{
    int8_t numEngines = 1;
    AircraftType type = AircraftType::JET;

    // jet
    double n1Epsilon = 10000;
    double n2Epsilon = 10000;
    double ittEpsilon = 10000;

    // prop aircraft
    double rpmEpsilon = 10000;
    double powerEpsilon = 10000;
    double manPressEpsilon = 10000;
    double chtEpsilon = 10000;

    double trqEpsilon = 10000;

    // general
    double fuelFlowEpsilon = 10000;
    double egtEpsilon = 10000;
    double oilTempEpsilon = 10000;
    double oilPressEpsilon = 10000;

    double fuelQtyEpsilon = 10000;

    // jet aircraft
    TemperatureGaugeType ittGaugeType = TemperatureGaugeType::ITT;

    // prop aircraft
    bool hasRpm = true;
    bool usePropRpm = false;

    bool hasPower = false;
    bool powerAsPct = true;
    double maxPower = 1;

    bool hasManPress = true;
    bool hasCht = false;
    TemperatureGaugeType chtGaugeType = TemperatureGaugeType::CHT;

    // general
    bool fuelFlowByWeight = false;

    bool singleTank = false;
    bool fuelQtyByWeight = false;

    bool hasApu = false;
    bool hasEgt = false;
    TemperatureGaugeType egtGaugeType = TemperatureGaugeType::EGT;

    bool hasFlaps = false;
    bool hasSpoilers = false;

    bool hasElevTrim = false;
    bool hasRudderTrim = false;
    bool hasAileronTrim = false;


};



#endif  // __AIRCRAFT_CONFIG_HPP__