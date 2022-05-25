#include "../SimInterface.hpp"
#include "RadioHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace radio
{

void RadioHandler::reset()
{
    d_previous = DataStruct();

    sendCurrentData();
}

}  // namespace radio
