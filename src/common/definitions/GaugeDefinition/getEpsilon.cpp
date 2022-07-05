#include "GaugeDefinition.hpp"
#include "common/UnitConverter/UnitConverter.hpp"
#include <cmath>

namespace definitions
{

double GaugeDefinition::getEpsilon(bool isCircular) const
{
    // convert into the default units
    double inversionFactor = 1 / UnitConverter::getMultiplier(unit);
    double baseUnitRange = (maxValue - minValue) * inversionFactor;
    double textIncrementBaseValue = textIncrement * inversionFactor;

    double eps = 0;
    // calculate an epsilon that should give about 4 positions per pixel on a 1920x1200 display
    if (isCircular)
        eps = baseUnitRange / 1750.0;
    else
        eps = baseUnitRange / 500.0;

    return std::min(eps, textIncrementBaseValue / 4.0);
}

}  // namespace definitions