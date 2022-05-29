#ifndef __AIRCRAFT_TURBOPROP_HANDLER__
#define __AIRCRAFT_TURBOPROP_HANDLER__

#include "DataStruct.hpp"
#include "../AircraftBase/AircraftHandler.hpp"

#include <QByteArray>
#include <stdint.h>


typedef void *HANDLE;

struct AircraftConfig;

namespace aircraft::turboprop
{

class TurbopropHandler : public base::AircraftHandler
{

    EngineStruct d_engine1;
    EngineStruct d_engine2;
    EngineStruct d_engine3;
    EngineStruct d_engine4;


    double d_n1Eps = 10000;
    double d_trqEps = 10000;
    double d_ittEps = 10000;
    double d_rpmEps = 10000;

    bool d_trqAsPct = true;

public:

    TurbopropHandler() = default;

    void setupData(HANDLE simConnectHandle, const AircraftConfig &config);

    [[nodiscard]] QByteArray processData(const unsigned long *raw);

    QByteArray reset()
    {
        resetBase();
        d_engine1 = EngineStruct();
        d_engine2 = EngineStruct();
        d_engine3 = EngineStruct();
        d_engine4 = EngineStruct();

        d_n1Eps = 10000;
        d_trqEps = 10000;
        d_ittEps = 10000;
        d_rpmEps = 10000;

        d_trqAsPct = true;

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();

private:

    void processEngine(const unsigned long *raw,
                       const uint8_t engineIdx,
                       EngineStruct &previous,
                       QByteArray &dataToSend);
};

}  // namespace aircraft::turboprop


#endif  // __AIRCRAFT_TURBOPROP_HANDLER__