#ifndef __WAYPOINT_MODEL_HPP__
#define __WAYPOINT_MODEL_HPP__

#include "../FlightPlanWaypoint.hpp"

#include <QAbstractListModel>
#include <vector>
#include <QDebug>

namespace flightplan
{

class WaypointModel : public QAbstractListModel
{
    Q_OBJECT

    struct WaypointCalculated
    {
        double legDistance;
        double totalDistance;
        int bearing;
        // QString iconUrl;
    };

public:

    enum WaypointRoles
    {
        IdentRole = Qt::UserRole + 1,
        TypeIconUrlRole,
        LatitudeRole,
        LongitudeRole,
        AltitudeRole,
        SpeedRole,
        DistanceRole,
        BearingRole,
        MapIconUrlRole
    };

    explicit WaypointModel(QObject *parent = nullptr)
      : QAbstractListModel(parent)
    {}

    void append(const FlightPlanWaypoint &waypoint)
    {
        beginInsertRows(QModelIndex(), d_waypoints.size(), d_waypoints.size());

        if (d_waypoints.empty())
        {
            d_calculatedData.push_back(WaypointCalculated());
        }
        else
        {
            const FlightPlanWaypoint &lastWaypoint = d_waypoints.back();

            const double distance = lastWaypoint.position.distanceTo(waypoint.position) / 1852.0;
            const int bearing = std::lround(lastWaypoint.position.azimuthTo(waypoint.position));

            d_calculatedData.push_back({ distance, d_calculatedData.back().totalDistance + distance, bearing });
        }

        d_waypoints.push_back(waypoint);
        endInsertRows();

        emit flightplanTitleChanged();
    }

    void append(const std::vector<FlightPlanWaypoint> &waypoints)
    {
        if (waypoints.empty())
            return;

        beginInsertRows(QModelIndex(), d_waypoints.size(), d_waypoints.size() + waypoints.size() - 1);

        double totalDistance = d_waypoints.empty() ? 0 : d_calculatedData.back().totalDistance;
        QGeoCoordinate lastPosition = d_waypoints.empty() ? QGeoCoordinate() : d_waypoints.back().position;

        for (auto begin = waypoints.cbegin(), end = waypoints.cend(); begin != end; ++begin)
        {
            // both give 0 if d_waypoints is empty (since lastposition is invalid)
            const double distance = lastPosition.distanceTo(begin->position) / 1852.0;
            const int bearing = std::lround(lastPosition.azimuthTo(begin->position));

            totalDistance += distance;

            d_calculatedData.push_back({ distance, totalDistance, bearing });

            lastPosition = begin->position;
        }

        d_waypoints.insert(d_waypoints.cend(), waypoints.cbegin(), waypoints.cend());

        endInsertRows();

        emit flightplanTitleChanged();
    }

    void insert(size_t pos, const FlightPlanWaypoint &waypoint)
    {
        beginInsertRows(QModelIndex(), pos, pos);

        // will be updated later if needed
        d_calculatedData.insert(d_calculatedData.cbegin() + pos, WaypointCalculated());

        d_waypoints.insert(d_waypoints.cbegin() + pos, waypoint);

        updateCalculatedData(pos);

        endInsertRows();

        emit dataChanged(index(pos), index(d_waypoints.size() - 1));

        if (pos == 0 || pos == d_waypoints.size() - 2)
            emit flightplanTitleChanged();
    }

    void insert(size_t pos, const std::vector<FlightPlanWaypoint> &waypoints)
    {
        if (waypoints.empty())
            return;

        size_t originalSize = d_waypoints.size();

        beginInsertRows(QModelIndex(), pos, pos + waypoints.size() - 1);

        // empty d_waypoints implies pos == 0
        double totalDistance = pos == 0 ? 0 : d_calculatedData[pos - 1].totalDistance;
        QGeoCoordinate lastPosition = pos == 0 ? QGeoCoordinate() : d_waypoints[pos - 1].position;

        // store results in vector so we can use a single insert operation
        std::vector<WaypointCalculated> temp;

        for (auto begin = waypoints.cbegin(), end = waypoints.cend(); begin != end; ++begin)
        {
            // both give 0 if we insert at the start (since lastposition is then invalid)
            const double distance = lastPosition.distanceTo(begin->position) / 1852.0;
            const int bearing = std::lround(lastPosition.azimuthTo(begin->position));

            totalDistance += distance;

            temp.push_back({ distance, totalDistance, bearing });

            lastPosition = begin->position;
        }


        d_calculatedData.insert(d_calculatedData.cbegin() + pos, temp.cbegin(), temp.cend());
        d_waypoints.insert(d_waypoints.cbegin() + pos, waypoints.cbegin(), waypoints.cend());

        updateCalculatedData(pos + waypoints.size());

        endInsertRows();

        emit dataChanged(index(pos + waypoints.size()), index(d_waypoints.size() - 1));

        if (pos == 0 || pos == originalSize)
            emit flightplanTitleChanged();
    }

    void erase(size_t pos)
    {
        beginRemoveRows(QModelIndex(), pos, pos);

        d_calculatedData.erase(d_calculatedData.cbegin() + pos);
        d_waypoints.erase(d_waypoints.cbegin() + pos);

        // pos is now the index to the first element after the erased data
        updateCalculatedData(pos);

        endRemoveRows();

        emit dataChanged(index(pos), index(d_waypoints.size() - 1));

        if (pos == 0 || pos == d_waypoints.size())
            emit flightplanTitleChanged();
    }

