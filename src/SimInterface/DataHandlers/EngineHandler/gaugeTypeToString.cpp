#include "EngineHandler.hpp"


namespace handler::engine
{

std::string EngineHandler::gaugeTypeToString(SwitchingGaugeType gaugeType, AircraftType aircraftType, TemperatureGaugeType tempGaugeType)
{
    switch (gaugeType)
    {
        case SwitchingGaugeType::N1:
            return "TURB ENG N1:" + std::to_string(d_engineIdx);
        case SwitchingGaugeType::N2:
            return "TURB ENG N2:" + std::to_string(d_engineIdx);
        case SwitchingGaugeType::ENGINE_TEMP:
        {
            switch (tempGaugeType)
            {
                case TemperatureGaugeType::EGT:
                    return "GENERAL ENG EXHAUST GAS TEMPERATURE:" + std::to_string(d_engineIdx);
                case TemperatureGaugeType::ITT:
                    return "TURB ENG ITT:" + std::to_string(d_engineIdx);
                case TemperatureGaugeType::CHT:
                {
                    if (aircraftType == AircraftType::PROP)
                        return "RECIP ENG CYLINDER HEAD TEMPERATURE:" + std::to_string(d_engineIdx);
                    return "ENG CYLINDER HEAD TEMPERATURE:" + std::to_string(d_engineIdx);
                }
                case TemperatureGaugeType::TIT:
                    return "RECIP ENG TURBINE INLET TEMPERATURE:" + std::to_string(d_engineIdx);
            }
        }
        case SwitchingGaugeType::RPM:
            return "GENERAL ENG RPM:" + std::to_string(d_engineIdx);
        case SwitchingGaugeType::RPM_PCT:
            return "GENERAL ENG PCT MAX RPM:" + std::to_string(d_engineIdx);
        case SwitchingGaugeType::PROP_RPM:
            return "PROP RPM:" + std::to_string(d_engineIdx);
        case SwitchingGaugeType::PROP_RPM_PCT:
            return "PROP MAX RPM PERCENT:" + std::to_string(d_engineIdx);
        case SwitchingGaugeType::POWER:
        case SwitchingGaugeType::POWER_PCT:
            return "RECIP ENG BRAKE POWER:" + std::to_string(d_engineIdx);
        case SwitchingGaugeType::MANIFOLD_PRESSURE:
            return "RECIP ENG MANIFOLD PRESSURE:" + std::to_string(d_engineIdx);
        case SwitchingGaugeType::TORQUE:
        {
            if (aircraftType == AircraftType::PROP)
                return "ENG TORQUE:" + std::to_string(d_engineIdx);
            return "TURB ENG FREE TURBINE TORQUE:" + std::to_string(d_engineIdx);
        }
        case SwitchingGaugeType::TORQUE_PCT:
            return "TURB ENG MAX TORQUE PERCENT:" + std::to_string(d_engineIdx);
        case SwitchingGaugeType::NONE:
            return "";
    }
}

}  // namespace handler::engine
