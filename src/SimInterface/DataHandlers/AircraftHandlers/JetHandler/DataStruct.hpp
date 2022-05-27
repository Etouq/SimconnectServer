#ifndef __JET_AIRCRAFT_DATASTRUCT_HPP__
#define __JET_AIRCRAFT_DATASTRUCT_HPP__

#include <cstdint>
#include "../AircraftBase/DataStruct.hpp"

namespace aircraft::jet
{

struct EngineStruct
{
    double n1 = 0;
    double n2 = 0;
    double itt = 0;

    base::EngineCommon common;
};

}  // namespace aircraft::jet

#endif  // __JET_AIRCRAFT_DATASTRUCT_HPP__