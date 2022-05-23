#include "AirspeedHandler.hpp"

#include "../SimInterface.hpp"

AirspeedHandler::AirspeedHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}
