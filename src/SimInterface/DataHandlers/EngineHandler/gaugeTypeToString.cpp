#include "EngineHandler.hpp"

namespace handler::engine
{

std::string EngineHandler::gaugeTypeToString(SwitchingGaugeType gaugeType,
                                             AircraftType aircraftType,
                                             TemperatureGaugeType tempGaugeType,
                                             Units unit)
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
        {
            if (unit == Units::PERCENT)
                return "GENERAL ENG PCT MAX RPM:" + std::to_string(d_engineIdx);
            return "GENERAL ENG RPM:" + std::to_string(d_engineIdx);
        }
        case SwitchingGaugeType::PROP_RPM:
        {
            if (unit == Units::PERCENT)
                return "PROP MAX RPM PERCENT:" + std::to_string(d_engineIdx);
            return "PROP RPM:" + std::to_string(d_engineIdx);
        }
        case SwitchingGaugeType::POWER:
            return "RECIP ENG BRAKE POWER:" + std::to_string(d_engineIdx);
        case SwitchingGaugeType::MANIFOLD_PRESSURE:
            return "RECIP ENG MANIFOLD PRESSURE:" + std::to_string(d_engineIdx);
        case SwitchingGaugeType::TORQUE:
        {
            if (aircraftType == AircraftType::PROP)
                return "ENG TORQUE:" + std::to_string(d_engineIdx);

            if (unit == Units::PERCENT)
                return "TURB ENG MAX TORQUE PERCENT:" + std::to_string(d_engineIdx);
            return "TURB ENG FREE TURBINE TORQUE:" + std::to_string(d_engineIdx);
        }
        case SwitchingGaugeType::NONE:
            return "";
    }
}

}  // namespace handler::engine
