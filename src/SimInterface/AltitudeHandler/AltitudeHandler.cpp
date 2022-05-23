#include "AltitudeHandler.hpp"

#include "../SimInterface.hpp"

AltitudeHandler::AltitudeHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}
