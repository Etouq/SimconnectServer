#include "../SimInterface.hpp"
#include "AttitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace attitude
{

void AttitudeHandler::reset()
{
    d_previous = DataStruct();

    sendCurrentData();
}

}  // namespace attitude
