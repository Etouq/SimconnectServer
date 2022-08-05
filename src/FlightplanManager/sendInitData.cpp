#include "FlightplanManager.hpp"
#include "common/dataIdentifiers.hpp"
#include "ConnectionHandler/FdcSocket/FdcSocket.hpp"

void FlightplanManager::sendInitData(FdcSocket *newSocket)
{
    if (d_wpModel.rowCount() == 0)
    {
        newSocket->writeToSocket(std::string({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                                               static_cast<char>(MfdIdentifier::CLEAR_FLIGHTPLAN),
                                               static_cast<char>(DataGroupIdentifier::MFD_DATA),
                                               static_cast<char>(MfdIdentifier::FLIGHTPLAN_LEG_IDX) })
                                   .append(reinterpret_cast<const char *>(&d_activeLegIdx), sizeof(d_activeLegIdx)));

        return;
    }

    const std::vector<FlightPlanWaypoint> waypoints = d_wpModel.data();

    const uint64_t listSize = waypoints.size();

    std::string planBinaryData(reinterpret_cast<const char *>(&listSize), sizeof(listSize));

    for (const FlightPlanWaypoint &waypoint : waypoints)
    {
        planBinaryData += waypoint.toBinary();
    }

    const uint64_t binarySize = planBinaryData.size();
    planBinaryData.insert(0, reinterpret_cast<const char *>(&binarySize), sizeof(binarySize));

    planBinaryData.insert(
      0,
      { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FLIGHTPLAN_LIST) });

    newSocket->writeToSocket(planBinaryData);
    newSocket->writeToSocket(std::string({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                                           static_cast<char>(MfdIdentifier::FLIGHTPLAN_LEG_IDX) })
                               .append(reinterpret_cast<const char *>(&d_activeLegIdx), sizeof(d_activeLegIdx)));
}