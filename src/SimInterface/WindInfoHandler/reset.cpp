#include "../SimInterface.hpp"
#include "WindInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace windinfo
{

void WindInfoHandler::reset()
{
    d_previous = DataStruct();

    sendCurrentData();
}

}  // namespace windinfo
