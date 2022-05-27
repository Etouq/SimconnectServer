#ifndef __PROP_AIRCRAFT_DATASTRUCT_HPP__
#define __PROP_AIRCRAFT_DATASTRUCT_HPP__

#include <cstdint>
#include "../AircraftBase/DataStruct.hpp"

namespace aircraft::prop
{

struct EngineStruct
{
    double rpm = 0;
    double power = 0;
    double manPress = 0;
    double cht = 0;

    base::EngineCommon common;
};


}  // namespace aircraft::prop

#endif  // __PROP_AIRCRAFT_DATASTRUCT_HPP__