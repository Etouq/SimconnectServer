#ifndef __ENGINE_HANDLER_DATASTRUCT_HPP__
#define __ENGINE_HANDLER_DATASTRUCT_HPP__

#include <cstdint>

namespace handler::engine
{

struct DataStruct
{
    double firstGauge = 0;
    double secondGauge = 0;
    double thirdGauge = 0;
    double fourthGauge = 0;

    double fuelFlow = 0;
    double oilTemp = 0;
    double secondaryEngineTemp = 0;
    double oilPress = 0;
};

}  // namespace handler::engine

#endif  // __ENGINE_HANDLER_DATASTRUCT_HPP__