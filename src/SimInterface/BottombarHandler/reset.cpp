#include "../SimInterface.hpp"
#include "BottombarHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace bottombar
{

void BottombarHandler::reset()
{
    d_previous = DataStruct();

    sendCurrentData();
}

}  // namespace bottombar
