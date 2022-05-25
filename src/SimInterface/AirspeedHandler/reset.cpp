#include "../SimInterface.hpp"
#include "AirspeedHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace airspeed
{

void AirspeedHandler::reset()
{
    d_previous = DataStruct();

    sendCurrentData();
}

}  // namespace airspeed
