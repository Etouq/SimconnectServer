#include "TurbopropHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>


namespace aircraft::turboprop
{

struct IndexedId
{
    SimconnectIds id;
    const uint8_t engineIdx;
};

void TurbopropHandler::processEngine(const unsigned long *raw,
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

    if (std::abs(previous.trq - newData.trq) >= d_trqEps)
    {
        previous.trq = newData.trq;
        id.id = SimconnectIds::ENGINE_TRQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.trq), sizeof(newData.trq));
    }

    if (std::abs(previous.itt - newData.itt) >= d_ittEps)
    {
        previous.itt = newData.itt;
        id.id = SimconnectIds::ENGINE_ITT;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.itt), sizeof(newData.itt));
    }

    if (std::abs(previous.rpm - newData.rpm) >= d_rpmEps)
    {
        previous.rpm = newData.rpm;
        id.id = SimconnectIds::ENGINE_RPM;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.rpm), sizeof(newData.rpm));
    }

    base::AircraftHandler::processEngine(newData.common, engineIdx, previous.common, dataToSend);
}

}  // namespace aircraft::turboprop
