#include "EngineHandler.hpp"


namespace handler::engine
{

std::string EngineHandler::gaugeTypeToUnit(SwitchingGaugeType gaugeType, AircraftType aircraftType, Units unit)
{
    switch (gaugeType)
    {
        case SwitchingGaugeType::N1:
        case SwitchingGaugeType::N2:
            return "percent";
        case SwitchingGaugeType::ENGINE_TEMP:
            return "celsius";
        case SwitchingGaugeType::RPM:
        case SwitchingGaugeType::PROP_RPM:
        {
            if (unit == Units::PERCENT)
                return "percent";
            return "rpm";
        }
        case SwitchingGaugeType::POWER:
            return "ft lb per second";
        case SwitchingGaugeType::MANIFOLD_PRESSURE:
            return "kpa";
        case SwitchingGaugeType::TORQUE:
        {
            if (aircraftType == AircraftType::PROP)
                return "newton meter";

            if (unit == Units::PERCENT)
                return "percent";
            return "newton meter";
        }
        case SwitchingGaugeType::NONE:
            return "";
    }
}

}  // namespace handler::engine
