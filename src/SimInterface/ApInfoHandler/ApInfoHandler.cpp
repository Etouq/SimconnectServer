#include "../SimInterface.hpp"
#include "ApInfoHandler.hpp"

namespace apinfo
{

ApInfoHandler::ApInfoHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}

}  // namespace apinfo
