#include "enums.hpp"
#include "SimInterface.hpp"
#include "common/dataIdentifiers.hpp"

void SimInterface::processDispatches()
{
    SIMCONNECT_RECV *pData;
    DWORD cbData;
    int dataIdx = 0;

    while (SUCCEEDED(SimConnect_GetNextDispatch(d_simConnectHandle, &pData, &cbData)) && !quit)
    {
        dataIdx++;
        switch (pData->dwID)
        {
            case SIMCONNECT_RECV_ID_OPEN:
            {
                break;
            }
            case SIMCONNECT_RECV_ID_EVENT:
            {
                SIMCONNECT_RECV_EVENT *evt = static_cast<SIMCONNECT_RECV_EVENT *>(pData);

                if (evt->uEventID == EVENT_6HZ_ID)
                {
                    if (updateAircraft)
                    {
                        QByteArray dataToSend = d_engine1Handler.reset();
                        dataToSend += d_engine2Handler.reset();
                        dataToSend += d_engine3Handler.reset();
                        dataToSend += d_engine4Handler.reset();
                        dataToSend += d_aircraftHandler.reset();
                        emit sendData(dataToSend);

                        SimConnect_ClearDataDefinition(d_simConnectHandle, ENGINE1_DEFINITION);
                        SimConnect_ClearDataDefinition(d_simConnectHandle, ENGINE2_DEFINITION);
                        SimConnect_ClearDataDefinition(d_simConnectHandle, ENGINE3_DEFINITION);
                        SimConnect_ClearDataDefinition(d_simConnectHandle, ENGINE4_DEFINITION);
                        SimConnect_ClearDataDefinition(d_simConnectHandle, AIRCRAFT_GENERAL_DEFINITION);

                        d_aircraftHandler.setupData(d_simConnectHandle, d_aircraftConfig);

                        updateAircraft = false;

                        switch (d_aircraftConfig.numEngines)
                        {
                            case 4:
                                SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                                                  ENGINE4_REQUEST,
                                                                  ENGINE4_DEFINITION,
                                                                  SIMCONNECT_OBJECT_ID_USER,
                                                                  SIMCONNECT_PERIOD_SIM_FRAME,
                                                                  SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
                                SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                                                  ENGINE3_REQUEST,
                                                                  ENGINE3_DEFINITION,
                                                                  SIMCONNECT_OBJECT_ID_USER,
                                                                  SIMCONNECT_PERIOD_SIM_FRAME,
                                                                  SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
                            case 2:
                                SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                                                  ENGINE2_REQUEST,
                                                                  ENGINE2_DEFINITION,
                                                                  SIMCONNECT_OBJECT_ID_USER,
                                                                  SIMCONNECT_PERIOD_SIM_FRAME,
                                                                  SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
                            case 1:
                            default:
                                SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                                                  ENGINE1_REQUEST,
                                                                  ENGINE1_DEFINITION,
                                                                  SIMCONNECT_OBJECT_ID_USER,
                                                                  SIMCONNECT_PERIOD_SIM_FRAME,
                                                                  SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
                        }

                        SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                                          AIRCRAFT_GENERAL_REQUEST,
                                                          AIRCRAFT_GENERAL_DEFINITION,
                                                          SIMCONNECT_OBJECT_ID_USER,
                                                          SIMCONNECT_PERIOD_SIM_FRAME,
                                                          SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
                    }


                    if (d_sharedDataUpdated->load(std::memory_order_seq_cst))
                    {
                        d_sharedDataUpdated->store(false, std::memory_order_seq_cst);
                        processSharedData();


                        if (quit)
                            break;
                    }
                }
                else if (evt->uEventID == SIM_START_EVENT_ID)
                {
                    QByteArray dataToSend;
                    util::appendData(ServerMessageIdentifier::SIM_START_EVENT, dataToSend);
                    emit sendData(dataToSend);
                }
                else if (evt->uEventID == SIM_STOP_EVENT_ID)
                {
                    QByteArray dataToSend;
                    util::appendData(ServerMessageIdentifier::SIM_STOP_EVENT, dataToSend);
                    emit sendData(dataToSend);
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

                switch (pObjData->dwRequestID)
                {
                    case AIRSPEED_REQUEST:
                    {
                        emit sendData(d_airspeedHandler.processData(&pObjData->dwData));
                        break;
                    }
                    case ALTIMETER_REQUEST:
                    {
                        emit sendData(d_altitudeHandler.processData(&pObjData->dwData));
                        break;
                    }
                    case ATTITUDE_REQUEST:
                    {
                        emit sendData(d_attitudeHandler.processData(&pObjData->dwData));
                        break;
                    }
                    case BOTTOMBAR_REQUEST:
                    {
                        QByteArray dataToSend = d_bottombarHandler.processData(&pObjData->dwData);
                        if (!dataToSend.isEmpty())
                            emit sendData(dataToSend);

                        break;
                    }
                    case HSI_REQUEST:
                    {
                        emit sendData(d_hsiHandler.processData(&pObjData->dwData));
                        break;
                    }
                    case HSI_BRG_REQUEST:
                    {
                        emit sendData(d_bearingHandler.processData(&pObjData->dwData));
                        break;
                    }
                    case RADIO_REQUEST:
                    {
                        emit sendData(d_radioHandler.processData(&pObjData->dwData));
                        break;
                    }
                    case NAV_INFO_REQUEST:
                    {
                        emit sendData(d_navInfoHandler.processData(&pObjData->dwData));
                        break;
                    }
                    case WIND_REQUEST:
                    {
                        emit sendData(d_windHandler.processData(&pObjData->dwData));
                        break;
                    }
                    case AP_INFO_REQUEST:
                    {
                        QByteArray dataToSend = d_autopilotHandler.processData(&pObjData->dwData);
                        if (!dataToSend.isEmpty())
                            emit sendData(d_autopilotHandler.processData(&pObjData->dwData));

                        break;
                    }
                    case ENGINE1_REQUEST:
                    {
                        emit sendData(d_engine1Handler.processData(&pObjData->dwData));

                        break;
                    }
                    case ENGINE2_REQUEST:
                    {
                        emit sendData(d_engine2Handler.processData(&pObjData->dwData));

                        break;
                    }
                    case ENGINE3_REQUEST:
                    {
                        emit sendData(d_engine3Handler.processData(&pObjData->dwData));

                        break;
                    }
                    case ENGINE4_REQUEST:
                    {
                        emit sendData(d_engine4Handler.processData(&pObjData->dwData));

                        break;
                    }
                    case AIRCRAFT_GENERAL_REQUEST:
                    {
                        emit sendData(d_aircraftHandler.processData(&pObjData->dwData));

                        break;
                    }
                    case MISC_REQUEST:
                    {
                        bool wpIdValid = false;
                        QByteArray dataToSend = d_miscHandler.processData(&pObjData->dwData, &wpIdValid);
                        if (!dataToSend.isEmpty())
                            emit sendData(dataToSend);

                        dataToSend = d_hsiHandler.gpsWpNextIdValid(wpIdValid);
                        if (!dataToSend.isEmpty())
                            emit sendData(dataToSend);

                        break;
                    }
                    default:
                    {
                        emit receivedError(
                          QString("unknown simobject data request id received: %1").arg(pObjData->dwRequestID));
                        break;
                    }
                }
                break;
            }
            case SIMCONNECT_RECV_ID_EXCEPTION:
            {
                SIMCONNECT_RECV_EXCEPTION *pObjData = static_cast<SIMCONNECT_RECV_EXCEPTION *>(pData);
                processException(pObjData->dwException);

                [[fallthrough]];
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