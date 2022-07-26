#include "AltitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace altitude
{

void AltitudeHandler::handleNav1(std::string &dataToSend, const DataStruct &newData)
{
    if (newData.nav1HasGlideslope) [[unlikely]]
    {
        if (d_vertDevMode != VerticalDeviationMode::GS) [[unlikely]]
        {
            d_vertDevMode = VerticalDeviationMode::GS;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::VERT_DEV_MODE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_vertDevMode), sizeof(d_vertDevMode));

            // update deviation as well
            d_previous.nav1Gsi = newData.nav1Gsi;
            d_deviation = newData.nav1Gsi / 127.0;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::VERT_DEV_VALUE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_deviation), sizeof(d_deviation));
        }
        else if (std::abs(d_previous.nav1Gsi - newData.nav1Gsi) >= 0.1) [[likely]]
        {
            d_previous.nav1Gsi = newData.nav1Gsi;
            d_deviation = newData.nav1Gsi / 127.0;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::VERT_DEV_VALUE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_deviation), sizeof(d_deviation));
        }
    }
    else if (d_vertDevMode != VerticalDeviationMode::NONE) [[unlikely]]
    {
        d_vertDevMode = VerticalDeviationMode::NONE;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::VERT_DEV_MODE) });
        dataToSend.append(reinterpret_cast<const char*>(&d_vertDevMode), sizeof(d_vertDevMode));
    }
}

}  // namespace altitude
