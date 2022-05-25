#include "../SimInterface.hpp"
#include "AltitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace altitude
{

void AltitudeHandler::reset()
{
    d_previous = DataStruct();

    d_lastVertMode = 0;
    d_deviation = 0.0;

    sendCurrentData();
}

}  // namespace altitude