    void move(size_t from, size_t to)
    {
        if (from == to || from == to + 1)
            return;

        size_t start = from < to ? from : to;
        size_t end = from > to ? from : to;

        beginMoveRows(QModelIndex(), from, from, QModelIndex(), to + 1);

        if (from > to)
            to += 1;

        WaypointCalculated calcTemp = d_calculatedData[from];
        FlightPlanWaypoint wpTemp = d_waypoints[from];

        d_calculatedData.erase(d_calculatedData.cbegin() + from);
        d_waypoints.erase(d_waypoints.cbegin() + from);


        d_calculatedData.insert(d_calculatedData.cbegin() + to, calcTemp);
        d_waypoints.insert(d_waypoints.cbegin() + to, wpTemp);

        updateCalculatedData(start);

        endMoveRows();

        emit dataChanged(index(start), index(d_waypoints.size() - 1));

        if (start == 0 || end == d_waypoints.size() - 1)
            emit flightplanTitleChanged();
    }

    void erase(size_t first, size_t last)
    {
        if (first >= last)
            return;

        size_t originalSize = d_waypoints.size();

        beginRemoveRows(QModelIndex(), first, last - 1);

        d_calculatedData.erase(d_calculatedData.cbegin() + first, d_calculatedData.cbegin() + last);
        d_waypoints.erase(d_waypoints.cbegin() + first, d_waypoints.cbegin() + last);

        // first is now the index to the first element after the erased data
        updateCalculatedData(first);

        endRemoveRows();

        emit dataChanged(index(first), index(d_waypoints.size() - 1));

        if (first == 0 || last == originalSize)
            emit flightplanTitleChanged();
    }

    void set(size_t pos, const FlightPlanWaypoint &waypoint)
    {
        d_waypoints[pos] = waypoint;

        updateCalculatedData(pos);

        emit dataChanged(index(pos), index(d_waypoints.size() - 1));

        if (pos == 0 || pos == d_waypoints.size() - 1)
            emit flightplanTitleChanged();
    }

    void overwrite(const std::vector<FlightPlanWaypoint> &waypoints)
    {
        if (waypoints.empty())
            return clear();

        beginResetModel();

        d_waypoints = waypoints;

        d_calculatedData = { WaypointCalculated() };

        double totalDistance = 0;
        QGeoCoordinate lastPosition = d_waypoints.front().position;

        for (auto begin = d_waypoints.cbegin() + 1, end = d_waypoints.cend(); begin != end; ++begin)
        {
            // both give 0 if d_waypoints is empty (since lastposition is invalid)
            const double distance = lastPosition.distanceTo(begin->position) / 1852.0;
            const int bearing = std::lround(lastPosition.azimuthTo(begin->position));

            totalDistance += distance;

            d_calculatedData.push_back({ distance, totalDistance, bearing });

            lastPosition = begin->position;
        }

        endResetModel();

        emit flightplanTitleChanged();
    }

    Q_INVOKABLE QString getTitle()
    {
        if (d_waypoints.size() == 0)
            return "____/____";

        if (d_waypoints.size() == 1)
            return d_waypoints.front().ident + "/____";

        return d_waypoints.front().ident + "/" + d_waypoints.back().ident;
    }

    void clear()
    {
        beginRemoveRows(QModelIndex(), 0, d_waypoints.size() - 1);
        d_waypoints.clear();
        d_calculatedData.clear();
        endRemoveRows();

        emit flightplanTitleChanged();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        Q_UNUSED(parent);
        return d_waypoints.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    const std::vector<FlightPlanWaypoint> &data() const
    {
        return d_waypoints;
    }

    QList<FlightPlanWaypoint> dataAsList() const
    {
        return QList(d_waypoints.cbegin(), d_waypoints.cend());
    }

    const FlightPlanWaypoint &at(size_t pos) const
    {
        return d_waypoints[pos];
    }

signals:

    void flightplanTitleChanged();

protected:

    QHash<int, QByteArray> roleNames() const
    {
        return { { IdentRole, "ident" },
                 { TypeIconUrlRole, "wpTypeUrl" },
                 { LatitudeRole, "lat" },
                 { LongitudeRole, "lon" },
                 { AltitudeRole, "altTypeText" },
                 { SpeedRole, "speed" },
                 { DistanceRole, "dist" },
                 { BearingRole, "dtk" },
                 { MapIconUrlRole, "mapIconUrl" } };
    }

private:

    void updateCalculatedData(size_t pos)
    {
        if (pos >= d_waypoints.size())
            return;

        double totalDistance = pos == 0 ? 0 : d_calculatedData[pos - 1].totalDistance;
        QGeoCoordinate lastPosition = pos == 0 ? QGeoCoordinate() : d_waypoints[pos - 1].position;

        // update distances and bearings for all waypoints starting at pos
        auto calcBegin = d_calculatedData.begin() + pos;

        for (auto begin = d_waypoints.cbegin() + pos, end = d_waypoints.cend(); begin != end; ++begin, ++calcBegin)
        {
            calcBegin->legDistance = lastPosition.distanceTo(begin->position) / 1852.0;
            totalDistance += calcBegin->legDistance;
            calcBegin->totalDistance = totalDistance;
            calcBegin->bearing = std::lround(lastPosition.azimuthTo(begin->position));

            lastPosition = begin->position;
        }
    }

    std::vector<FlightPlanWaypoint> d_waypoints;
    std::vector<WaypointCalculated> d_calculatedData;
};

}  // namespace flightplan

#endif  // __WAYPOINT_MODEL_HPP__