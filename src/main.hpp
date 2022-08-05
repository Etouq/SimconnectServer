#ifndef __MAIN_HPP__
#define __MAIN_HPP__

#include "AircraftManager/AircraftManager.hpp"
#include "ConnectionHandler/ConnectionHandler.hpp"
#include "FlightplanManager/FlightplanManager.hpp"
#include "SimThreadManager/SimThreadManager.hpp"

void setupQml(AircraftManager *aircraftManager,
              ConnectionHandler *connectionHandler,
              FlightplanManager *flightplanManager,
              sim::SimThreadManager *simManager);

void connectSignals(const AircraftManager *aircraftManager,
                    const ConnectionHandler *connectionHandler,
                    const FlightplanManager *flightplanManager,
                    const sim::SimThreadManager *simManager);

#endif  // __MAIN_HPP__