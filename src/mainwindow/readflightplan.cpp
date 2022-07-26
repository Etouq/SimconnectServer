#include "mainwindow.hpp"
// #include "FlightplanReader/flightplanreader.hpp"
#include "common/dataIdentifiers.hpp"

#include <QFile>

void MainWindow::readFlightplan(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        //d_flightplanManager.readFromFile(file);
        file.close();
        // QList<FlightPlanWaypoint> waypoints = d_flightplanManager.getFlightplan();
        // // QList<FlightPlanWaypoint> waypoints = FlightplanReader::readFile(file);
        // // file.close();
        // std::string flightplanBytes(static_cast<uint16_t>(waypoints.size()), sizeof(uint16_t));

        // for (const FlightPlanWaypoint &waypoint : waypoints)
        // {
        //     double coordPart = waypoint.position.latitude();
        //     flightplanBytes.append(reinterpret_cast<const char *>(&coordPart), sizeof(coordPart));
        //     coordPart = waypoint.position.longitude();
        //     flightplanBytes.append(reinterpret_cast<const char *>(&coordPart), sizeof(coordPart));

        //     flightplanBytes.append(reinterpret_cast<const char *>(&waypoint.alt1), sizeof(waypoint.alt1));
        //     flightplanBytes.append(reinterpret_cast<const char *>(&waypoint.alt2), sizeof(waypoint.alt2));

        //     flightplanBytes.append({ static_cast<char>(static_cast<uint8_t>(waypoint.ident.size())) });
        //     flightplanBytes += waypoint.ident.toStdString();

        //     flightplanBytes.append({ static_cast<char>(waypoint.wpType), static_cast<char>(waypoint.altType) });
        // }

        // uint64_t byteSize = flightplanBytes.size();
        // flightplanBytes.insert(0, reinterpret_cast<const char *>(&byteSize), sizeof(byteSize));

        // flightplanBytes.insert(flightplanBytes.begin(), { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FLIGHTPLAN_LIST) });

        // d_connectionHandler.sendDataToClients(QByteArray::fromStdString(flightplanBytes));
    }
}
