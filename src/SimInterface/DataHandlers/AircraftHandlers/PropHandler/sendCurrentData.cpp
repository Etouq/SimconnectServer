#include "PropHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

#include "SimInterface/DataHandlers/AircraftHandlers/PropHandler/DataStruct.hpp"

namespace aircraft::prop
{

QByteArray PropHandler::sendCurrentData()
{
    QByteArray dataToSend = sendCurrentDataBase();

    SimconnectIds id;
    for (uint8_t engineIdx = 1; engineIdx <= 4; ++engineIdx)
    {
        EngineStruct engine = engineIdx == 1 ? d_engine1
          : engineIdx == 2                   ? d_engine2
          : engineIdx == 3                   ? d_engine3
                                             : d_engine4;

        id = SimconnectIds::ENGINE_RPM;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&engineIdx), sizeof(engineIdx));
        dataToSend.append(reinterpret_cast<const char *>(&engine.rpm), sizeof(engine.rpm));

        double transformedValue = d_powerAsPct ? engine.power / d_maxPower : engine.power;
        id = SimconnectIds::ENGINE_POWER;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&engineIdx), sizeof(engineIdx));
        dataToSend.append(reinterpret_cast<const char *>(&transformedValue), sizeof(transformedValue));

        id = SimconnectIds::ENGINE_MANIFOLD_PRESSURE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&engineIdx), sizeof(engineIdx));
        dataToSend.append(reinterpret_cast<const char *>(&engine.manPress), sizeof(engine.manPress));

        id = SimconnectIds::ENGINE_CHT;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&engineIdx), sizeof(engineIdx));
        dataToSend.append(reinterpret_cast<const char *>(&engine.cht), sizeof(engine.cht));

        sendCurrentEngineData(engine.common, dataToSend, engineIdx);
    }


    return dataToSend;
}

}  // namespace aircraft::prop
