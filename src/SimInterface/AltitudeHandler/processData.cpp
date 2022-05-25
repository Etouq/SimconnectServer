#include "../SimInterface.hpp"
#include "AltitudeHandler.hpp"
#include "common/simEnums.hpp"

#include <cmath>

namespace altitude
{

void AltitudeHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));
    SimconnectIds id = SimconnectIds::ALTITUDE;
    QByteArray dataToSend;

    if (std::abs(d_previous.altitude - newData.altitude) >= 0.09)
    {
        d_previous.altitude = newData.altitude;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.altitude), sizeof(newData.altitude));
    }

    if (std::abs(d_previous.radarAltitude - newData.radarAltitude) >= 0.09)
    {
        d_previous.radarAltitude = newData.radarAltitude;
        id = SimconnectIds::RADAR_ALTITUDE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.radarAltitude), sizeof(newData.radarAltitude));
    }

    if (d_previous.refAltitude != newData.refAltitude)
    {
        d_previous.refAltitude = newData.refAltitude;
        id = SimconnectIds::REF_ALTITUDE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.refAltitude), sizeof(newData.refAltitude));
    }

    if (std::abs(d_previous.pressure - newData.pressure) >= 0.009)
    {
        d_previous.pressure = newData.pressure;
        id = SimconnectIds::PRESSURE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.pressure), sizeof(newData.pressure));
    }


    if (std::abs(d_previous.vspeed - newData.vspeed) >= 0.009)
    {
        d_previous.vspeed = newData.vspeed;
        id = SimconnectIds::VSPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.vspeed), sizeof(newData.vspeed));
    }

    if (d_previous.refVspeed != newData.refVspeed)
    {
        d_previous.refVspeed = newData.refVspeed;
        id = SimconnectIds::REF_VSPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.refVspeed), sizeof(newData.refVspeed));
    }


    int32_t cdiSource = newData.gpsDrivesNav1 ? 3 : newData.autopilotNavSelected;
    switch (cdiSource)
    {
        case 1:  // nav1
        {
            if (newData.nav1HasGlideslope)
            {
                if (d_lastVertMode != VerticalDeviationMode::GS)
                {
                    d_lastVertMode = VerticalDeviationMode::GS;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    // update deviation as well
                    d_previous.nav1Gsi = newData.nav1Gsi;
                    d_deviation = newData.nav1Gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
                }
                else if (std::abs(d_previous.nav1Gsi - newData.nav1Gsi) >= 0.1)
                {
                    d_previous.nav1Gsi = newData.nav1Gsi;
                    d_deviation = newData.nav1Gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
                }
            }
            else if (d_lastVertMode != VerticalDeviationMode::NONE)
            {
                d_lastVertMode = VerticalDeviationMode::NONE;
                id = SimconnectIds::VERT_DEV_MODE;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));
            }
            break;
        }
        case 2:  // nav2
        {
            if (newData.nav2HasGlideslope)
            {
                if (d_lastVertMode != VerticalDeviationMode::GS)
                {
                    d_lastVertMode = VerticalDeviationMode::GS;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    // update deviation as well
                    d_previous.nav2Gsi = newData.nav2Gsi;
                    d_deviation = newData.nav2Gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));

                }
                else if (std::abs(d_previous.nav2Gsi - newData.nav2Gsi) >= 0.1)
                {
                    d_previous.nav2Gsi = newData.nav2Gsi;
                    d_deviation = newData.nav2Gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
                }
            }
            else if (d_lastVertMode != VerticalDeviationMode::NONE)
            {
                d_lastVertMode = VerticalDeviationMode::NONE;
                id = SimconnectIds::VERT_DEV_MODE;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));
            }
            break;
        }
        case 3:  // gps
        {
            if ((newData.gpsApproachActive || newData.apApproachActive) && newData.gpsApproachApproachType == ApproachType::RNAV)
            {
                if (d_lastVertMode != VerticalDeviationMode::GP)
                {
                    d_lastVertMode = VerticalDeviationMode::GP;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    // update deviation as well
                    d_previous.gpsVertError = newData.gpsVertError;
                    d_deviation = newData.gpsVertError / 150.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));

                }
                else if (std::abs(d_previous.gpsVertError - newData.gpsVertError) >= 0.1)
                {
                    d_previous.gpsVertError = newData.gpsVertError;
                    d_deviation = newData.gpsVertError / 150.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
                }
            }
            else if (newData.nav1HasGlideslope)
            {
                if (d_lastVertMode != VerticalDeviationMode::GSPREVIEW)
                {
                    d_lastVertMode = VerticalDeviationMode::GSPREVIEW;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    // update deviation as well
                    d_previous.nav1Gsi = newData.nav1Gsi;
                    d_deviation = newData.nav1Gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));

                }
                else if (std::abs(d_previous.nav1Gsi - newData.nav1Gsi) >= 0.1)
                {
                    d_previous.nav1Gsi = newData.nav1Gsi;
                    d_deviation = newData.nav1Gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
                }
            }
            else if (newData.nav2HasGlideslope)
            {
                if (d_lastVertMode != VerticalDeviationMode::GSPREVIEW)
                {
                    d_lastVertMode = VerticalDeviationMode::GSPREVIEW;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    // update deviation as well
                    d_previous.nav2Gsi = newData.nav2Gsi;
                    d_deviation = newData.nav2Gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));

                }
                else if (std::abs(d_previous.nav2Gsi - newData.nav2Gsi) >= 0.1)
                {
                    d_previous.nav2Gsi = newData.nav2Gsi;
                    d_deviation = newData.nav2Gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
                }
            }
            else if (d_lastVertMode != VerticalDeviationMode::NONE)
            {
                d_lastVertMode = VerticalDeviationMode::NONE;
                id = SimconnectIds::VERT_DEV_MODE;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));
            }

            break;
        }
        default:
        {
            if (d_lastVertMode != VerticalDeviationMode::NONE)
            {
                d_lastVertMode = VerticalDeviationMode::NONE;
                id = SimconnectIds::VERT_DEV_MODE;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));
            }
        }
    }


    if (!dataToSend.isEmpty())
        emit d_parent->sendData(dataToSend);
}

}  // namespace altitude
