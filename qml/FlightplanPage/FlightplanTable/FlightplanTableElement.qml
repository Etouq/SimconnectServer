import QtQuick 2.15
import QtQuick.Controls 2.15

import TypeEnums 1.0
import Flightplan 1.0

import "private"

ListView {
    id: flightplanTableView

    property bool editModeActive: false
    property int selectedItemIndex

    property int showCount: 6


    signal elementClicked(int index)

    clip: true

    width: contentWidth + 20
    height: 60 + (flightplanTableView.showCount - 1) * 59
    contentWidth: contentItem.childrenRect.width

    spacing: -1
    reuseItems: true

    model: flightplanModel

    boundsBehavior: Flickable.StopAtBounds

    ListModel {
        id: flightplanModel
    }

    Component.onCompleted: {
        flightplanTableView.fillFlightplan()
        //console.log(width, contentWidth, childrenRect.width, contentItem.width, contentItem.childrenRect.width)
        // Qt.callLater(getData);
    }

    function getData() {
        console.log(width, contentWidth, childrenRect, contentItem.childrenRect)
    }

    Connections {
        target: FlightplanManager
        function onFlightplanChanged() {
            const viewIndex = flightplanTableView.indexAt(5, flightplanTableView.contentY);
            flightplanTableView.fillFlightplan();
            flightplanTableView.positionViewAtIndex(viewIndex, ListView.Beginning);
        }
    }

    function fillFlightplan() {
        flightplanModel.clear();

        for (let idx = 0; idx < FlightplanManager.waypointCount(); idx++) {
            const waypoint = FlightplanManager.getWaypoint(idx)
            flightplanModel.append({
                "ident": waypoint.ident,
                "wpTypeUrl": flightplanTableView.getWpTypeUrl(waypoint.waypointType),
                "altTypeText": flightplanTableView.getAltString(waypoint.altitudeType, waypoint.alt1, waypoint.alt2),
                "dtk": FlightplanManager.getLegBearing(idx),
                "dist": FlightplanManager.getLegDistanceTo(idx),
                "totDist": FlightplanManager.getCumulativeDistance(idx),
                "speed": waypoint.speed <= 0 ? "" : (waypoint.speed + "KT")
            });
        }
    }

    function getWpTypeUrl(typeId) {
        switch (typeId) {
            case WaypointType.AIRPORT:
                return "qrc:/miscImages/ICON_MAP_AIRPORT.png";
            case WaypointType.INTERSECTION:
                return "qrc:/miscImages/ICON_MAP_INT.png";
            case WaypointType.NDB:
                return "qrc:/miscImages/ICON_MAP_NDB.png";
            case WaypointType.USER:
                return "qrc:/miscImages/ICON_MAP_USER.png";
            case WaypointType.VOR:
                return "qrc:/miscImages/ICON_MAP_VOR_2.png";
            case WaypointType.ATC:
            case WaypointType.NONE:
            default:
                return "qrc:/miscImages/ICON_MAP_USER.png";
        }
    }

    function getAltString(altType, alt1, alt2) {
        switch (altType) {
            case WpAltitudeType.NONE:
                return " _____FT";
            case WpAltitudeType.AT:
                return " " + alt1.toString() + "FT";
            case WpAltitudeType.AT_OR_BELOW:
                return "B" + alt1.toString() + "FT";
            case WpAltitudeType.AT_OR_ABOVE:
                return "A" + alt1.toString() + "FT";
            case WpAltitudeType.BETWEEN:
                return "A" + alt1.toString() + "FT\nB" + alt2.toString() + "FT";
            default:
                return " _____FT";
        }
    }

    ScrollBar.vertical: ScrollBar {
        anchors.right: flightplanTableView.right
        anchors.rightMargin: 5
        policy: ScrollBar.AlwaysOn
        width: 10

        contentItem: Rectangle {
            implicitWidth: 10
            implicitHeight: flightplanTableView.height * 100 / (95 * flightplanTableView.model.count)
            color: "white"
        }

    }

    //snapMode: ListView.SnapToItem

    delegate: TableRow {

        isSelectedItem: flightplanTableView.selectedItemIndex === index

        MouseArea {
            anchors.fill: parent

            cursorShape: flightplanTableView.editModeActive ? Qt.ArrowCursor : Qt.PointingHandCursor
            acceptedButtons: flightplanTableView.editModeActive ? Qt.NoButton : Qt.LeftButton

            onClicked: function() {
                flightplanTableView.elementClicked(parent.index)
            }
        }
    }


}
