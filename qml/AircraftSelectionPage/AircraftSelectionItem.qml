import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import SimconnectServer 1.0

Rectangle {
    id: thumbnailRoot

    required property string key
    readonly property bool isCurrent: AircraftManager.isCurrentAircraft(key)

    readonly property real minHeight: aircraftThumb.height + 7.5 + aircraftTitle.height + 1

    color: clickRegion.containsPress ? "#0093d0" : "white"//"#1A1D21"

    signal thumbnailClicked()

    MouseArea {
        id: clickRegion
        anchors.fill: parent

        cursorShape: Qt.PointingHandCursor

        onClicked: function() {
            AircraftManager.selectAircraft(thumbnailRoot.key);
            thumbnailRoot.thumbnailClicked();
        }
    }

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0; color: "#0093d0" }
            GradientStop { position: 0.6; color: "#000093d0" }
        }
    }

    Loader {
        anchors.fill: parent
        active: thumbnailRoot.isCurrent
        sourceComponent: Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: Material.primary
            border.width: 2
        }
    }

    Image {
        id: aircraftThumb

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 7.5
        anchors.rightMargin: 7.5
        anchors.bottomMargin: 7.5

        height: width * 216 / 600
        sourceSize.width: 600
        sourceSize.height: 216

        fillMode: Image.PreserveAspectFit

        asynchronous: true
        source: AircraftManager.getImagePath(thumbnailRoot.key)
    }

    Text {
        id: aircraftTitle
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: (1 + aircraftThumb.y) / 2

        width: parent.width
        horizontalAlignment: Text.AlignHCenter

        font.pixelSize: 18
        font.family: "Roboto Mono"
        font.bold: true

        color: thumbnailRoot.isCurrent ? Material.primary : "white"

        wrapMode: Text.WordWrap
        text: AircraftManager.getName(thumbnailRoot.key)
    }
}

