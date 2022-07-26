#ifndef __FLIGHTPLAN_MANAGER_HPP__
#define __FLIGHTPLAN_MANAGER_HPP__

#include "FlightPlanWaypoint.hpp"
#include "QmlWaypoint.hpp"

#include <QList>
#include <QObject>
#include <QQmlEngine>
#include <QRegularExpression>

class QFile;
class QXmlStreamReader;

class FlightplanManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int activeLegIdx READ activeLegIdx NOTIFY activeLegIdxChanged)


public:

    FlightplanManager(QObject *parent = nullptr)
      : QObject(parent)
    {
        qRegisterMetaType<QmlWaypoint *>("QmlWaypoint*");
        qmlRegisterUncreatableType<QmlWaypoint>("Flightplan", 1, 0, "Waypoint", "Bad Boy");
    }

    Q_INVOKABLE void readFromFile(const QString &url);

    int activeLegIdx() const
    {
        return d_activeLegIdx;
    }

    Q_INVOKABLE QString getFileBasePath() const;

    Q_INVOKABLE QString getLegDistanceTo(int idx) const
    {
        if (idx == 0)
            return "";

        double distance = d_waypoints[idx - 1].position.distanceTo(d_waypoints[idx].position) / 1852.0;
        return QString::number(distance, 'f', distance < 100 ? 1 : 0) + "NM";
    }

    Q_INVOKABLE QString getCumulativeDistance(int idx) const
    {
        if (idx == 0)
            return "";
        double totalDist = 0.0;
        for (int i = 1; i <= idx; i++)
            totalDist += d_waypoints[i - 1].position.distanceTo(d_waypoints[i].position);

        totalDist /= 1852.0;
        return QString::number(totalDist, 'f', totalDist < 100 ? 1 : 0) + "NM";
    }

    Q_INVOKABLE QString getLegBearing(int idx) const
    {
        if (idx == 0)
            return "";
        return QString::number(std::lround(d_waypoints[idx - 1].position.azimuthTo(d_waypoints[idx].position))) + "°";
    }

    Q_INVOKABLE QString getTitle()
    {
        if (d_waypoints.size() == 0)
            return "____/____";

        if (d_waypoints.size() == 1)
            return d_waypoints.constFirst().ident + "/____";

        return d_waypoints.constFirst().ident + "/" + d_waypoints.constLast().ident;
    }

    Q_INVOKABLE QmlWaypoint *waypoint()
    {
        return new QmlWaypoint();
    }

    Q_INVOKABLE QmlWaypoint *getWaypoint(int index)
    {
        return new QmlWaypoint(d_waypoints.at(index));
    }

    Q_INVOKABLE int waypointCount() const
    {
        return d_waypoints.size();
    }

    Q_INVOKABLE void insertWaypoint(int index, QmlWaypoint *waypoint)
    {
        d_waypoints.insert(index,
                           { .position = waypoint->d_position,
                             .alt1 = waypoint->d_alt1,
                             .alt2 = waypoint->d_alt2,
                             .ident = waypoint->d_ident,
                             .wpType = waypoint->d_wpType,
                             .altType = waypoint->d_altType });

        emit flightplanChanged();
    }

    Q_INVOKABLE void updateWaypoint(int index, QmlWaypoint *waypoint)
    {
        d_waypoints[index] = { .position = waypoint->d_position,
                               .alt1 = waypoint->d_alt1,
                               .alt2 = waypoint->d_alt2,
                               .ident = waypoint->d_ident,
                               .wpType = waypoint->d_wpType,
                               .altType = waypoint->d_altType };

        emit flightplanChanged();
    }

    Q_INVOKABLE void moveWaypoint(int fromIndex, int toIndex)
    {
        d_waypoints.move(fromIndex, toIndex);

        emit flightplanChanged();
    }

    Q_INVOKABLE void appendWaypoint(QmlWaypoint *waypoint)
    {
        insertWaypoint(d_waypoints.size(), waypoint);
    }

    Q_INVOKABLE void removeWaypoint(int index)
    {
        d_waypoints.removeAt(index);

        emit flightplanChanged();
    }

    Q_INVOKABLE void clearFlightplan()
    {
        d_waypoints.clear();

        emit flightplanChanged();
    }

    const QList<FlightPlanWaypoint> &getFlightplan() const
    {
        return d_waypoints;
    }

signals:

    void flightplanChanged();

    void activeLegIdxChanged();

private:

    void readNextWaypoint(QXmlStreamReader &xml);

    std::pair<QGeoCoordinate, double> parsePosition(const QString &position);

    QList<FlightPlanWaypoint> d_waypoints;

    int d_activeLegIdx = 3;

    static const QRegularExpression positionExpr;
};

#endif  // __FLIGHTPLAN_MANAGER_HPP__