#include "../SimInterface.hpp"
#include "AltitudeHandler.hpp"


namespace altitude
{

AltitudeHandler::AltitudeHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}

}  // namespace altitude