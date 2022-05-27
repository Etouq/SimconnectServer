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

void AircraftHandler::sendCurrentEngineData(const EngineCommon &data, QByteArray &dataToSend, const uint8_t engineIdx)
{
    IndexedId id{ SimconnectIds::ENGINE_FUEL_FLOW, engineIdx };
    double transformedValue = data.fuelFlow * (d_fuelFlowByWeight ? 3600 : 3.785411784);
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&transformedValue), sizeof(transformedValue));

    id.id = SimconnectIds::ENGINE_EGT;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&data.egt), sizeof(data.egt));

    id.id = SimconnectIds::ENGINE_OIL_TEMP;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&data.oilTemp), sizeof(data.oilTemp));

    id.id = SimconnectIds::ENGINE_OIL_PRESS;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&data.oilPress), sizeof(data.oilPress));
}

}  // namespace aircraft::base
