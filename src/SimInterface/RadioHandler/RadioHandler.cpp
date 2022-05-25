#include "../SimInterface.hpp"
#include "RadioHandler.hpp"

namespace radio
{

RadioHandler::RadioHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}

}  // namespace radio
