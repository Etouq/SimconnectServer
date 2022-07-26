#include "AltitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace altitude
{

std::string AltitudeHandler::sendCurrentData()
{
    std::string dataToSend;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ALTITUDE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.altitude), sizeof(d_previous.altitude));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::RADAR_ALTITUDE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.radarAltitude), sizeof(d_previous.radarAltitude));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::REF_ALTITUDE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.refAltitude), sizeof(d_previous.refAltitude));

    d_previous.pressure = d_previous.pressure;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::PRESSURE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.pressure), sizeof(d_previous.pressure));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::VSPEED) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.vspeed), sizeof(d_previous.vspeed));

    d_previous.refVspeed = d_previous.refVspeed;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::REF_VSPEED) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.refVspeed), sizeof(d_previous.refVspeed));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::VERT_DEV_MODE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_vertDevMode), sizeof(d_vertDevMode));
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::VERT_DEV_VALUE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_deviation), sizeof(d_deviation));

    return dataToSend;
}

}  // namespace altitude
