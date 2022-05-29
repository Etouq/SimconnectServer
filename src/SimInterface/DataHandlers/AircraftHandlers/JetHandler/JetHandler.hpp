#ifndef __AIRCRAFT_JET_HANDLER__
#define __AIRCRAFT_JET_HANDLER__

#include "DataStruct.hpp"
#include "../AircraftBase/AircraftHandler.hpp"

#include <QByteArray>
#include <stdint.h>


typedef void *HANDLE;

struct AircraftConfig;

namespace aircraft::jet
{

class JetHandler : public base::AircraftHandler
{

    EngineStruct d_engine1;
    EngineStruct d_engine2;
    EngineStruct d_engine3;
    EngineStruct d_engine4;


    double d_n1Eps = 10000;
    double d_n2Eps = 10000;
    double d_ittEps = 10000;

public:

    JetHandler() = default;

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
        d_n2Eps = 10000;
        d_ittEps = 10000;

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();

private:

    void processEngine(const unsigned long *raw,
                       const uint8_t engineIdx,
                       EngineStruct &previous,
                       QByteArray &dataToSend);
};

}  // namespace aircraft::jet


#endif  // __AIRCRAFT_JET_HANDLER__