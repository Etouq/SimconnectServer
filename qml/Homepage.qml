import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml 2.15

import SimconnectServer 1.0
import TypeEnums 1.0

import "CustomControls"

Item {
    id: homePage

    signal selectAircraftClicked()
    signal activateFlightplanPage()

    Column {
        id: navigationButtons

        y: 70
        anchors.right: parent.right
        anchors.rightMargin: 80

        spacing: 50

        GradientButton {
            text: "Select Aircraft"
            width: 200
            onClicked: homePage.selectAircraftClicked()
        }

        GradientButton {
            text: "Flightplan"
            width: 200
            onClicked: homePage.activateFlightplanPage()
        }
    }

    Text {
        anchors.left: clientContainer.left
        anchors.bottom: clientContainer.top
        anchors.leftMargin: 5
        anchors.bottomMargin: 5
        font.pixelSize: 20
        color: "white"
        text: "Connections"
    }

    Rectangle {
        id: clientContainer

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: navigationButtons.left
        anchors.bottom: parent.bottom

        anchors.leftMargin: 80
        anchors.topMargin: 70
        anchors.rightMargin: 80
        anchors.bottomMargin: 70

        color: "transparent"
        border.color: "white"
        border.width: 1

        ListView {
            id: clientView

            anchors.fill: parent
            anchors.margins: 10

            clip: true

            model: clientModel

            delegate: Item {
                required property string name
                required property string address

                height: childrenRect.height

                Text {
                    font.pixelSize: 15
                    font.family: "Roboto"
                    width: 100

                    wrapMode: Text.Wrap

                    color: "white"

                    text: name
                }

                Text {
                    font.pixelSize: 15
                    font.family: "Roboto"
                    x: 110
                    width: 300

                    wrapMode: Text.Wrap

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