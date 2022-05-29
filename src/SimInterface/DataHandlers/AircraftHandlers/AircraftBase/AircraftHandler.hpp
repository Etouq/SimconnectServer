#ifndef __AIRCRAFT_BASE_HANDLER__
#define __AIRCRAFT_BASE_HANDLER__

#include "DataStruct.hpp"
#include "../../../AircraftConfig.hpp"

#include <QByteArray>
#include <stdint.h>


typedef void *HANDLE;

struct AircraftConfig;

namespace aircraft::base
{

class AircraftHandler
{
protected:

    DataStruct d_previous;

    uint8_t d_numEngines = 1;

    double d_fuelFlowEps = 10000;
    double d_egtEps = 10000;
    double d_oilTempEps = 10000;
    double d_oilPressEps = 10000;

    double d_fuelQtyEps = 10000;

    bool d_fuelFlowByWeight = false;

    bool d_checkEgt = false;

    bool d_checkFlaps = true;
    bool d_checkSpoilers = true;
    double d_flapsAngle = 0;
    double d_spoilersPct = 0;

    bool d_checkElevTrim = true;
    bool d_checkRuddTrim = true;
    bool d_checkAilTrim = true;

    bool d_checkApu = false;

    bool d_singleTank = false;
    bool d_fuelQtyByWeight = false;

public:

    AircraftHandler() = default;
    virtual ~AircraftHandler() = default;

    virtual void setupData(HANDLE simConnectHandle, const AircraftConfig &config) = 0;

    [[nodiscard]] virtual QByteArray processData(const unsigned long *raw) = 0;

    virtual QByteArray reset() = 0;

    [[nodiscard]] virtual QByteArray sendCurrentData() = 0;

protected:

    void copyConfig(const AircraftConfig &config)
    {
        d_singleTank = config.singleTank;
        d_fuelQtyByWeight = config.fuelQtyByWeight;

        d_checkEgt = config.hasEgt;

        d_checkFlaps = config.hasFlaps;
        d_checkSpoilers = config.hasSpoilers;

        d_checkElevTrim = config.hasElevTrim;
        d_checkRuddTrim = config.hasRudderTrim;
        d_checkAilTrim = config.hasAileronTrim;

        d_fuelFlowEps = config.fuelFlowEpsilon;
        d_egtEps = d_checkEgt ? config.egtEpsilon : 10000;
        d_oilTempEps = config.oilTempEpsilon;
        d_oilPressEps = config.oilPressEpsilon;

        d_fuelQtyEps = config.fuelQtyEpsilon;
        d_fuelFlowByWeight = config.fuelFlowByWeight;
    }

    void setupDataBase(HANDLE simConnectHandle);

    void setupEngineCommon(HANDLE simConnectHandle, const AircraftConfig &config, const uint8_t idx);

    [[nodiscard]] QByteArray processDataBase(const unsigned long *raw);

    void resetBase()
    {
        d_previous = DataStruct();

        d_numEngines = 1;

        d_fuelFlowEps = 10000;
        d_egtEps = 10000;
        d_oilTempEps = 10000;
        d_oilPressEps = 10000;

        d_fuelQtyEps = 10000;

        d_checkEgt = false;

        d_checkFlaps = true;
        d_checkSpoilers = false;
        d_flapsAngle = 0;
        d_spoilersPct = 0;

        d_checkElevTrim = true;
        d_checkRuddTrim = true;
        d_checkAilTrim = true;

        d_checkApu = false;

        d_singleTank = false;
        d_fuelQtyByWeight = false;
    }

    void sendCurrentEngineData(const EngineCommon &data, QByteArray &dataToSend, const uint8_t engineIdx);

    [[nodiscard]] QByteArray sendCurrentDataBase();

    void processEngine(EngineCommon &newData, const uint8_t engineIdx, EngineCommon &previous, QByteArray &dataToSend);
};

}  // namespace aircraft::base


#endif  // __AIRCRAFT_BASE_HANDLER__