#ifndef __AIRSPEED_DATASTRUCT_HPP__
#define __AIRSPEED_DATASTRUCT_HPP__

#include <cstdint>

namespace airspeed
{

struct DataStruct
{
    double airspeed = 0;
    double maxSpeed = 0;

    int32_t trueAirspeed = 0;
    int32_t refSpeed = 0;
};

}  // namespace airspeed

#endif  // __AIRSPEED_DATASTRUCT_HPP__