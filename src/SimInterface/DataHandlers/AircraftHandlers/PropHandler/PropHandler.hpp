#ifndef __AIRCRAFT_PROP_HANDLER__
#define __AIRCRAFT_PROP_HANDLER__

#include "DataStruct.hpp"
#include "../AircraftBase/AircraftHandler.hpp"

#include <QByteArray>
#include <stdint.h>


typedef void *HANDLE;

struct AircraftConfig;

namespace aircraft::prop
{

class PropHandler : public base::AircraftHandler
{

    EngineStruct d_engine1;
    EngineStruct d_engine2;
    EngineStruct d_engine3;
    EngineStruct d_engine4;

    double d_rpmEps = 10000;
    double d_powerEps = 10000;
    double d_manPressEps = 10000;
    double d_chtEps = 10000;

    bool d_powerAsPct = false;
    double d_maxPower = 1;

    bool d_checkRpm = true;
    bool d_checkPower = false;
    bool d_checkManPress = true;
    bool d_checkCht = false;

public:

    PropHandler() = default;

    void setupData(HANDLE simConnectHandle, const AircraftConfig &config);

    [[nodiscard]] QByteArray processData(const unsigned long *raw);

    QByteArray reset()
    {
        resetBase();
        d_engine1 = EngineStruct();
        d_engine2 = EngineStruct();
        d_engine3 = EngineStruct();
        d_engine4 = EngineStruct();

        d_rpmEps = 10000;
        d_powerEps = 10000;
        d_manPressEps = 10000;
        d_chtEps = 10000;

        d_powerAsPct = false;
        d_maxPower = 1;

        d_checkRpm = true;
        d_checkPower = false;
        d_checkManPress = true;
        d_checkCht = false;

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();

private:

    void processEngine(const unsigned long *raw,
                       const uint8_t engineIdx,
                       EngineStruct &previous,
                       QByteArray &dataToSend);
};

}  // namespace aircraft::prop


#endif  // __AIRCRAFT_PROP_HANDLER__