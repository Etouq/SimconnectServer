#include "../SimInterface.hpp"
#include "NavInfoHandler.hpp"

namespace navinfo
{

NavInfoHandler::NavInfoHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}

}  // namespace navinfo
