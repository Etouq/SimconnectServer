#ifndef __QML_ENUMS_HPP__
#define __QML_ENUMS_HPP__

#include "FlightplanManager/FlightPlanWaypoint.hpp"

#include <QObject>


class QmlWaypointTypeClass
{
    Q_GADGET

public:

    enum class Value
    {
        NONE = static_cast<int>(WaypointType::NONE),
        AIRPORT = static_cast<int>(WaypointType::AIRPORT),
        INTERSECTION = static_cast<int>(WaypointType::INTERSECTION),
        VOR = static_cast<int>(WaypointType::VOR),
        NDB = static_cast<int>(WaypointType::NDB),
        USER = static_cast<int>(WaypointType::USER),
        ATC = static_cast<int>(WaypointType::ATC)
    };
    Q_ENUM(Value)

private:

    explicit QmlWaypointTypeClass();
};

typedef QmlWaypointTypeClass::Value QmlWaypointType;

class QmlWpAltitudeTypeClass
{
    Q_GADGET

public:

    enum class Value
    {
        NONE = static_cast<int>(WpAltitudeType::NONE),
        AT = static_cast<int>(WpAltitudeType::AT),
        AT_OR_BELOW = static_cast<int>(WpAltitudeType::AT_OR_BELOW),
        AT_OR_ABOVE = static_cast<int>(WpAltitudeType::AT_OR_ABOVE),
        BETWEEN = static_cast<int>(WpAltitudeType::BETWEEN)
    };
    Q_ENUM(Value)

private:

    explicit QmlWpAltitudeTypeClass();
};

typedef QmlWpAltitudeTypeClass::Value QmlWpAltitudeType;

namespace io::network
{

class ConnectionStateClass
{
    Q_GADGET

public:

    enum Value
    {
        DISCONNECTED,
        CONNECTED,
        CONNECTING,
        DISCONNECTING
    };
    Q_ENUM(Value)

private:

    explicit ConnectionStateClass()
    {}
};

typedef ConnectionStateClass::Value ConnectionState;

}  // namespace io::network

#endif  // __QML_ENUMS_HPP__
