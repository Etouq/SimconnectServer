#ifndef GAUGEDEFINITION_H
#define GAUGEDEFINITION_H

#include "../BaseTypes.hpp"
#include "common/Units.hpp"

#include <cstdint>
#include <QColor>
#include <QString>
#include <string>
#include <QList>

class QIODevice;
class QByteArray;

namespace definitions
{

// definition used to display a gauge
struct GaugeDefinition
{

    QString title = "";
    QString unitString = "";

    double minValue = 0;
    double maxValue = 0;

    QList<ColorZone> colorZones;
    QList<GradDef> grads;
    QList<TextGradDef> textGrads;

    double textIncrement = 1;
    int8_t textNumDigits = 0;

    bool forceTextColor = false;
    QColor textForcedColor = QColor();

    bool hasMinRedBlink = false;
    double minRedBlinkThreshold = 0;
    bool hasMaxRedBlink = false;
    double maxRedBlinkThreshold = 0;

    bool noText = false;

    Units unit = Units::NONE;

    std::string toBinary() const;

    static GaugeDefinition fromBinary(QIODevice &data, FileVersion version)
    {
        switch (version)
        {
            case FileVersion::V1:
            case FileVersion::V2:
                return fromBinaryV1(data);
                break;
            case FileVersion::V3:
                return fromBinaryV3(data);
                break;
        }
    }

    double getEpsilon(bool isCircular) const;

private:

    static GaugeDefinition fromBinaryV1(QIODevice &data);
    static GaugeDefinition fromBinaryV3(QIODevice &data);
};

}  // namespace definitions


#endif  // GAUGEDEFINITION_H
