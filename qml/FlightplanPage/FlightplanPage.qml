import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Flightplan 1.0

import "FlightplanTable"
import "../CustomControls"

Item {
    id: flightplanPageRoot

    property bool editModeActive: false
    property bool moveModeActive: false
    property int selectedItemIndex: -1

    signal backClicked()

    MouseArea {
        anchors.fill: parent

        onClicked: function() {
            editModeActive = false
            moveModeActive = false
            selectedItemIndex = -1
        }
    }

    GradientButton {
        text: "Back"

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10

        onClicked: flightplanPageRoot.backClicked()
    }

    Text {
        visible: flightplanPageRoot.moveModeActive || waypointInput.insertModeActive

        anchors.left: planTable.left
        anchors.bottom: planTable.top
        anchors.leftMargin: 5
        anchors.bottomMargin: 5

        font.pixelSize: 15

        color: "white"

        text: flightplanPageRoot.moveModeActive ? "Select item after which the selected item will be moved" : "Select item before which the new waypoint will be inserted"
    }

    FlightplanTable {
        id: planTable

        anchors.right: waypointInput.left
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        //width: 600

        editModeActive: flightplanPageRoot.editModeActive
        selectedItemIndex: flightplanPageRoot.selectedItemIndex

        onElementClicked: function(index) {
            if (waypointInput.insertModeActive) {
                waypointInput.insertWaypoint(index);
                return;
            }

            if (flightplanPageRoot.moveModeActive) {
                FlightplanManager.moveWaypoint(flightplanPageRoot.selectedItemIndex, index);
                return;
            }

            flightplanPageRoot.selectedItemIndex = index
        }
    }

    WaypointInput {
        id: waypointInput

        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: planTable.top

        editOrMoveModeActive: flightplanPageRoot.editModeActive || flightplanPageRoot.moveModeActive
    }

    RowLayout {
        anchors.top: planTable.bottom
        anchors.left: planTable.left
        anchors.right: planTable.right
        anchors.topMargin: 5

        spacing: 10

        Button {
            id: clearButton

            visible: flightplanPageRoot.selectedItemIndex === -1

            topInset: 0
            bottomInset: 0

            leftPadding: 5
            bottomPadding: 0
            topPadding: 0
            rightPadding: 5

            text: "Clear All"

            Layout.fillWidth: true
            Layout.preferredWidth: 200

            onClicked: FlightplanManager.clearFlightplan()
        }

        Button {
            id: fromFileButton

            visible: flightplanPageRoot.selectedItemIndex === -1

            topInset: 0
            bottomInset: 0

            leftPadding: 5
            bottomPadding: 0
            topPadding: 0
            rightPadding: 5

            text: "Read From File"

            Layout.fillWidth: true
            Layout.preferredWidth: 200

            onClicked: function() {
                flightplanFileDialog.folder = "file:///" + FlightplanManager.getFileBasePath();
                flightplanFileDialog.open();
            }
        }

        Button {
            id: moveButton

            visible: !flightplanPageRoot.editModeActive && !flightplanPageRoot.moveModeActive && flightplanPageRoot.selectedItemIndex >= 0

            topInset: 0
            bottomInset: 0

            leftPadding: 5
            bottomPadding: 0
            topPadding: 0
            rightPadding: 5

            text: "Move"

            // width: 140
            Layout.fillWidth: true

            onClicked: flightplanPageRoot.moveModeActive = true
        }

        Button {
            id: editButton

            visible: !flightplanPageRoot.editModeActive && !flightplanPageRoot.moveModeActive && flightplanPageRoot.selectedItemIndex >= 0

            topInset: 0
            bottomInset: 0

            leftPadding: 5
            bottomPadding: 0
            topPadding: 0
            rightPadding: 5

            text: "Edit"

            // width: 140
            Layout.fillWidth: true

            onClicked: function() {
                waypointInput.copyWaypointData(flightplanPageRoot.selectedItemIndex);
                flightplanPageRoot.editModeActive = true
            }
        }

        Button {
            id: copyButton

            visible: !flightplanPageRoot.editModeActive && !flightplanPageRoot.moveModeActive && flightplanPageRoot.selectedItemIndex >= 0

            topInset: 0
            bottomInset: 0

            leftPadding: 5
            bottomPadding: 0
            topPadding: 0
            rightPadding: 5

            text: "Copy"

            // width: 140
            Layout.fillWidth: true

            onClicked: function() {
                waypointInput.copyWaypointData(flightplanPageRoot.selectedItemIndex);
            }
        }

        Button {
            id: deleteButton

            visible: !flightplanPageRoot.editModeActive && !flightplanPageRoot.moveModeActive && flightplanPageRoot.selectedItemIndex >= 0

            topInset: 0
            bottomInset: 0

            leftPadding: 5
            bottomPadding: 0
            topPadding: 0
            rightPadding: 5

            text: "Delete"

            // width: 140
            Layout.fillWidth: true

            onClicked: function() {
                FlightplanManager.removeWaypoint(flightplanPageRoot.selectedItemIndex);
                flightplanPageRoot.selectedItemIndex = -1;
            }
        }

        Button {
            id: saveEditButton

            visible: flightplanPageRoot.editModeActive && flightplanPageRoot.selectedItemIndex >= 0

            topInset: 0
            bottomInset: 0

            leftPadding: 5
            bottomPadding: 0
            topPadding: 0
            rightPadding: 5

            text: "Save"

            // width: 140
            Layout.fillWidth: true

            onClicked: function() {
                FlightplanManager.updateWaypoint(flightplanPageRoot.selectedItemIndex, waypointInput.createWaypoint());
                flightplanPageRoot.editModeActive = false;
                flightplanPageRoot.selectedItemIndex = -1;
            }
        }

        Button {
            id: cancelEditButton

            visible: flightplanPageRoot.editModeActive || flightplanPageRoot.moveModeActive && flightplanPageRoot.selectedItemIndex >= 0

            topInset: 0
            bottomInset: 0

            leftPadding: 5
            bottomPadding: 0
            topPadding: 0
            rightPadding: 5

            text: "Cancel"

            // width: 140
            Layout.fillWidth: true

            onClicked: function() {
                flightplanPageRoot.editModeActive = false;
                flightplanPageRoot.moveModeActive = false;
                flightplanPageRoot.selectedItemIndex = -1;
            }
        }
    }

    FlightplanFileDialog {
        id: flightplanFileDialog
    }

    Connections {
        target: FlightplanManager
        function onFlightplanChanged() {
            flightplanPageRoot.editModeActive = false;
            flightplanPageRoot.moveModeActive = false;
            flightplanPageRoot.selectedItemIndex = -1;
            waypointInput.insertModeActive = false;
        }
    }


}
