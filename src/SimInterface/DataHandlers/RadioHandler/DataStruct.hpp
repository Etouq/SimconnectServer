#ifndef __RADIO_DATASTRUCT_HPP__
#define __RADIO_DATASTRUCT_HPP__

#include <cstdint>

namespace radio
{

struct DataStruct
{
    float com1Freq = 0;
    float com2Freq = 0;

    float nav1Freq = 0;
    float nav2Freq = 0;

    float com1Stby = 0;
    float com2Stby = 0;

    float nav1Stby = 0;
    float nav2Stby = 0;

    int32_t xpdrCode = 0;
    int32_t xpdrState = 0;
};

}  // namespace radio

#endif  // __RADIO_DATASTRUCT_HPP__