import QtQuick 2.15
import QtQuick.Controls 2.15

import Flightplan 1.0


Rectangle {
    id: tableRoot

    width: flightplanTableView.width + 5//913
    height: flightplanTableView.height + headerRow.height + 8//width * 525 / 913

    color: "black"
    border.color: "white"

    border.width: 3

    property alias editModeActive: flightplanTableView.editModeActive
    property alias selectedItemIndex: flightplanTableView.selectedItemIndex

    signal elementClicked(int index)

    FontMetrics {
        id: fontMetrics
        font.family: "Roboto Mono"
        font.bold: true
        font.pixelSize: 20
    }

    Row {
        id: headerRow

        readonly property real cellPadding: 4
        readonly property real borderWidth: 1

        anchors.left: flightplanTableView.left
        anchors.leftMargin: headerRow.borderWidth + headerRow.cellPadding + 6
        anchors.bottom: flightplanTableView.top
        anchors.bottomMargin: 3
        height: 30

        spacing: headerRow.borderWidth + headerRow.cellPadding * 2 + 12

        Text {
            id: fpTitle
            width: 20 + (60 - 2 * (headerRow.cellPadding + headerRow.borderWidth)) + fontMetrics.boundingRect("A".repeat(9)).width - 6 - headerRow.cellPadding
            height: 30

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.family: "Roboto Mono"
            font.bold: true
            font.pixelSize: 20

            color: "white"
            text: FlightplanManager.getTitle()
        }

        Text {
            width: fontMetrics.boundingRect("A00000FT").width
            height: 30

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.family: "Roboto Mono"
            font.bold: true
            font.pixelSize: 20

            color: "white"
            text: "ALT"
        }

        Text {
            width: fontMetrics.boundingRect("000°").width
            height: 30

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.family: "Roboto Mono"
            font.bold: true
            font.pixelSize: 20

            color: "white"
            text: "DTK"
        }

        Text {
            width: fontMetrics.boundingRect("00.0NM").width
            height: 30

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.family: "Roboto Mono"
            font.bold: true
            font.pixelSize: 20

            color: "white"
            text: "DIST"
        }

        Text {
            width: fontMetrics.boundingRect("___KT").width
            height: 30

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.family: "Roboto Mono"
            font.bold: true
            font.pixelSize: 20

            color: "white"
            text: "SPD"
        }
    }

    FlightplanTableElement {
        id: flightplanTableView
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2

        onElementClicked: function(index) {
            tableRoot.elementClicked(index);
        }
    }

    Rectangle {
        anchors.left: flightplanTableView.left
        anchors.right: parent.right
        anchors.top: flightplanTableView.top
        height: 1

        color: "white"
    }

    Connections {
        target: FlightplanManager
        function onFlightplanChanged() {
            fpTitle.text = FlightplanManager.getTitle();
        }
    }


}
