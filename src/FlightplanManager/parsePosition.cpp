#include "FlightplanManager.hpp"

const QRegularExpression FlightplanManager::positionExpr = QRegularExpression(
      R"delim(([NS])(\d+)°\s*(\d+)'\s*(\d+(?:\.\d+)?)"\s*,\s*([EW])(\d+)°\s*(\d+)'\s*(\d+(?:\.\d+)?)"\s*,\s*([+-]?\d+(?:\.\d+)?))delim");

std::pair<QGeoCoordinate, double> FlightplanManager::parsePosition(const QString &position)
    {
        if (QRegularExpressionMatch match = positionExpr.match(position); match.hasMatch())
        {
            bool northLat = !match.captured(1).isNull() && match.captured(1) != "S";
            double latDeg = match.captured(2).toDouble();
            double latMin = match.captured(3).toDouble();
            double latSec = match.captured(4).toDouble();

            bool eastLon =!match.captured(5).isNull() && match.captured(5) != "W";
            double lonDeg = match.captured(6).toDouble();
            double lonMin = match.captured(7).toDouble();
            double lonSec = match.captured(8).toDouble();

            double lat = (latDeg + latMin / 60.0 + latSec / 3600.0) * (northLat ? 1.0 : -1.0);
            double lon = (lonDeg + lonMin / 60.0 + lonSec / 3600.0) * (eastLon ? 1.0 : -1.0);

            return std::make_pair(QGeoCoordinate(lat, lon), QString(match.captured(9)).toDouble());
        }

        return std::make_pair(QGeoCoordinate(), 0);
    }