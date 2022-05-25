#include "../SimInterface.hpp"
#include "ApInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace apinfo
{

void ApInfoHandler::reset()
{
    d_apMaster = false;
    d_yawDamper = false;

    d_verticalActive = "";
    d_modeReference = "";
    d_armed = "";
    d_armedReference = "";
    d_lateralActive = "";
    d_lateralArmed = "";

    sendCurrentData();
}

}  // namespace apinfo
