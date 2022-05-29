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
                        emit sendData(d_aircraftHandler->reset());

                        SimConnect_ClearDataDefinition(d_simConnectHandle, ENGINE_DEFINITION);

                        if (d_aircraftHandler != nullptr)
                            delete d_aircraftHandler;

                        switch (d_aircraftConfig.type)
                        {
                            case AircraftType::JET:
                                d_aircraftHandler = new JetHandler();
                                break;
                            case AircraftType::PROP:
                                d_aircraftHandler = new PropHandler();
                                break;
                            case AircraftType::TURBOPROP:
                                d_aircraftHandler = new TurbopropHandler();
                                break;
                        }

                        d_aircraftHandler->setupData(d_simConnectHandle, d_aircraftConfig);

                        updateAircraft = false;
                        SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                                          ENGINE_REQUEST,
                                                          ENGINE_DEFINITION,
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
                    SimconnectIds id = SimconnectIds::SIM_START_EVENT;
                    emit sendData(QByteArray(reinterpret_cast<char *>(&id), sizeof(id)));
                }
                else if (evt->uEventID == SIM_STOP_EVENT_ID)
                {
                    SimconnectIds id = SimconnectIds::SIM_STOP_EVENT;
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
                            emit sendData(dataToSend);

                        break;
                    }
                    case ENGINE_REQUEST:
                    {
                        QByteArray dataToSend = d_aircraftHandler->processData(&pObjData->dwData);
                        if (!dataToSend.isEmpty())
                            emit sendData(dataToSend);

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