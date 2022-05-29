#include "TurbopropHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace aircraft::turboprop
{

QByteArray TurbopropHandler::sendCurrentData()
{
    QByteArray dataToSend = sendCurrentDataBase();

    SimconnectIds id;
    for (uint8_t engineIdx = 1; engineIdx <= 4; ++engineIdx)
    {
        EngineStruct engine = engineIdx == 1 ? d_engine1
          : engineIdx == 2                   ? d_engine2
          : engineIdx == 3                   ? d_engine3
                                             : d_engine4;

        id = SimconnectIds::ENGINE_N1;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&engineIdx), sizeof(engineIdx));
        dataToSend.append(reinterpret_cast<const char *>(&engine.n1), sizeof(engine.n1));


        id = SimconnectIds::ENGINE_TRQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&engineIdx), sizeof(engineIdx));
        dataToSend.append(reinterpret_cast<const char *>(&engine.trq), sizeof(engine.trq));

        id = SimconnectIds::ENGINE_ITT;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&engineIdx), sizeof(engineIdx));
        dataToSend.append(reinterpret_cast<const char *>(&engine.itt), sizeof(engine.itt));

        id = SimconnectIds::ENGINE_RPM;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&engineIdx), sizeof(engineIdx));
        dataToSend.append(reinterpret_cast<const char *>(&engine.rpm), sizeof(engine.rpm));

        sendCurrentEngineData(engine.common, dataToSend, engineIdx);
    }

    return dataToSend;
}

}  // namespace aircraft::turboprop
