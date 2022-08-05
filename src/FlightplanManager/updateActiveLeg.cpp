#include "FlightplanManager.hpp"

#include <cmath>
#include <numbers>

void FlightplanManager::updateActiveLeg(double latitude, double longitude)
{
    d_userPosition = QGeoCoordinate(latitude, longitude);

    if (d_wpModel.rowCount() == 0)
    {
        if (d_activeLegIdx != -1)
        {
            d_activeLegIdx = -1;
            emit activeLegIdxChanged(-1);
        }

        return;
    }

    std::vector<FlightPlanWaypoint> waypoints = d_wpModel.data();
    QGeoCoordinate prevCoord = waypoints.front().position;

    double deltaStartUser = prevCoord.distanceTo(d_userPosition) / (6378.137 / 1852.0);
    double thetaStartUser = prevCoord.azimuthTo(d_userPosition);
    double thetaStartEnd = 0;

    double shortestDist = deltaStartUser;
    int32_t shortestDistIdx = -1;

    // distances calculated according to
    // http://www.movable-type.co.uk/scripts/latlong.html
    // and
    // https://stackoverflow.com/questions/32771458/distance-from-lat-lng-point-to-minor-arc-segment

    for (int32_t idx = 1; idx < waypoints.size(); ++idx)
    {
        QGeoCoordinate nextCoord = waypoints.at(idx).position;

        thetaStartEnd = prevCoord.azimuthTo(nextCoord);

        double relativeBearing = thetaStartUser - thetaStartEnd;

        if (relativeBearing < 0.0)
            relativeBearing += 360.0;

        if (relativeBearing > 180.0)
            relativeBearing = 360.0 - relativeBearing;

        if (relativeBearing > 90)  // are we in front of the start of the segment?
        {
            if (deltaStartUser < shortestDist)
            {
                shortestDist = deltaStartUser;
                shortestDistIdx = idx;
            }

            // update coordinate
            prevCoord = nextCoord;

            deltaStartUser = prevCoord.distanceTo(d_userPosition) / (6378.137 / 1852.0);
            thetaStartUser = prevCoord.azimuthTo(d_userPosition);
        }
        else
        {
            double crossTrack = std::asin(std::sin(deltaStartUser)
                                          * std::sin((thetaStartUser - thetaStartEnd) * std::numbers::pi / 180.0))
              * (6378.137 / 1852.0);
            double segmentLength = prevCoord.distanceTo(nextCoord) / (6378.137 / 1852.0);

            // update coordinate
            prevCoord = nextCoord;

            deltaStartUser = prevCoord.distanceTo(d_userPosition) / (6378.137 / 1852.0);
            thetaStartUser = prevCoord.azimuthTo(d_userPosition);

            if (crossTrack > segmentLength)  // are we behind the end of the segment?
            {
                if (deltaStartUser < shortestDist)
                {
                    shortestDist = deltaStartUser;
                    shortestDistIdx = idx + 1;  // closest to end must mean we are at the start of the next segment
                }
            }
            else if (crossTrack < shortestDist)
            {
                shortestDist = crossTrack;
                shortestDistIdx = idx;
            }
        }
    }

    if (d_activeLegIdx != shortestDistIdx)
    {
        d_activeLegIdx = shortestDistIdx;
        emit activeLegIdxChanged(d_activeLegIdx);
    }
}
