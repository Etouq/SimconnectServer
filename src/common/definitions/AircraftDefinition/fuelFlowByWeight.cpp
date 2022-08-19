#include "AircraftDefinition.hpp"

namespace definitions
{

bool AircraftDefinition::fuelFlowByWeight() const
{
    switch (fuelFlowGauge.unit)
    {
        case Units::KG_PER_HOUR:
        case Units::TONNE_PER_HOUR:
        case Units::SLUG_PER_HOUR:
        case Units::GRAM_PER_HOUR:
        case Units::LBS_PER_HOUR:
        case Units::USTONNE_PER_HOUR:
        case Units::UKTONNE_PER_HOUR:
        case Units::KG_PER_MINUTE:
        case Units::TONNE_PER_MINUTE:
        case Units::SLUG_PER_MINUTE:
        case Units::GRAM_PER_MINUTE:
        case Units::LBS_PER_MINUTE:
        case Units::USTONNE_PER_MINUTE:
        case Units::UKTONNE_PER_MINUTE:
        case Units::KG_PER_SECOND:
        case Units::TONNE_PER_SECOND:
        case Units::SLUG_PER_SECOND:
        case Units::GRAM_PER_SECOND:
        case Units::LBS_PER_SECOND:
        case Units::USTONNE_PER_SECOND:
        case Units::UKTONNE_PER_SECOND:
            return true;
        default:
            return false;
    }
}

}  // namespace definitions
