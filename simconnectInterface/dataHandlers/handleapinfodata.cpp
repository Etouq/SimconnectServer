#include "../simconnectthread.ih"


void SimconnectThread::handleApInfoData(const PfdApInfoStruct &newData)
{
    if (!d_lastSlowData.hasAp)
        return;

    DataIdentifiers id = DataIdentifiers::ALTITUDE;
    QByteArray dataToSend;


    if (d_lastApInfoData.ap_master != newData.ap_master)
    {
        d_lastApInfoData.ap_master = newData.ap_master;
        id = DataIdentifiers::AP_STATUS;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ap_master), sizeof(newData.ap_master));
    }
    if (d_lastApInfoData.ap_yaw_damper != newData.ap_yaw_damper)
    {
        d_lastApInfoData.ap_yaw_damper = newData.ap_yaw_damper;
        id = DataIdentifiers::AP_YD_STATUS;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ap_yaw_damper), sizeof(newData.ap_yaw_damper));
    }

    QByteArray AP_VerticalActive = "";
    QByteArray AP_ModeReference = "";
    QByteArray AP_Armed = "";
    QByteArray AP_ArmedReference = "";
    QByteArray AP_LateralActive = "";
    QByteArray AP_LateralArmed = "";

    uint8_t size = 0;


    // vertical active and modereference
    if (newData.ap_pitch_hold)
        AP_VerticalActive = "PIT";
    else if (newData.ap_flc)
    {
        AP_VerticalActive = "FLC";
        AP_ModeReference = QByteArray::number(d_lastApInfoData.ref_speed) + "KT";
    }
    else if (newData.ap_altitude_lock)
    {
        AP_VerticalActive = newData.ap_altitude_arm ? "ALTS" : "ALT";
        AP_ModeReference = QByteArray::number(d_lastApInfoData.ref_altitude) + "FT";
    }
    else if (newData.ap_vertical_hold)
    {
        AP_VerticalActive = "VS";
        AP_ModeReference = QByteArray::number(d_lastApInfoData.ref_vspeed) + "FPM";
    }
    else if (newData.ap_glideslope_active)
        AP_VerticalActive = d_lastApInfoData.gpsDrivesNav1 ? "GP" : "GS";

    if (d_lastAP_VerticalActive != AP_VerticalActive)
    {
        d_lastAP_VerticalActive = AP_VerticalActive;
        size = AP_VerticalActive.size();
        id = DataIdentifiers::AP_VERTICAL_ACTIVE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_VerticalActive.constData(), size);
    }
    if (d_lastAP_ModeReference != AP_ModeReference)
    {
        d_lastAP_ModeReference = AP_ModeReference;
        size = AP_ModeReference.size();
        id = DataIdentifiers::AP_MODE_REFERENCE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_ModeReference.constData(), size);
    }


    // armed and armed reference
    if (newData.ap_altitude_arm)
        AP_Armed = "ALT";
    else if (newData.ap_glideslope_arm)
    {
        if (d_lastApInfoData.gpsDrivesNav1)
        {
            AP_Armed = "V ALT";
            AP_ArmedReference = "GP";
        }
        else
            AP_Armed = "GS";
    }
    else if (newData.ap_vertical_hold)
        AP_Armed = "ALTS";

    if (d_lastAP_Armed != AP_Armed)
    {
        d_lastAP_Armed = AP_Armed;
        size = AP_Armed.size();
        id = DataIdentifiers::AP_ARMED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_Armed.constData(), size);
    }
    if (d_lastAP_ArmedReference != AP_ArmedReference)
    {
        d_lastAP_ArmedReference = AP_ArmedReference;
        size = AP_ArmedReference.size();
        id = DataIdentifiers::AP_ARMED_REFERENCE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_ArmedReference.constData(), size);
    }


    // lateral active
    if (newData.ap_wing_leveler)
        AP_LateralActive = "LVL";
    else if (newData.ap_bank_hold)
        AP_LateralActive = "ROL";
    else if (newData.ap_heading_lock)
        AP_LateralActive = "HDG";
    else if (newData.ap_nav1_lock)
    {
        if (d_lastApInfoData.gpsDrivesNav1)
            AP_LateralActive = "GPS";
        else
        {
            if ((d_lastApInfoData.autopilot_nav_selected == 1 && d_lastApInfoData.nav1_has_loc)
                || (d_lastApInfoData.autopilot_nav_selected == 2 && d_lastApInfoData.nav2_has_loc))
                AP_LateralActive = "LOC";
            else
                AP_LateralActive = "VOR";
        }
    }
    else if (newData.ap_backcourse_hold)
        AP_LateralActive = "BC";
    else if (newData.autopilot_approach_hold)
    {
        if (d_lastApInfoData.gpsDrivesNav1)
            AP_LateralActive = "GPS";
        else
        {
            if ((d_lastApInfoData.autopilot_nav_selected == 1 && d_lastApInfoData.nav1_has_loc)
                || (d_lastApInfoData.autopilot_nav_selected == 2 && d_lastApInfoData.nav2_has_loc))
                AP_LateralActive = "LOC";
            else
                AP_LateralActive = "VOR";
        }
    }

    if (d_lastAP_LateralActive != AP_LateralActive)
    {
        d_lastAP_LateralActive = AP_LateralActive;
        size = AP_LateralActive.size();
        id = DataIdentifiers::AP_LATERAL_ACTIVE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_LateralActive.constData(), size);
    }


    // lateral armed
    if (newData.ap_heading_lock || newData.ap_wing_leveler)
    {
        if (newData.ap_nav1_lock)
        {
            if (d_lastApInfoData.gpsDrivesNav1)
                AP_LateralArmed = "GPS";
            else
            {
                if ((d_lastApInfoData.autopilot_nav_selected == 1 && d_lastApInfoData.nav1_has_loc)
                    || (d_lastApInfoData.autopilot_nav_selected == 2 && d_lastApInfoData.nav2_has_loc))
                    AP_LateralArmed = "LOC";
                else
                    AP_LateralArmed = "VOR";
            }
        }
        else if (newData.ap_backcourse_hold)
            AP_LateralArmed = "BC";
        else if (newData.autopilot_approach_hold)
        {
            if (d_lastApInfoData.gpsDrivesNav1)
                AP_LateralArmed = "GPS";
            else
            {
                if ((d_lastApInfoData.autopilot_nav_selected == 1 && d_lastApInfoData.nav1_has_loc)
                    || (d_lastApInfoData.autopilot_nav_selected == 2 && d_lastApInfoData.nav2_has_loc))
                    AP_LateralArmed = "LOC";
                else
                    AP_LateralArmed = "VOR";
            }
        }
    }

    if (d_lastAP_LateralArmed != AP_LateralArmed)
    {
        d_lastAP_LateralArmed = AP_LateralArmed;
        size = AP_LateralArmed.size();
        id = DataIdentifiers::AP_LATERAL_ARMED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
        dataToSend.append(AP_LateralArmed.constData(), size);
    }



    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}
