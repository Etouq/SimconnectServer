#include "../SimInterface.hpp"
#include "NavInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace navinfo
{

void NavInfoHandler::reset()
{
    d_previous = DataStruct();

    sendCurrentData();
}

}  // namespace navinfo
