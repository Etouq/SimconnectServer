#include "../SimInterface.hpp"
#include "WindInfoHandler.hpp"

namespace windinfo
{

WindInfoHandler::WindInfoHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}

}  // namespace windinfo
