#ifndef __QML_WAYPOINT_HPP__
#define __QML_WAYPOINT_HPP__

#include "FlightPlanWaypoint.hpp"
#include "common/QmlEnums.hpp"

#include <QGeoCoordinate>
#include <QObject>


class QmlWaypoint : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QGeoCoordinate position MEMBER d_position NOTIFY positionChanged)
    Q_PROPERTY(int alt1 MEMBER d_alt1 NOTIFY alt1Changed)
    Q_PROPERTY(int alt2 MEMBER d_alt2 NOTIFY alt2Changed)
    Q_PROPERTY(QString ident MEMBER d_ident NOTIFY identChanged)
    Q_PROPERTY(QmlWaypointTypeClass::Value waypointType READ waypointType WRITE setWaypointType NOTIFY waypointTypeChanged)
    Q_PROPERTY(QmlWpAltitudeTypeClass::Value altitudeType READ altitudeType WRITE setAltitudeType NOTIFY altitudeTypeChanged)
    Q_PROPERTY(int speed MEMBER d_speed NOTIFY speedChanged)

public:

    explicit QmlWaypoint(QObject *parent = nullptr)
      : QObject(parent)
    {}

    QmlWaypoint(const FlightPlanWaypoint &waypoint, QObject *parent = nullptr)
      : QObject(parent),
        d_position(waypoint.position),
        d_alt1(waypoint.alt1),
        d_alt2(waypoint.alt2),
        d_ident(waypoint.ident),
        d_wpType(waypoint.wpType),
        d_altType(waypoint.altType),
        d_speed(waypoint.speed)
    {}

    QmlWaypointType waypointType() const
    {
        return static_cast<QmlWaypointType>(d_wpType);
    }

    QmlWpAltitudeType altitudeType() const
    {
        return static_cast<QmlWpAltitudeType>(d_altType);
    }

    void setWaypointType(QmlWaypointType type)
    {
        d_wpType = static_cast<WaypointType>(type);
        emit waypointTypeChanged();
    }

    void setAltitudeType(QmlWpAltitudeType type)
    {
        d_altType = static_cast<WpAltitudeType>(type);
        emit altitudeTypeChanged();
    }

signals:

    void positionChanged();
    void alt1Changed();
    void alt2Changed();
    void identChanged();
    void speedChanged();

    void waypointTypeChanged();
    void altitudeTypeChanged();

private:

    QGeoCoordinate d_position = QGeoCoordinate(0, 0);
    int d_alt1 = 0;
    int d_alt2 = 0;
    QString d_ident = "";
    WaypointType d_wpType = WaypointType::NONE;
    WpAltitudeType d_altType = WpAltitudeType::NONE;
    int d_speed = 0;

    friend class FlightplanManager;
};

#endif  // __QML_WAYPOINT_HPP__