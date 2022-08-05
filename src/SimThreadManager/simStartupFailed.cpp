#include "SimThreadManager.hpp"

namespace sim
{

void SimThreadManager::simStartupFailed()
{
    d_state = SimState::WAITING_FOR_NEXT_ATTEMPT;
    emit stateChanged();

    // try again in 10 seconds
    d_trySimStartTimer.start();

    emit qmlSimStartupFailed();
}

}  // namespace sim