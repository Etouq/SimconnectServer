#ifndef __FLIGHTPLAN_MANAGER_HPP__
#define __FLIGHTPLAN_MANAGER_HPP__

#include "FlightPlanWaypoint.hpp"
#include "QmlWaypoint.hpp"

#include <QList>
#include <QObject>
#include <QRegularExpression>
#include "WaypointModel/WaypointModel.hpp"

class QFile;
class QXmlStreamReader;
class FdcSocket;

class FlightplanManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int activeLegIdx READ activeLegIdx NOTIFY activeLegIdxChanged)

public:

    // checks if we have an existing flightplan. If we do, read and store it
    FlightplanManager(QObject *parent = nullptr)
      : QObject(parent)
    {
        readFromJson();
    }

    flightplan::WaypointModel *getModel()
    {
        return &d_wpModel;
    }

    Q_INVOKABLE void readFromFile(const QString &url);

    int activeLegIdx() const
    {
        return d_activeLegIdx;
    }

    Q_INVOKABLE QString getFileBasePath() const;

    Q_INVOKABLE QmlWaypoint *waypoint()
    {
        return new QmlWaypoint();
    }

    Q_INVOKABLE QmlWaypoint *getWaypoint(int index)
    {
        return new QmlWaypoint(d_wpModel.at(index));
    }

    Q_INVOKABLE void insertWaypoint(int index, QmlWaypoint *waypoint)
    {
        d_wpModel.insert(index,
                           { .position = waypoint->d_position,
                             .alt1 = waypoint->d_alt1,
                             .alt2 = waypoint->d_alt2,
                             .ident = waypoint->d_ident,
                             .wpType = waypoint->d_wpType,
                             .altType = waypoint->d_altType });

        emit flightplanChanged(d_wpModel.data());
    }

    Q_INVOKABLE void updateWaypoint(int index, QmlWaypoint *waypoint)
    {
        d_wpModel.set(index,
                           { .position = waypoint->d_position,
                               .alt1 = waypoint->d_alt1,
                               .alt2 = waypoint->d_alt2,
                               .ident = waypoint->d_ident,
                               .wpType = waypoint->d_wpType,
                               .altType = waypoint->d_altType });

        emit flightplanChanged(d_wpModel.data());
    }

    Q_INVOKABLE void moveWaypoint(int fromIndex, int toIndex)
    {
        d_wpModel.move(fromIndex, toIndex);

        emit flightplanChanged(d_wpModel.data());
    }

    Q_INVOKABLE void appendWaypoint(QmlWaypoint *waypoint)
    {
        d_wpModel.append({ .position = waypoint->d_position,
                             .alt1 = waypoint->d_alt1,
                             .alt2 = waypoint->d_alt2,
                             .ident = waypoint->d_ident,
                             .wpType = waypoint->d_wpType,
                             .altType = waypoint->d_altType });

        emit flightplanChanged(d_wpModel.data());
    }

    Q_INVOKABLE void removeWaypoint(int index)
    {
        d_wpModel.erase(index);

        emit flightplanChanged(d_wpModel.data());
    }

    Q_INVOKABLE void clearFlightplan()
    {
        d_wpModel.clear();

        emit flightplanChanged(d_wpModel.data());
    }

    const std::vector<FlightPlanWaypoint> &getFlightplan() const
    {
        return d_wpModel.data();
    }

signals:

    void flightplanChanged(const std::vector<FlightPlanWaypoint> &newPlan);

    void activeLegIdxChanged(int32_t newIdx);

public slots:

    void updateActiveLeg(double latitude, double longitude);

    void sendInitData(FdcSocket *newSocket);

    // called when application is about to close, stores current flightplan in json file for readout on next startup
    void storeFlightplan();

private:

    void readFromJson();

    FlightPlanWaypoint readNextWaypoint(QXmlStreamReader &xml);

    std::pair<QGeoCoordinate, double> parsePosition(const QString &position);

    flightplan::WaypointModel d_wpModel;

    int32_t d_activeLegIdx = -1;

    static const QRegularExpression positionExpr;

    QGeoCoordinate d_userPosition;
};

#endif  // __FLIGHTPLAN_MANAGER_HPP__