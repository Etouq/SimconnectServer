#include "../SimInterface.hpp"
#include "HsiHandler.hpp"

namespace hsi
{

HsiHandler::HsiHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}

}  // namespace hsi
