#ifndef __SIM_THREAD_MANAGER_HPP__
#define __SIM_THREAD_MANAGER_HPP__

#include "SimInterface/SharedThreadData.hpp"
#include "SimInterface/SimInterface.hpp"

#include <QObject>
#include <QDebug>
#include <QTimer>

#include <shared_mutex>
#include <unordered_map>

class FdcSocket;

namespace definitions
{
struct AircraftDefinition;
}

namespace sim
{


class SimThreadManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(sim::SimThreadManager::SimState state READ state NOTIFY stateChanged)

public:

    SimThreadManager(const AircraftConfig &initialConfig, QObject *parent = nullptr);

    ~SimThreadManager();

    void startSim()
    {
        if (!d_sim.isRunning())
            startConnectionAttempt();
    }

    enum SimState
    {
        CONNECTED,
        CONNECTING,
        WAITING_FOR_NEXT_ATTEMPT,
        WAITING_FOR_USER_RESTART,
        UNEXPECTED_DISCONNECT
    };
    Q_ENUM(SimState)

    SimState state() const
    {
        return d_state;
    }

    const SimInterface &sim() const
    {
        return d_sim;
    }

    std::atomic_bool &sharedDataUpdated()
    {
        return d_sharedDataUpdated;
    }

    std::shared_mutex &sharedDataMutex()
    {
        return d_sharedDataMutex;
    }

    SharedThreadData &sharedData()
    {
        return d_sharedData;
    }

    Q_INVOKABLE void userRestart()
    {
        startConnectionAttempt();
    }

signals:

    void stateChanged();
    void qmlSimStartupFailed(); // used to indicate failure to qml

public slots:

    void initSocket(FdcSocket *newSocket) const;

    void updateConfig(const definitions::AircraftDefinition &definition);

    void setAircraftLoaded()
    {
        {
            std::unique_lock<std::shared_mutex> lock(d_sharedDataMutex);
            d_sharedData.aircraftLoaded = true;
        }

        d_sharedDataUpdated.store(true, std::memory_order_seq_cst);
    }

    void setCommandString(const QByteArray &commandString)
    {
        {
            std::unique_lock<std::shared_mutex> lock(d_sharedDataMutex);
            d_sharedData.commandString += commandString;
        }

        d_sharedDataUpdated.store(true, std::memory_order_seq_cst);
    }

private slots:

    void simStartupFailed();

    void simConnected()
    {
        d_state = SimState::CONNECTED;
        emit stateChanged();
    }

    void simClosed()
    {
        // sim closed so wait for user to restart connection attempts
        d_state = SimState::WAITING_FOR_USER_RESTART;
        emit stateChanged();
    }

    void threadFinished()
    {
        if (d_state != SimState::WAITING_FOR_USER_RESTART && d_state != SimState::WAITING_FOR_NEXT_ATTEMPT)
        {
            qDebug() << "state was:" << d_state;
            d_state = SimState::UNEXPECTED_DISCONNECT;
            emit stateChanged();

            // thread closed unexpectedly, so restart connection timer
            d_trySimStartTimer.start();
        }
    }

    void startConnectionAttempt();


private:

    SimInterface d_sim;
    SimState d_state = SimState::CONNECTING;

    QTimer d_trySimStartTimer;

    // communication data (since simthread does not run an event loop)
    std::atomic_bool d_sharedDataUpdated;
    std::shared_mutex d_sharedDataMutex;
    SharedThreadData d_sharedData;
};

}  // namespace sim

#endif  // __SIM_THREAD_MANAGER_HPP__