#include "GaugeDefinition.hpp"
#include "common/UnitConverter/UnitConverter.hpp"

#include <cmath>


namespace definitions
{

double GaugeDefinition::getEpsilon(bool isCircular,
                                   SwitchingGaugeType gaugeType,
                                   AircraftType aircraftType,
                                   double maxPower,
                                   double maxTorque) const
{
    Units localUnit = unit;
    double localMax = maxValue;
    double localMin = minValue;

    if (gaugeType == SwitchingGaugeType::POWER && unit == Units::PERCENT)
    {
        localUnit = Units::FT_LBF_SEC;
        localMax = (maxValue / 100.0) * maxPower;
        localMin = (minValue / 100.0) * maxPower;
    }
    else if (gaugeType == SwitchingGaugeType::TORQUE && aircraftType == AircraftType::PROP && unit == Units::PERCENT)
    {
        localUnit = Units::NEWTONMETER;
        localMax = (maxValue / 100.0) * maxTorque;
        localMin = (minValue / 100.0) * maxTorque;
    }
    // convert into the default units
    const double inversionFactor = 1 / UnitConverter::getMultiplier(localUnit);
    const double baseUnitRange = (localMax - localMin) * inversionFactor;
    const double textIncrementBaseValue = textIncrement * inversionFactor;

    // calculate an epsilon that should give about 4 positions per pixel on a 1920x1200 display
    const double eps = baseUnitRange / (isCircular ? 1750.0 : 500.0);

    return std::min(eps, textIncrementBaseValue / 4.0);
}

}  // namespace definitions