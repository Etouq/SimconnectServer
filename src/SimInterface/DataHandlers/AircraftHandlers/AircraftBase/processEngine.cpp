#include "AircraftHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>
#include <stdint.h>



namespace aircraft::base
{

struct IndexedId
{
    SimconnectIds id;
    const uint8_t engineIdx;
};

void AircraftHandler::processEngine(EngineCommon &newData,
                                const uint8_t engineIdx,
                                EngineCommon &previous,
                                QByteArray &dataToSend)
{
    IndexedId id{ SimconnectIds::ENGINE_FUEL_FLOW, engineIdx };


    if (std::abs(previous.fuelFlow - newData.fuelFlow) >= d_fuelFlowEps)
    {
        previous.fuelFlow = newData.fuelFlow;
        newData.fuelFlow *= d_fuelFlowByWeight ? 3600 : 3.785411784;
        id.id = SimconnectIds::ENGINE_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.fuelFlow), sizeof(newData.fuelFlow));
    }

    if (d_checkEgt && std::abs(previous.egt - newData.egt) >= d_egtEps)
    {
        previous.egt = newData.egt;
        id.id = SimconnectIds::ENGINE_EGT;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.egt), sizeof(newData.egt));
    }

    if (std::abs(previous.oilTemp - newData.oilTemp) >= d_oilTempEps) [[unlikely]]
    {
        previous.oilTemp = newData.oilTemp;
        id.id = SimconnectIds::ENGINE_OIL_TEMP;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.oilTemp), sizeof(newData.oilTemp));
    }

    if (std::abs(previous.oilPress - newData.oilPress) >= d_oilPressEps) [[unlikely]]
    {
        previous.oilPress = newData.oilPress;
        id.id = SimconnectIds::ENGINE_OIL_PRESS;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.oilPress), sizeof(newData.oilPress));
    }
}

}  // namespace aircraft::base
