#include "main.hpp"

void connectSignals(const AircraftManager *aircraftManager,
                    const ConnectionHandler *connectionHandler,
                    const FlightplanManager *flightplanManager,
                    const sim::SimThreadManager *simManager)
{
    // connect aircraftManager's signals
    QObject::connect(aircraftManager,
                     &AircraftManager::aircraftSelected,
                     connectionHandler,
                     &ConnectionHandler::aircraftSelected);
    QObject::connect(aircraftManager,
                     &AircraftManager::aircraftSelected,
                     simManager,
                     &sim::SimThreadManager::updateConfig);

    // connect flightplanManager's signals
    QObject::connect(flightplanManager,
                     &FlightplanManager::flightplanChanged,
                     connectionHandler,
                     &ConnectionHandler::flightplanChanged);

    QObject::connect(flightplanManager,
                     &FlightplanManager::activeLegIdxChanged,
                     connectionHandler,
                     &ConnectionHandler::updateActiveLegIdx);

    // connect connectionhandler's signals
    QObject::connect(connectionHandler,
                     &ConnectionHandler::initSocket,
                     aircraftManager,
                     &AircraftManager::initSocket);

    QObject::connect(connectionHandler,
                     &ConnectionHandler::initSocket,
                     flightplanManager,
                     &FlightplanManager::sendInitData);

    QObject::connect(connectionHandler,
                     &ConnectionHandler::initSocket,
                     simManager,
                     &sim::SimThreadManager::initSocket);

    // connect sim's signals
    QObject::connect(&simManager->sim(),
                     &SimInterface::updatePosition,
                     flightplanManager,
                     &FlightplanManager::updateActiveLeg);
}