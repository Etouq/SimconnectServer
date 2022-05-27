#include "PropHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>
#include <stdint.h>

#include "SimInterface/DataHandlers/AircraftHandlers/PropHandler/DataStruct.hpp"


namespace aircraft::prop
{

struct IndexedId
{
    SimconnectIds id;
    const uint8_t engineIdx;
};

void PropHandler::processEngine(const unsigned long *raw,
                                const uint8_t engineIdx,
                                EngineStruct &previous,
                                QByteArray &dataToSend)
{
    EngineStruct newData(*reinterpret_cast<const EngineStruct *>(raw + (engineIdx - 1) * sizeof(EngineStruct)));
    IndexedId id{ SimconnectIds::ENGINE_RPM, engineIdx };

    if (d_checkRpm && std::abs(previous.rpm - newData.rpm) >= d_rpmEps) [[likely]]
    {
        previous.rpm = newData.rpm;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.rpm), sizeof(newData.rpm));
    }

    if (d_checkPower && std::abs(previous.power - newData.power) >= d_powerEps)
    {
        previous.power = newData.power;

        if (d_powerAsPct) [[likely]]
            newData.power /= d_maxPower;

        id.id = SimconnectIds::ENGINE_POWER;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.power), sizeof(newData.power));
    }

    if (d_checkManPress && std::abs(previous.manPress - newData.manPress) >= d_manPressEps)
    {
        previous.manPress = newData.manPress;
        id.id = SimconnectIds::ENGINE_MANIFOLD_PRESSURE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.manPress), sizeof(newData.manPress));
    }

    if (d_checkCht && std::abs(previous.cht - newData.cht) >= d_chtEps) [[unlikely]]
    {
        previous.cht = newData.cht;
        id.id = SimconnectIds::ENGINE_CHT;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.cht), sizeof(newData.cht));
    }

    base::AircraftHandler::processEngine(newData.common, engineIdx, previous.common, dataToSend);

}

}  // namespace aircraft::prop
