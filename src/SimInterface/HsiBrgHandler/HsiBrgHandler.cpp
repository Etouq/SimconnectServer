#include "../SimInterface.hpp"
#include "HsiBrgHandler.hpp"

namespace hsibrg
{

HsiBrgHandler::HsiBrgHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}

}  // namespace hsibrg
