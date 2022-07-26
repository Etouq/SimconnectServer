#include "ApInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "DataStruct.hpp"

#include <fmt/core.h>
#include <cmath>

namespace apinfo
{

std::string ApInfoHandler::processData(unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<DataStruct *>(raw));

    std::string dataToSend;

    if (d_apMaster != newData.apMaster)
    {
        d_apMaster = newData.apMaster;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_STATUS) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.apMaster), sizeof(newData.apMaster));
    }
    if (d_yawDamper != newData.apYawDamper)
    {
        d_yawDamper = newData.apYawDamper;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_YD_STATUS) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.apYawDamper), sizeof(newData.apYawDamper));
    }
    if (d_flc != newData.apFlc)
    {
        d_flc = newData.apFlc;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_FLC) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.apFlc), sizeof(newData.apFlc));
    }

    std::string AP_VerticalActive = "";
    std::string AP_ModeReference = "";
    std::string AP_Armed = "";
    std::string AP_ArmedReference = "";
    std::string AP_LateralActive = "";
    std::string AP_LateralArmed = "";


    // vertical active and modereference
    if (newData.apPitchHold)
        AP_VerticalActive = "PIT";
    else if (newData.apFlc) [[unlikely]]
    {
        AP_VerticalActive = "FLC";
        if (newData.apManagedInMach) [[unlikely]]
        {
            if (newData.refMach < 1.0) [[unlikely]]
            {
                AP_ModeReference = fmt::format(".{0:03d}", std::lround(newData.refMach * 1000));
            }
            else [[likely]]
            {
                AP_ModeReference = fmt::format("{0:.3f}", newData.refMach);
            }
        }
        else [[likely]]
        {
            AP_ModeReference = fmt::format("{0:d}KT", newData.refSpeed);
        }
    }
    else if (newData.apMachHold) [[unlikely]]
    {
        AP_VerticalActive = "FLC";
        if (newData.refMach < 1.0) [[unlikely]]
        {
            AP_ModeReference = fmt::format(".{0:03d}", std::lround(newData.refMach * 1000));
        }
        else [[likely]]
        {
            AP_ModeReference = fmt::format("{0:.3f}", newData.refMach);
        }
    }
    else if (newData.apAltitudeLock) [[likely]]
    {
        AP_VerticalActive = newData.apAltitudeArm ? "ALTS" : "ALT";
        AP_ModeReference = fmt::format("{0:d}FT", newData.refAltitude);
    }
    else if (newData.apVerticalHold) [[likely]]
    {
        AP_VerticalActive = "VS";
        AP_ModeReference = fmt::format("{0:d}FPM", newData.refVspeed);
    }
    else if (newData.apGlideslopeActive)
        AP_VerticalActive = newData.gpsDrivesNav1 ? "GP" : "GS";

    if (d_verticalActive != AP_VerticalActive)
    {
        d_verticalActive = AP_VerticalActive;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_VERTICAL_ACTIVE) });
        dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(AP_VerticalActive.size())));
        dataToSend += AP_VerticalActive;
    }
    if (d_modeReference != AP_ModeReference)
    {
        d_modeReference = AP_ModeReference;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_MODE_REFERENCE) });
        dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(AP_ModeReference.size())));
        dataToSend += AP_ModeReference;
    }


    // armed and armed reference
    if (newData.apAltitudeArm)
        AP_Armed = "ALT";
    else if (newData.apGlideslopeArm)
    {
        if (newData.gpsDrivesNav1)
        {
            AP_Armed = "V ALT";
            AP_ArmedReference = "GP";
        }
        else
            AP_Armed = "GS";
    }
    else if (newData.apVerticalHold)
        AP_Armed = "ALTS";

    if (d_armed != AP_Armed)
    {
        d_armed = AP_Armed;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_ARMED) });
        dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(AP_Armed.size())));
        dataToSend += AP_Armed;
    }
    if (d_armedReference != AP_ArmedReference)
    {
        d_armedReference = AP_ArmedReference;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_ARMED_REFERENCE) });
        dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(AP_ArmedReference.size())));
        dataToSend += AP_ArmedReference;
    }


    // lateral active
    if (newData.apWingLeveler)
        AP_LateralActive = "LVL";
    else if (newData.apBankHold)
        AP_LateralActive = "ROL";
    else if (newData.apHeadingLock) [[likely]]
        AP_LateralActive = "HDG";
    else if (newData.apNav1Lock) [[likely]]
    {
        if (newData.gpsDrivesNav1)
            AP_LateralActive = "GPS";
        else
        {
            if ((newData.autopilotNavSelected == 1 && newData.nav1HasLoc)
                || (newData.autopilotNavSelected == 2 && newData.nav2HasLoc))
                AP_LateralActive = "LOC";
            else
                AP_LateralActive = "VOR";
        }
    }
    else if (newData.apBackcourseHold)
        AP_LateralActive = "BC";
    else if (newData.autopilotApproachHold)
    {
        if (newData.gpsDrivesNav1)
            AP_LateralActive = "GPS";
        else
        {
            if ((newData.autopilotNavSelected == 1 && newData.nav1HasLoc)
                || (newData.autopilotNavSelected == 2 && newData.nav2HasLoc))
                AP_LateralActive = "LOC";
            else
                AP_LateralActive = "VOR";
        }
    }

    if (d_lateralActive != AP_LateralActive)
    {
        d_lateralActive = AP_LateralActive;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_LATERAL_ACTIVE) });
        dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(AP_LateralActive.size())));
        dataToSend += AP_LateralActive;
    }


    // lateral armed
    if (newData.apHeadingLock || newData.apWingLeveler)
    {
        if (newData.apNav1Lock)
        {
            if (newData.gpsDrivesNav1)
                AP_LateralArmed = "GPS";
            else
            {
                if ((newData.autopilotNavSelected == 1 && newData.nav1HasLoc)
                    || (newData.autopilotNavSelected == 2 && newData.nav2HasLoc))
                    AP_LateralArmed = "LOC";
                else
                    AP_LateralArmed = "VOR";
            }
        }
        else if (newData.apBackcourseHold)
            AP_LateralArmed = "BC";
        else if (newData.autopilotApproachHold)
        {
            if (newData.gpsDrivesNav1)
                AP_LateralArmed = "GPS";
            else
            {
                if ((newData.autopilotNavSelected == 1 && newData.nav1HasLoc)
                    || (newData.autopilotNavSelected == 2 && newData.nav2HasLoc))
                    AP_LateralArmed = "LOC";
                else
                    AP_LateralArmed = "VOR";
            }
        }
    }

    if (d_lateralArmed != AP_LateralArmed)
    {
        d_lateralArmed = AP_LateralArmed;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_LATERAL_ARMED) });
        dataToSend.push_back(static_cast<char>(static_cast<uint8_t>(AP_LateralArmed.size())));
        dataToSend += AP_LateralArmed;
    }

    return dataToSend;
}

}  // namespace apinfo
