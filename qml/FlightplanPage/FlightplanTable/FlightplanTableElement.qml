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
    contentWidth: flightplanTableView.identCellWidth + flightplanTableView.altCellWidth + flightplanTableView.dtkCellWidth + flightplanTableView.distCellWidth + flightplanTableView.speedCellWidth + 6 * flightplanTableView.borderWidth + 10 * flightplanTableView.cellPadding

    spacing: -1
    reuseItems: true

    model: WaypointModel

    boundsBehavior: Flickable.StopAtBounds

    FontMetrics {
        id: fontMetrics
        font.family: "Roboto Mono"
        font.bold: true
        font.pixelSize: 20
    }

    readonly property real cellPadding: 4
    readonly property real borderWidth: 1
    readonly property real contentHeight: 60 - 2 * (flightplanTableView.cellPadding + flightplanTableView.borderWidth)
    readonly property real identCellWidth: 20 + flightplanTableView.contentHeight + fontMetrics.boundingRect("A".repeat(9)).width + 6 - flightplanTableView.cellPadding
    readonly property real altCellWidth: fontMetrics.boundingRect("A00000FT").width + 12
    readonly property real dtkCellWidth: fontMetrics.boundingRect("000°").width + 12
    readonly property real distCellWidth: fontMetrics.boundingRect("00.0NM").width + 12
    readonly property real speedCellWidth: fontMetrics.boundingRect("___KT").width + 12

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

    delegate: TableRow {

        identCellWidth: flightplanTableView.identCellWidth
        altCellWidth: flightplanTableView.altCellWidth
        dtkCellWidth: flightplanTableView.dtkCellWidth
        distCellWidth: flightplanTableView.distCellWidth
        speedCellWidth: flightplanTableView.speedCellWidth

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
