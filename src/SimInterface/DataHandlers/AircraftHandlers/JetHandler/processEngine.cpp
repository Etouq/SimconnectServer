#include "JetHandler.hpp"
#include "SimInterface/DataHandlers/AircraftHandlers/AircraftBase/AircraftHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>
#include <stdint.h>

#include "SimInterface/DataHandlers/AircraftHandlers/JetHandler/DataStruct.hpp"


namespace aircraft::jet
{

struct IndexedId
{
    SimconnectIds id;
    const uint8_t engineIdx;
};

void JetHandler::processEngine(const unsigned long *raw,
                                const uint8_t engineIdx,
                                EngineStruct &previous,
                                QByteArray &dataToSend)
{
    EngineStruct newData(*reinterpret_cast<const EngineStruct *>(raw + (engineIdx - 1) * sizeof(EngineStruct)));
    IndexedId id{ SimconnectIds::ENGINE_N1, engineIdx };

    if (std::abs(previous.n1 - newData.n1) >= d_n1Eps)
    {
        previous.n1 = newData.n1;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.n1), sizeof(newData.n1));
    }

    if (std::abs(previous.n2 - newData.n2) >= d_n2Eps)
    {
        previous.n2 = newData.n2;
        id.id = SimconnectIds::ENGINE_N2;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.n2), sizeof(newData.n2));
    }

    if (std::abs(previous.itt - newData.itt) >= d_ittEps)
    {
        previous.itt = newData.itt;
        id.id = SimconnectIds::ENGINE_ITT;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.itt), sizeof(newData.itt));
    }

    base::AircraftHandler::processEngine(newData.common, engineIdx, previous.common, dataToSend);
}

}  // namespace aircraft::jet
