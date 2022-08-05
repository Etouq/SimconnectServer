#include "SimThreadManager.hpp"

namespace sim
{

void SimThreadManager::startConnectionAttempt()
{
    if (d_sim.isRunning())
        return;

    d_state = SimState::CONNECTING;
    emit stateChanged();

    d_sim.start();
}

}  // namespace sim