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

        d_gauge1Factor = 1;
        d_gauge2Factor = 1;
        d_gauge3Factor = 1;
        d_gauge4Factor = 1;

        d_fuelFlowByWeight = false;

        d_hasSecondaryTempGauge = false;

        d_gauge1IsPct = false;
        d_gauge2IsPct = false;
        d_gauge3IsPct = false;
        d_gauge4IsPct = false;

        return sendCurrentData();
    }

private:

    std::string gaugeTypeToString(SwitchingGaugeType gaugeType, AircraftType aircraftType, TemperatureGaugeType tempGaugeType, Units unit);
    std::string gaugeTypeToUnit(SwitchingGaugeType gaugeType, AircraftType aircraftType, Units unit = Units::NONE);

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

    double d_gauge1Factor = 1;
    double d_gauge2Factor = 1;
    double d_gauge3Factor = 1;
    double d_gauge4Factor = 1;

    bool d_fuelFlowByWeight = false;

    bool d_hasSecondaryTempGauge = false;

    bool d_gauge1IsPct = false;
    bool d_gauge2IsPct = false;
    bool d_gauge3IsPct = false;
    bool d_gauge4IsPct = false;
};

}  // namespace handler::engine

#endif  // __ENGINE_HANDLER_HPP__