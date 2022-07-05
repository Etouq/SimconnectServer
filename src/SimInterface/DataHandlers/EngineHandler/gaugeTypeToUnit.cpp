#include "EngineHandler.hpp"


namespace handler::engine
{

std::string EngineHandler::gaugeTypeToUnit(SwitchingGaugeType gaugeType)
{
    switch (gaugeType)
    {
        case SwitchingGaugeType::N1:
        case SwitchingGaugeType::N2:
        case SwitchingGaugeType::RPM_PCT:
        case SwitchingGaugeType::TORQUE_PCT:
        case SwitchingGaugeType::PROP_RPM_PCT:
            return "percent";
        case SwitchingGaugeType::ENGINE_TEMP:
            return "celsius";
        case SwitchingGaugeType::RPM:
        case SwitchingGaugeType::PROP_RPM:
            return "rpm";
        case SwitchingGaugeType::POWER:
        case SwitchingGaugeType::POWER_PCT:
            return "ft lb per second";
        case SwitchingGaugeType::MANIFOLD_PRESSURE:
            return "kpa";
        case SwitchingGaugeType::TORQUE:
            return "newton meter";
        case SwitchingGaugeType::NONE:
            return "";
    }
}

}  // namespace handler::engine
