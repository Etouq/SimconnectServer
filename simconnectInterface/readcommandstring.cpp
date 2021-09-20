#include "simconnectthread.ih"

#include <QBuffer>

enum class CommandIds : uint8_t
{
    SET_COM1_FREQ,
    SET_COM2_FREQ,
    SET_NAV1_FREQ,
    SET_NAV2_FREQ,
    SWAP_COM1,
    SWAP_COM2,
    SWAP_NAV1,
    SWAP_NAV2,
    SET_XPDR_CODE,
    SET_XPDR_STATE
};

void SimconnectThread::readCommandString(const QByteArray &data)
{
    QBuffer buffer;
    buffer.buffer() = data;
    buffer.open(QBuffer::ReadOnly);
    CommandIds commandId = CommandIds::SET_COM1_FREQ;
    //emit receivedError("Command string is: " + data.toHex());

    while (buffer.bytesAvailable() > 0)
    {
        buffer.read(reinterpret_cast<char *>(&commandId), sizeof(commandId));
        //emit receivedError("Received command: " + QString::number(static_cast<int>(commandId)));

        switch (commandId)
        {
            case CommandIds::SET_COM1_FREQ:
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
            case CommandIds::SWAP_COM1:
                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SWAP_COM1,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                break;
            case CommandIds::SET_COM2_FREQ:
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
            case CommandIds::SWAP_COM2:
                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SWAP_COM2,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                break;
            case CommandIds::SET_NAV1_FREQ:
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
            case CommandIds::SWAP_NAV1:
                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SWAP_NAV1,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                break;
            case CommandIds::SET_NAV2_FREQ:
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
            case CommandIds::SWAP_NAV2:
                SimConnect_TransmitClientEvent(d_simConnectHandle,
                                               SIMCONNECT_OBJECT_ID_USER,
                                               SIM_COMMAND_IDS::SWAP_NAV2,
                                               1,
                                               SIMCONNECT_GROUP_PRIORITY_HIGHEST,
                                               SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
                break;
            case CommandIds::SET_XPDR_CODE:
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
            case CommandIds::SET_XPDR_STATE:
            {
                SetXpndrStateStruct newState;
                buffer.read(reinterpret_cast<char *>(&newState.state), sizeof(newState.state));


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
        }
    }
}
