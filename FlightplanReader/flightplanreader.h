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

    QXmlStreamReader flightPlanXml;

    const QRegularExpression llaRegExp = QRegularExpression(
      R"delim(([NS])\s*(\d+)\s*°\s*(\d+)\s*'\s*(\d+\.?\d*|\.\d+)\s*"\s*,\s*([EW])\s*(\d+)\s*°\s*(\d+)\s*'\s*(\d+\.?\d*|\.\d+)\s*"\s*,\s*([+-]?)\s*0*(\d+\.?\d*|\.\d+))delim");

public:
    FlightplanReader();

    QList<FlightPlanWaypoint> readFlightPlanFile(QFile &file);

private:
    FlightPlanWaypoint readWaypoint();
};

#endif   // FLIGHTPLANREADER_H
