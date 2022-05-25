#include "../SimInterface.hpp"
#include "HsiHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace hsi
{

void HsiHandler::reset()
{
    d_previous = DataStruct();

    d_displayDeviation = false;
    d_navSource = HsiNavSource::NONE;
    d_course = -5000.0;
    d_courseDeviation = -5000.0;
    d_nextGpsWpIdValid = false;

    sendCurrentData();
}

}  // namespace hsi
