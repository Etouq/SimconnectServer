#include "../SimInterface.hpp"
#include "AttitudeHandler.hpp"

namespace attitude
{

AttitudeHandler::AttitudeHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}

}  // namespace attitude
