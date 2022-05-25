#include "../SimInterface.hpp"
#include "HsiBrgHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace hsibrg
{

void HsiBrgHandler::reset()
{
    d_previous = DataStruct();

    sendCurrentData();
}

}  // namespace hsibrg
