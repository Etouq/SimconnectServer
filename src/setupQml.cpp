#include "main.hpp"
#include "common/QmlEnums.hpp"

#include <QQmlEngine>

void setupQml(AircraftManager *aircraftManager,
              ConnectionHandler *connectionHandler,
              FlightplanManager *flightplanManager,
              sim::SimThreadManager *simManager)
{

    qRegisterMetaType<QmlWaypoint *>("QmlWaypoint*");
    qmlRegisterUncreatableType<QmlWaypoint>("Flightplan", 1, 0, "Waypoint", "Bad Boy");

    qRegisterMetaType<QmlWaypointType>("QmlWaypointType");
    qmlRegisterUncreatableType<QmlWaypointTypeClass>("TypeEnums",
                                                     1,
                                                     0,
                                                     "WaypointType",
                                                     "Not creatable as it is an enum type");

    qRegisterMetaType<QmlWpAltitudeType>("QmlWpAltitudeType");
    qmlRegisterUncreatableType<QmlWpAltitudeTypeClass>("TypeEnums",
                                                       1,
                                                       0,
                                                       "WpAltitudeType",
                                                       "Not creatable as it is an enum type");

    // qRegisterMetaType<sim::SimThreadManager::SimState>("SimState");
    qmlRegisterUncreatableType<sim::SimThreadManager>("TypeEnums",
                                                                1,
                                                                0,
                                                                "SimState",
                                                                "Not creatable as it is an enum type");

    qmlRegisterSingletonInstance("SimconnectServer", 1, 0, "AircraftManager", aircraftManager);
    qmlRegisterSingletonInstance("SimconnectServer", 1, 0, "ConnectionHandler", connectionHandler);

    qmlRegisterSingletonInstance("Flightplan", 1, 0, "FlightplanManager", flightplanManager);
    qmlRegisterSingletonInstance("Flightplan", 1, 0, "WaypointModel", flightplanManager->getModel());

    qmlRegisterSingletonInstance("SimconnectServer", 1, 0, "SimManager", simManager);
}