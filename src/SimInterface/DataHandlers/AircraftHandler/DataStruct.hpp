#ifndef __AIRCRAFT_HANDLER_DATASTRUCT_HPP__
#define __AIRCRAFT_HANDLER_DATASTRUCT_HPP__

#include <cstdint>

namespace handler::aircraft
{

struct DataStruct
{
    double fuelLeftQty = 0;  // also serves as total when single tank
    double fuelRightQty = 0;

    double flapsLeftAngle = 0;
    double flapsRightAngle = 0;
    double spoilerLeftPos = 0;
    double spoilerRightPos = 0;

    double elevTrimPct = 0;
    double ruddTrimPct = 0;
    double ailTrimPct = 0;

    double apuN1 = 0;
    double fuelDensity = 1;

    int32_t elevTrimAngle = 0;
    int32_t ruddTrimAngle = 0;
    int32_t ailTrimAngle = 0;
};

}  // namespace handler::aircraft

#endif  // __AIRCRAFT_HANDLER_DATASTRUCT_HPP__