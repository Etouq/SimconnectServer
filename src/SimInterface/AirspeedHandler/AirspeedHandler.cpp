#include "../SimInterface.hpp"
#include "AirspeedHandler.hpp"


namespace airspeed
{

AirspeedHandler::AirspeedHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}

}  // namespace airspeed
