#ifndef __BOTTOMBAR_DATASTRUCT_HPP__
#define __BOTTOMBAR_DATASTRUCT_HPP__

#include <cstdint>

namespace bottombar
{

struct RawStruct
{
    int32_t zuluSeconds = 0;
    int32_t localSeconds = 0;

    int32_t groundSpeed = 0;
    float totalAirTemp = 0;
    float outsideAirTemp = 0;
    float stdAtmAirTemp = 0;
};

struct DataStruct
{
    int32_t zuluSeconds = 0;
    int32_t localSeconds = 0;

    int32_t groundSpeed = 0;
    float totalAirTemp = 0;
    float outsideAirTemp = 0;
    float isaAirTemp = 0;

    DataStruct() = default;

    DataStruct(RawStruct *data)
      : zuluSeconds(data->zuluSeconds),
        localSeconds(data->localSeconds),

        groundSpeed(data->groundSpeed),
        totalAirTemp(data->totalAirTemp),
        outsideAirTemp(data->outsideAirTemp),
        isaAirTemp(data->outsideAirTemp - data->stdAtmAirTemp)
    {}
};

}  // namespace bottombar

#endif  // __BOTTOMBAR_DATASTRUCT_HPP__