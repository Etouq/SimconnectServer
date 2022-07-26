#ifndef __ENGINE_HANDLER_HPP__
#define __ENGINE_HANDLER_HPP__

#include "DataStruct.hpp"
#include "common/definitions/AircraftConfig.hpp"

#include <string>


typedef void *HANDLE;

struct AircraftConfig;

namespace handler::engine
{

class EngineHandler
{

public:

    constexpr EngineHandler(uint8_t engineIdx)
      : d_engineIdx(engineIdx)
    {
    }

    void setupData(HANDLE simConnectHandle, const AircraftConfig &config);

    [[nodiscard]] std::string processData(const unsigned long *raw);

    [[nodiscard]] std::string sendCurrentData();

    std::string reset()
    {
        d_previous = DataStruct();

        d_numGauges = 2;

        d_firstGaugeEpsilon = 10000;
        d_secondGaugeEpsilon = 10000;
        d_thirdGaugeEpsilon = 10000;
        d_fourthGaugeEpsilon = 10000;

        d_fuelFlowEpsilon = 10000;
        d_oilTempEpsilon = 10000;
        d_secondaryTempEpsilon = 10000;
        d_oilPressEpsilon = 10000;

        d_maxPower = 1;

        d_fuelFlowByWeight = false;

        d_hasSecondaryTempGauge = false;

        d_gauge1IsPowerPct = false;
        d_gauge2IsPowerPct = false;
        d_gauge3IsPowerPct = false;
        d_gauge4IsPowerPct = false;

        return sendCurrentData();
    }

private:

    std::string gaugeTypeToString(SwitchingGaugeType gaugeType, AircraftType aircraftType, TemperatureGaugeType tempGaugeType);
    std::string gaugeTypeToUnit(SwitchingGaugeType gaugeType);

    DataStruct d_previous;

    const uint8_t d_engineIdx;

    uint8_t d_numGauges = 2;

    double d_firstGaugeEpsilon = 10000;
    double d_secondGaugeEpsilon = 10000;
    double d_thirdGaugeEpsilon = 10000;
    double d_fourthGaugeEpsilon = 10000;

    double d_fuelFlowEpsilon = 10000;
    double d_oilTempEpsilon = 10000;
    double d_secondaryTempEpsilon = 10000;
    double d_oilPressEpsilon = 10000;

    double d_maxPower = 1;

    bool d_fuelFlowByWeight = false;

    bool d_hasSecondaryTempGauge = false;

    bool d_gauge1IsPowerPct = false;
    bool d_gauge2IsPowerPct = false;
    bool d_gauge3IsPowerPct = false;
    bool d_gauge4IsPowerPct = false;
};

}  // namespace handler::engine

#endif  // __ENGINE_HANDLER_HPP__