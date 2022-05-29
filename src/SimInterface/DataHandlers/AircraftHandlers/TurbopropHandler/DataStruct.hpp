#ifndef __TURBOPROP_AIRCRAFT_DATASTRUCT_HPP__
#define __TURBOPROP_AIRCRAFT_DATASTRUCT_HPP__

#include <cstdint>
#include "../AircraftBase/DataStruct.hpp"

namespace aircraft::turboprop
{

struct EngineStruct
{
    double n1 = 0;
    double trq = 0;
    double itt = 0;
    double rpm = 0;

    base::EngineCommon common;
};

}  // namespace aircraft::turboprop

#endif  // __TURBOPROP_AIRCRAFT_DATASTRUCT_HPP__