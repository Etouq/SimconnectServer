#include "AircraftManager.hpp"
#include "common/dataIdentifiers.hpp"
#include "ConnectionHandler/FdcSocket/FdcSocket.hpp"

void AircraftManager::initSocket(FdcSocket *newSocket)
{
    connect(newSocket, &FdcSocket::updateDefaultSpeedBugs, this, &AircraftManager::updateDefaultSpeedBugs);

    QByteArray definitionBinary = d_definitions.at(d_currentDefinitionKey).toBinary();
    uint64_t binarySize = definitionBinary.size();

    newSocket->writeToSocket(QByteArray::fromStdString({ static_cast<char>(DataGroupIdentifier::SERVER_DATA),
                                                         static_cast<char>(ServerMessageIdentifier::LOAD_AIRCRAFT) })
                               .append(reinterpret_cast<const char *>(&binarySize), sizeof(binarySize))
                               .append(definitionBinary));
}