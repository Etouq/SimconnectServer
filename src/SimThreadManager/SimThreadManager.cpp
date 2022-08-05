#include "SimThreadManager.hpp"
#include "common/definitions/AircraftConfig.hpp"
#include <QQmlEngine>

namespace sim
{

SimThreadManager::SimThreadManager(const AircraftConfig &initialConfig, QObject *parent)
  : QObject(parent),
    d_sim(d_sharedDataUpdated, d_sharedDataMutex, d_sharedData, initialConfig)
{
    // connect sim signals
    connect(&d_sim, &SimInterface::simConnectionFailed, this, &SimThreadManager::simStartupFailed);
    connect(&d_sim, &SimInterface::connected, this, &SimThreadManager::simConnected);
    connect(&d_sim, &SimInterface::simConnectQuit, this, &SimThreadManager::simClosed);
    connect(&d_sim, &QThread::finished, this, &SimThreadManager::threadFinished);

    // setup timer
    d_trySimStartTimer.setInterval(10000);
    d_trySimStartTimer.setSingleShot(true);
    connect(&d_trySimStartTimer, &QTimer::timeout, this, &SimThreadManager::startConnectionAttempt);

    // start trying to connect to the sim every 10 seconds until we succeed
    startConnectionAttempt();
}

SimThreadManager::~SimThreadManager()
{
    // kill the timer if it is running
    if (d_trySimStartTimer.isActive())
        d_trySimStartTimer.stop();

    // we want the thread to close, so make sure it is not restarted
    disconnect(&d_sim, &QThread::finished, this, &SimThreadManager::threadFinished);

    // tell the sim to close
    {
        std::unique_lock<std::shared_mutex> lock(d_sharedDataMutex);
        d_sharedData.quit = true;
    }
    d_sharedDataUpdated.store(true, std::memory_order_seq_cst);

    // wait for the sim to be closed
    if (!d_sim.wait(1000))
        d_sim.terminate();   // terminate if thread took too long
}

}  // namespace sim