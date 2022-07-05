#include "enums.hpp"
#include "SimInterface.hpp"
#include "common/dataIdentifiers.hpp"

#include <QBuffer>
#include <stdint.h>


void SimInterface::parseCommandString(const QByteArray &data)
{
    QBuffer buffer;
    buffer.buffer() = data;
    buffer.open(QBuffer::ReadOnly);
    SimCommandId commandId = SimCommandId::SET_COM1_FREQ;
    // emit receivedError("Command string is: " + data.toHex());

    while (buffer.bytesAvailable() > 0)
    {
        buffer.read(reinterpret_cast<char *>(&commandId), sizeof(commandId));
        // emit receivedError("Received command: " + QString::number(static_cast<int>(commandId)));

        switch (commandId)
        {
            case SimCommandId::SET_COM1_FREQ:
            {
                uint32_t newFreq = 0;
                bool swap = false;
                buffer.read(reinterpret_cast<char *>(&newFreq), sizeof(newFreq));
                buffer.read(reinterpret_cast<char *>(&swap), sizeof(swap));

                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SET_COM1_STBY,
                                               newFreq,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);

                if (!swap)
                    break;
            }
            case SimCommandId::SWAP_COM1:
                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SWAP_COM1,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                break;
            case SimCommandId::SET_COM2_FREQ:
            {
                uint32_t newFreq = 0;
                bool swap = false;
                buffer.read(reinterpret_cast<char *>(&newFreq), sizeof(newFreq));
                buffer.read(reinterpret_cast<char *>(&swap), sizeof(swap));

                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SET_COM2_STBY,
                                               newFreq,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);

                if (!swap)
                    break;
            }
            case SimCommandId::SWAP_COM2:
                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SWAP_COM2,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                break;
            case SimCommandId::SET_COM3_FREQ:
            {
                uint32_t newFreq = 0;
                bool swap = false;
                buffer.read(reinterpret_cast<char *>(&newFreq), sizeof(newFreq));
                buffer.read(reinterpret_cast<char *>(&swap), sizeof(swap));

                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SET_COM3_STBY,
                                               newFreq,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);

                if (!swap)
                    break;
            }
            case SimCommandId::SWAP_COM3:
                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SWAP_COM3,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                break;
            case SimCommandId::SET_NAV1_FREQ:
            {
                uint32_t newFreq = 0;
                bool swap = false;
                buffer.read(reinterpret_cast<char *>(&newFreq), sizeof(newFreq));
                buffer.read(reinterpret_cast<char *>(&swap), sizeof(swap));

                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SET_NAV1_STBY,
                                               newFreq,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);

                if (!swap)
                    break;
            }
            case SimCommandId::SWAP_NAV1:
                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SWAP_NAV1,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                break;
            case SimCommandId::SET_NAV2_FREQ:
            {
                uint32_t newFreq = 0;
                bool swap = false;
                buffer.read(reinterpret_cast<char *>(&newFreq), sizeof(newFreq));
                buffer.read(reinterpret_cast<char *>(&swap), sizeof(swap));

                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SET_NAV2_STBY,
                                               newFreq,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);

                if (!swap)
                    break;
            }
            case SimCommandId::SWAP_NAV2:
                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SWAP_NAV2,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                break;
            case SimCommandId::SET_XPDR_CODE:
            {
                uint32_t newCode = 0;
                buffer.read(reinterpret_cast<char *>(&newCode), sizeof(newCode));

                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SET_XPNDR_CODE,
                                               newCode,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                break;
            }
            case SimCommandId::SET_XPDR_STATE:
            {
                uint32_t newState = 0;
                buffer.read(reinterpret_cast<char *>(&newState), sizeof(newState));


                // set data
                SimConnect_SetDataOnSimObject(d_simConnectHandle,
                                              SET_XPNDR_STATE_DEF,
                                              SIMCONNECT_OBJECT_ID_USER,
                                              0,
                                              0,
                                              sizeof(newState),
                                              &newState);

                break;
            }
            case SimCommandId::NEXT_CDI_MODE:
            {
                if (d_hsiHandler.gpsDrivesNav1())
                {
                    // gps goes to nav 1
                    SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::TOGGLE_GPS_DRIVES_NAV1,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                    SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SET_AP_NAV_SELECTED,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                }
                else if (d_hsiHandler.autopilotNavSelected() == 1)
                {
                    // nav 1 goes to nav 2
                    SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SET_AP_NAV_SELECTED,
                                               2,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                }
                else
                {
                    // nav 2 goes to gps
                    SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::TOGGLE_GPS_DRIVES_NAV1,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                }
            }
        }
    }
}