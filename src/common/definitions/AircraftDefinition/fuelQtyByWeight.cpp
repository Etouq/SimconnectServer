#include "AircraftDefinition.hpp"

namespace definitions
{

bool AircraftDefinition::fuelQtyByWeight() const
{
    switch (fuelQtyGauge.unit)
    {
        case Units::KG:
        case Units::TONNE:
        case Units::SLUG:
        case Units::GRAM:
        case Units::LBS:
        case Units::USTONNE:
        case Units::UKTONNE:
            return true;
        default:
            return false;
    }
}

}  // namespace definitions
