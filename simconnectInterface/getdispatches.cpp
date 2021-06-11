#include "simconnectthread.ih"
#include <QDebug>

void SimconnectThread::getDispatches()
{
    SIMCONNECT_RECV* pData;
    DWORD cbData;
    int dataIdx = 0;

    while (SUCCEEDED(SimConnect_GetNextDispatch(d_simConnectHandle, &pData, &cbData)) && !quit)
    {
        //qDebug() << "got data" << pData->dwID;
        dataIdx++;
        switch(pData->dwID)
        {
            case SIMCONNECT_RECV_ID_OPEN:
            {
                break;
            }
            case SIMCONNECT_RECV_ID_EVENT:
            {
                SIMCONNECT_RECV_EVENT *evt = static_cast<SIMCONNECT_RECV_EVENT *>(pData);

                //qDebug() << "received notification:" << evt->uEventID;

                if (evt->uEventID == EVENT_6HZ_ID)
                {
                    if (updateAircraft)
                    {
                        d_lastPfdData = PfdCleanDataStruct();
                        d_lastSlowData = SlowDatadefStruct();
                        d_lastStringsData = StringsDataStruct();
                        d_lastJetData = JetData();
                        d_lastPropData = PropData();
                        d_lastTurbopropData = TurbopropData();
                        sendBlankPfdData();
                        sendBlankEngineData();
                        sendBlankSlowData();
                        sendBlankStringsData();
                        SimConnect_ClearDataDefinition(d_simConnectHandle, ENGINE_DATA_DEFINITION_ID);
                        setupAircraftData();
                        updateAircraft = false;
                        SimConnect_RequestDataOnSimObject(d_simConnectHandle, ENGINE_DATA_REQUEST_ID, ENGINE_DATA_DEFINITION_ID, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
                    }

                    //qDebug() << "received notification 6hz:" << dataIdx;

                    if (sharedDataUpdated->load(std::memory_order_seq_cst))
                    {//emit receivedError("received data update");
                        sharedDataUpdated->store(false, std::memory_order_seq_cst);
                        readSharedData();

                        //emit receivedError(quit ? "have to quit" : "no quit");

                        if (quit)
                            break;
                    }

                }
                else if (evt->uEventID == SIM_START_EVENT_ID)
                {
                    DataIdentifiers id = DataIdentifiers::SIM_START_EVENT;
                    emit sendData(QByteArray(reinterpret_cast<char *>(&id), sizeof(id)));
                }
                else if (evt->uEventID == SIM_STOP_EVENT_ID)
                {
                    DataIdentifiers id = DataIdentifiers::SIM_STOP_EVENT;
                    emit sendData(QByteArray(reinterpret_cast<char *>(&id), sizeof(id)));
                }
                else
                {
                    emit receivedError(QString("unknown event id received: %1").arg(evt->uEventID));
                }

                break;
            }
            case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
            {
                SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData = static_cast<SIMCONNECT_RECV_SIMOBJECT_DATA *>(pData);

                switch(pObjData->dwRequestID)
                {
                    case PFD_DATA_REQUEST_ID:
                    {
                        handlePfdData(pObjData);
                        break;
                    }
                    case ENGINE_DATA_REQUEST_ID:
                    {
                        (this->*d_aircraftHandler)(pObjData);
                        break;
                    }
                    case SLOW_DATA_REQUEST_ID:
                    {
                        handleSlowData(pObjData);
                        break;
                    }
                    case STRINGS_DATA_REQUEST_ID:
                    {
                        handleStringsData(pObjData);
                        break;
                    }
                    default:
                    {
                        emit receivedError(QString("unknown simobject data request id received: %1").arg(pObjData->dwRequestID));
                        break;
                    }
                }
                break;
            }
            case SIMCONNECT_RECV_ID_EXCEPTION:
            {
                SIMCONNECT_RECV_EXCEPTION *pObjData = static_cast<SIMCONNECT_RECV_EXCEPTION *>(pData);
                switch (pObjData->dwException)
                {
                    case SIMCONNECT_EXCEPTION_NONE:
                        break;
                    case SIMCONNECT_EXCEPTION_ERROR:
                        emit receivedError("An unspecific error has occurred. This can be from incorrect flag settings, null or incorrect parameters, the need to have at least one up or down event with an input event, failed calls from the SimConnect server to the operating system, among other reasons.");
                        break;
                    case SIMCONNECT_EXCEPTION_SIZE_MISMATCH:
                        emit receivedError("Specifies the size of the data provided does not match the size required. This typically occurs when the wrong string length, fixed or variable, is involved.");
                        break;
                    case SIMCONNECT_EXCEPTION_UNRECOGNIZED_ID:
                        emit receivedError("Specifies that the client event, request ID, data definition ID, or object ID was not recognized.");
                        break;
                    case SIMCONNECT_EXCEPTION_UNOPENED:
                        emit receivedError("Specifies that communication with the SimConnect server has not been opened. This error is not currently used.");
                        break;
                    case SIMCONNECT_EXCEPTION_VERSION_MISMATCH:
                        emit receivedError("Specifies a versioning error has occurred. Typically this will occur when a client built on a newer version of the SimConnect client dll attempts to work with an older version of the SimConnect server.");
                        break;
                    case SIMCONNECT_EXCEPTION_TOO_MANY_GROUPS:
                        emit receivedError("Specifies that the maximum number of groups allowed has been reached. The maximum is 20.");
                        break;
                    case SIMCONNECT_EXCEPTION_NAME_UNRECOGNIZED:
                        emit receivedError("Specifies that the simulation event name (such as \"brakes\") is not recognized.");
                        break;
                    case SIMCONNECT_EXCEPTION_TOO_MANY_EVENT_NAMES:
                        emit receivedError("Specifies that the maximum number of event names allowed has been reached. The maximum is 1000.");
                        break;
                    case SIMCONNECT_EXCEPTION_EVENT_ID_DUPLICATE:
                        emit receivedError("Specifies that the event ID has been used already. This can occur with calls to SimConnect_MapClientEventToSimEvent, or SimConnect_SubscribeToSystemEvent.");
                        break;
                    case SIMCONNECT_EXCEPTION_TOO_MANY_MAPS:
                        emit receivedError("Specifies that the maximum number of mappings allowed has been reached. The maximum is 20.");
                        break;
                    case SIMCONNECT_EXCEPTION_TOO_MANY_OBJECTS:
                        emit receivedError("Specifies that the maximum number of objects allowed has been reached. The maximum is 1000.");
                        break;
                    case SIMCONNECT_EXCEPTION_TOO_MANY_REQUESTS:
                        emit receivedError("Specifies that the maximum number of requests allowed has been reached. The maximum is 1000.");
                        break;
                    case SIMCONNECT_EXCEPTION_INVALID_DATA_TYPE:
                        emit receivedError("Specifies that the data type requested does not apply to the type of data requested. Typically this occurs with a fixed length string of the wrong length.");
                        break;
                    case SIMCONNECT_EXCEPTION_INVALID_DATA_SIZE:
                        emit receivedError("Specifies that the size of the data provided is not what is expected. This can occur when the size of a structure provided does not match the size given, or a null string entry is made for a menu or sub-menu entry text, or data with a size of zero is added to a data definition. It can also occur with an invalid request to SimConnect_CreateClientData.");
                        break;
                    case SIMCONNECT_EXCEPTION_DATA_ERROR:
                        emit receivedError("Specifies a generic data error. This error is used by the SimConnect_WeatherCreateThermal function to report incorrect parameters, such as negative radii or values greater than the maximum allowed. It is also used by the SimConnect_FlightSave and SimConnect_FlightLoad functions to report incorrect file types. It is also used by other functions to report that flags or reserved parameters have not been set to zero.");
                        break;
                    case SIMCONNECT_EXCEPTION_INVALID_ARRAY:
                        emit receivedError("Specifies an invalid array has been sent to the SimConnect_SetDataOnSimObject function.");
                        break;
                    case SIMCONNECT_EXCEPTION_CREATE_OBJECT_FAILED:
                        emit receivedError("Specifies that the attempt to create an AI object failed.");
                        break;
                    case SIMCONNECT_EXCEPTION_LOAD_FLIGHTPLAN_FAILED:
                        emit receivedError("Specifies that the specified flight plan could not be found, or did not load correctly.");
                        break;
                    case SIMCONNECT_EXCEPTION_OPERATION_INVALID_FOR_OBJECT_TYPE:
                        emit receivedError("Specifies that the operation requested does not apply to the object type, for example trying to set a flight plan on an object that is not an aircraft will result in this error.");
                        break;
                    case SIMCONNECT_EXCEPTION_ILLEGAL_OPERATION:
                        emit receivedError("Specifies that the AI operation requested cannot be completed, such as requesting that an object be removed when the client did not create that object. This error also applies to the Weather system.");
                        break;
                    case SIMCONNECT_EXCEPTION_ALREADY_SUBSCRIBED:
                        emit receivedError("Specifies that the client has already subscribed to that event.");
                        break;
                    case SIMCONNECT_EXCEPTION_INVALID_ENUM:
                        emit receivedError("Specifies that the member of the enumeration provided was not valid. Currently this is only used if an unknown type is provided to SimConnect_RequestDataOnSimObjectType.");
                        break;
                }
            }
            case SIMCONNECT_RECV_ID_QUIT:
            {
                quit = true;
                emit simConnectQuit();
                break;
            }

            default:
            {
                emit receivedError(QString("unknown id received: %1").arg(pData->dwID));
                break;
            }
        }
    }
}

