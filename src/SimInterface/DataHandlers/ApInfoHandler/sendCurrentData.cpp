#include "ApInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace apinfo
{

std::string ApInfoHandler::sendCurrentData()
{
    std::string dataToSend;
    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_STATUS) });
    dataToSend.append(reinterpret_cast<const char *>(&d_apMaster), sizeof(d_apMaster));

    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_YD_STATUS) });
    dataToSend.append(reinterpret_cast<const char *>(&d_yawDamper), sizeof(d_yawDamper));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_FLC) });
    dataToSend.append(reinterpret_cast<const char *>(&d_flc), sizeof(d_flc));

    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_VERTICAL_ACTIVE) });
    dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(d_verticalActive.size())));
    dataToSend += d_verticalActive;

    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_MODE_REFERENCE) });
    dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(d_modeReference.size())));
    dataToSend += d_modeReference;


    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_ARMED) });
    dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(d_armed.size())));
    dataToSend += d_armed;

    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_ARMED_REFERENCE) });
    dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(d_armedReference.size())));
    dataToSend += d_armedReference;


    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_LATERAL_ACTIVE) });
    dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(d_lateralActive.size())));
    dataToSend += d_lateralActive;

    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_LATERAL_ARMED) });
    dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(d_lateralArmed.size())));
    dataToSend += d_lateralArmed;


    return dataToSend;
}

}  // namespace apinfo
