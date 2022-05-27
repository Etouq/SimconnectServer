#include "ApInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace apinfo
{

QByteArray ApInfoHandler::processData(unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<DataStruct *>(raw));
    SimconnectIds id = SimconnectIds::AP_STATUS;
    QByteArray dataToSend;

    if (d_apMaster != newData.apMaster)
    {
        d_apMaster = newData.apMaster;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.apMaster), sizeof(newData.apMaster));
    }
    if (d_yawDamper != newData.apYawDamper)
    {
        d_yawDamper = newData.apYawDamper;
        id = SimconnectIds::AP_YD_STATUS;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.apYawDamper), sizeof(newData.apYawDamper));
    }

    QByteArray AP_VerticalActive = "";
    QByteArray AP_ModeReference = "";
    QByteArray AP_Armed = "";
    QByteArray AP_ArmedReference = "";
    QByteArray AP_LateralActive = "";
    QByteArray AP_LateralArmed = "";

    uint8_t size = 0;


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
                AP_ModeReference = "." + QByteArray::number(static_cast<int>(newData.refMach * 1000 + 0.5));
            }
            else [[likely]]
            {
                AP_ModeReference = QByteArray::number(newData.refMach, 'f', 3);
            }
        }
        else [[likely]]
        {
            AP_ModeReference = QByteArray::number(newData.refSpeed) + "KT";
        }
    }
    else if (newData.apMachHold) [[unlikely]]
    {
        AP_VerticalActive = "FLC";
        if (newData.refMach < 1.0) [[unlikely]]
        {
            AP_ModeReference = "." + QByteArray::number(static_cast<int>(newData.refMach * 1000 + 0.5));
        }
        else [[likely]]
        {
            AP_ModeReference = QByteArray::number(newData.refMach, 'f', 3);
        }
    }
    else if (newData.apAltitudeLock) [[likely]]
    {
        AP_VerticalActive = newData.apAltitudeArm ? "ALTS" : "ALT";
        AP_ModeReference = QByteArray::number(newData.refAltitude) + "FT";
    }
    else if (newData.apVerticalHold) [[likely]]
    {
        AP_VerticalActive = "VS";
        AP_ModeReference = QByteArray::number(newData.refVspeed) + "FPM";
    }
    else if (newData.apGlideslopeActive)
        AP_VerticalActive = newData.gpsDrivesNav1 ? "GP" : "GS";

    if (d_verticalActive != AP_VerticalActive)
    {
        d_verticalActive = AP_VerticalActive;
        size = AP_VerticalActive.size();
        id = SimconnectIds::AP_VERTICAL_ACTIVE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_VerticalActive.constData(), size);
    }
    if (d_modeReference != AP_ModeReference)
    {
        d_modeReference = AP_ModeReference;
        size = AP_ModeReference.size();
        id = SimconnectIds::AP_MODE_REFERENCE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_ModeReference.constData(), size);
    }


    // armed and armed reference
    if (newData.apAltitudeArm)
        AP_Armed = "ALT";
    else if (newData.apGlideslopeArm)
    {
        if (d_previous.gpsDrivesNav1)
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
        size = AP_Armed.size();
        id = SimconnectIds::AP_ARMED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_Armed.constData(), size);
    }
    if (d_armedReference != AP_ArmedReference)
    {
        d_armedReference = AP_ArmedReference;
        size = AP_ArmedReference.size();
        id = SimconnectIds::AP_ARMED_REFERENCE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_ArmedReference.constData(), size);
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
        size = AP_LateralActive.size();
        id = SimconnectIds::AP_LATERAL_ACTIVE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_LateralActive.constData(), size);
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
        size = AP_LateralArmed.size();
        id = SimconnectIds::AP_LATERAL_ARMED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_LateralArmed.constData(), size);
    }

    return dataToSend;
}

}  // namespace apinfo
