#ifndef ENGINEDATADEFS_H
#define ENGINEDATADEFS_H

#include "sharedStructs.h"

struct AircraftCommonData
{
    double fuelQtyLeft = 0;
    double fuelQtyRight = 0;
    double fuelQtyTotal = 0;

    double engine1FuelFlow = 0;
    double engine2FuelFlow = 0;
    double engine3FuelFlow = 0;
    double engine4FuelFlow = 0;

    double engine1OilTemp = 0;
    double engine2OilTemp = 0;
    double engine3OilTemp = 0;
    double engine4OilTemp = 0;

    double engine1OilPress = 0;
    double engine2OilPress = 0;
    double engine3OilPress = 0;
    double engine4OilPress = 0;

    double apuRpmPct = 0;

    double flapsLeftAngle = 0;
    double flapsRightAngle = 0;

    double spoilersLeftPct = 0;
    double spoilersRightPct = 0;

    double elevTrimPct = 0;
    double rudderTrimPct = 0;
    double aileronTrimPct = 0;
};

struct JetData
{
    double engine1N1 = 0;
    double engine2N1 = 0;
    double engine3N1 = 0;
    double engine4N1 = 0;

    double engine1N2 = 0;
    double engine2N2 = 0;
    double engine3N2 = 0;
    double engine4N2 = 0;

    double engine1Itt = 0;
    double engine2Itt = 0;
    double engine3Itt = 0;
    double engine4Itt = 0;

    AircraftCommonData commonData;
};

struct PropData
{
    double engine1Rpm = 0;
    double engine2Rpm = 0;

    double engine1Second = 0;
    double engine2Second = 0;

    double engine1Egt = 0;
    double engine2Egt = 0;

    AircraftCommonData commonData;
};

struct TurbopropData
{
    double engine1N1 = 0;
    double engine2N1 = 0;

    double engine1Trq = 0;
    double engine2Trq = 0;

    double engine1Itt = 0;
    double engine2Itt = 0;

    double engine1Rpm = 0;
    double engine2Rpm = 0;

    double engine1Egt = 0;
    double engine2Egt = 0;

    AircraftCommonData commonData;
};


#endif   // ENGINEDATADEFS_H
