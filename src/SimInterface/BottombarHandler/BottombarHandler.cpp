#include "../SimInterface.hpp"
#include "BottombarHandler.hpp"

namespace bottombar
{

BottombarHandler::BottombarHandler(SimInterface *interface, QObject *parent)
  : d_parent(interface),
    QObject{ parent }
{}

}  // namespace bottombar
