#include "GaugeDefinition.hpp"

#include <QByteArray>

namespace definitions
{

std::string GaugeDefinition::toBinary() const
{
    std::string ret({ static_cast<char>(title.toStdString().size()) });
    ret += title.toStdString();

    ret.append({ static_cast<char>(unitString.toStdString().size()) });
    ret += unitString.toStdString();

    ret.append(reinterpret_cast<const char *>(&minValue), sizeof(minValue));
    ret.append(reinterpret_cast<const char *>(&maxValue), sizeof(maxValue));

    uint16_t listSize = colorZones.size();
    ret.append(reinterpret_cast<const char *>(&listSize), sizeof(listSize));

    for (const ColorZone &colorZone : colorZones)
    {
        ret.append(reinterpret_cast<const char *>(&colorZone.start), sizeof(colorZone.start));
        ret.append(reinterpret_cast<const char *>(&colorZone.end), sizeof(colorZone.end));
        ret.append({ static_cast<char>(colorZone.color.red()),
                     static_cast<char>(colorZone.color.green()),
                     static_cast<char>(colorZone.color.blue()) });
    }

    listSize = grads.size();
    ret.append(reinterpret_cast<const char *>(&listSize), sizeof(listSize));
    for (const GradDef &grad : grads)
    {
        ret.append(reinterpret_cast<const char *>(&grad.gradPos), sizeof(grad.gradPos));
        ret.append({ static_cast<char>(grad.isBig),
                     static_cast<char>(grad.gradColor.red()),
                     static_cast<char>(grad.gradColor.green()),
                     static_cast<char>(grad.gradColor.blue()) });
    }

    listSize = textGrads.size();
    ret.append(reinterpret_cast<const char *>(&listSize), sizeof(listSize));
    for (const TextGradDef &textGrad : textGrads)
    {
        ret.append(reinterpret_cast<const char *>(&textGrad.textGradPos), sizeof(textGrad.textGradPos));
        ret.append({ static_cast<char>(textGrad.gradText.toStdString().size()) });
        ret += textGrad.gradText.toStdString();
    }


    ret.append(reinterpret_cast<const char *>(&textIncrement), sizeof(textIncrement));
    ret.append({ static_cast<char>(textNumDigits) });

    ret.append({ static_cast<char>(forceTextColor) });
    ret.append({ static_cast<char>(textForcedColor.red()),
                 static_cast<char>(textForcedColor.green()),
                 static_cast<char>(textForcedColor.blue()) });

    ret.append({ static_cast<char>(hasMinRedBlink) });
    ret.append(reinterpret_cast<const char *>(&minRedBlinkThreshold), sizeof(minRedBlinkThreshold));
    ret.append({ static_cast<char>(hasMaxRedBlink) });
    ret.append(reinterpret_cast<const char *>(&maxRedBlinkThreshold), sizeof(maxRedBlinkThreshold));

    ret.append({ static_cast<char>(noText), static_cast<char>(unit) });

    return ret;
}


}  // namespace definitions