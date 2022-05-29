#ifndef FLIGHTPLANREADER_H
#define FLIGHTPLANREADER_H

#include <QGeoCoordinate>
#include <QList>
#include <QObject>
#include <QRegularExpression>
#include <QString>
#include <QXmlStreamReader>
#include <cstdint>

class QFile;

struct FlightPlanWaypoint
{
    QGeoCoordinate position = QGeoCoordinate(0, 0);
    int32_t alt1 = 0;
    int32_t alt2 = 0;
    QString ident = "";
    int8_t wpType = 0;    // 0: airport, 1: intersection, 2: ndb, 3: user, 4: vor TODO: look into
                          // more types such as vor-dme etc
    int8_t altType = 0;   // -1: none/invalid, 0: at, 1: at or above, 2: at or below, 3: between
};

class FlightplanReader
{

    inline static QXmlStreamReader flightPlanXml = QXmlStreamReader();

    inline static const QRegularExpression llaRegExp = QRegularExpression(
      R"delim(([NS])\s*(\d+)\s*°\s*(\d+)\s*'\s*(\d+\.?\d*|\.\d+)\s*"\s*,\s*([EW])\s*(\d+)\s*°\s*(\d+)\s*'\s*(\d+\.?\d*|\.\d+)\s*"\s*,\s*([+-]?)\s*0*(\d+\.?\d*|\.\d+))delim");

    static constexpr int latDirIdx = 1;
    static constexpr int latDegIdx = 2;
    static constexpr int latMinIdx = 3;
    static constexpr int latSecIdx = 4;

    static constexpr int lonDirIdx = 5;
    static constexpr int lonDegIdx = 6;
    static constexpr int lonMinIdx = 7;
    static constexpr int lonSecIdx = 8;

    static constexpr int altPosIdx = 8;
    static constexpr int altIdx = 8;

public:

    static QList<FlightPlanWaypoint> readFile(QFile &file);

private:
    static FlightPlanWaypoint readWaypoint();
    FlightplanReader() = delete;
};

#endif   // FLIGHTPLANREADER_H
