#include "SimThreadManager.hpp"
#include "common/definitions/AircraftConfig.hpp"
#include "common/definitions/AircraftDefinition/AircraftDefinition.hpp"

namespace sim
{

void SimThreadManager::updateConfig(const definitions::AircraftDefinition &definition)
{

    {
        std::unique_lock<std::shared_mutex> lock(d_sharedDataMutex);
        d_sharedData.aircraftConfig = definition.toConfig();
    }

    d_sharedDataUpdated.store(true, std::memory_order_seq_cst);
}

}  // namespace sim