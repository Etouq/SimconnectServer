#ifndef __BASE_AIRCRAFT_DATASTRUCT_HPP__
#define __BASE_AIRCRAFT_DATASTRUCT_HPP__

#include <cstdint>

namespace aircraft::base
{

struct EngineCommon
{
    double fuelFlow = 0;
    double egt = 0;
    double oilTemp = 0;
    double oilPress = 0;
};

struct DataStruct
{
    double flapsLeftAngle = 0;
    double flapsRightAngle = 0;
    double spoilerLeftPos = 0;
    double spoilerRightPos = 0;

    double elevTrim = 0;
    double ruddTrim = 0;
    double ailTrim = 0;

    double fuelLeftQty = 0;
    double fuelRightQty = 0;
    double fuelTotalQty = 0;

    double apuN1 = 0;
    double fuelDensity = 1;
};

}  // namespace aircraft::base

#endif  // __BASE_AIRCRAFT_DATASTRUCT_HPP__