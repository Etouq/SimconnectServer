import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml 2.15

import SimconnectServer 1.0

import "CustomControls"

Item {
    id: homePage

    signal selectAircraftClicked()
    signal activateFlightplanPage()

    SimStateDisplay {
        id: simStateDisplay

        y: 20

        anchors.left: parent.left
        anchors.right: clientContainer.right
        anchors.leftMargin: 45
        anchors.rightMargin: 5
    }

    Column {
        id: navigationButtons

        y: 20
        width: 150
        anchors.right: parent.right
        anchors.rightMargin: 40

        spacing: 20

        GradientButton {
            text: "Select\nAircraft"
            width: 150
            height: 63
            onClicked: homePage.selectAircraftClicked()
        }

        GradientButton {
            text: "Flightplan"
            width: 150
            height: 63
            onClicked: homePage.activateFlightplanPage()
        }
    }

    Text {
        id: clientTitle
        anchors.top: simStateDisplay.bottom
        anchors.left: clientContainer.left
        anchors.leftMargin: 5
        anchors.topMargin: 10

        font.family: "Roboto"
        font.pixelSize: 20
        font.bold: true

        color: "white"
        text: "Client Connections"
    }

    Rectangle {
        id: clientContainer

        anchors.left: parent.left
        anchors.top: clientTitle.bottom
        anchors.right: navigationButtons.left
        anchors.bottom: parent.bottom

        anchors.leftMargin: 40
        anchors.topMargin: 5
        anchors.rightMargin: 30
        anchors.bottomMargin: 20

        color: "transparent"
        border.color: "white"
        border.width: 1

        ListView {
            id: clientView

            anchors.fill: parent
            anchors.margins: 10

            clip: true

            model: clientModel

            delegate: RowLayout {
                required property string name
                required property string address

                height: childrenRect.height
                width: clientView.width

                Text {
                    id: nameText

                    Layout.minimumWidth: implicitWidth
                    Layout.fillWidth: true

                    leftPadding: 5
                    rightPadding: 5

                    elide: Text.ElideRight

                    font.family: "Roboto"
                    font.pixelSize: 15
                    font.bold: true

                    color: "white"

                    text: name
                }

                Text {
                    id: addressText

                    Layout.maximumWidth: 326
                    Layout.preferredWidth: 326
                    Layout.fillWidth: true

                    leftPadding: 5
                    rightPadding: 5

                    font.family: "Roboto"
                    font.pixelSize: 15
                    font.bold: true

                    elide: Text.ElideRight

                    color: "white"

                    text: address
                }

            }
        }
    }



    ListModel {
        id: clientModel
    }

    Connections {
        target: ConnectionHandler
        function onClientsChanged(numClients)
        {
            clientModel.clear();

            for (let idx = 0; idx < numClients; ++idx)
            {
                let clientName = ConnectionHandler.getClientName(idx);
                let splitIndex = clientName.lastIndexOf("@");
                let name = clientName.slice(0, splitIndex - 1);
                let address = clientName.slice(splitIndex + 2);
                clientModel.append({ "name": name, "address": address });
            }
        }
    }
}
