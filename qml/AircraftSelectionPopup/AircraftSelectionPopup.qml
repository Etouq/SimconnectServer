import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import SimconnectServer 1.0

Window {
    color: "#1A1D21"

    width: (400 + 15) * 3 + 10 * 2 + 40
    height: (144 + 25 + 7.5) * 4 + 10 * 3 + 40

    modality: Qt.ApplicationModal

    ScrollView {
        anchors.fill: parent
        anchors.margins: 20

        contentWidth: availableWidth
        contentHeight: thumbColumn.height


        clip: true

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        Column {
            id: thumbColumn
            width: parent.width

            Text {

                font.pixelSize: 40
                font.family: "Roboto Mono"
                font.bold: true

                color: "white"
                text: "Jet"
            }

            Grid {
                width: parent.width
                height: childrenRect.height
                columns: Math.max(1, Math.floor((parent.width + 10) / (400 + 15 + 10)))

                spacing: 10

                Repeater {
                    model: AircraftManager.getNumJets()

                    AircraftSelectionItem {
                        required property int index

                        title: AircraftManager.getJetName(index)
                        source: "file:" + AircraftManager.getJetImagePath(index)

                        onClicked: AircraftManager.selectJet(index)
                    }
                }
            }

            Text {

                font.pixelSize: 40
                font.family: "Roboto Mono"
                font.bold: true

                color: "white"
                text: "Turboprop"
            }

            Grid {
                width: parent.width
                height: childrenRect.height
                columns: Math.max(1, Math.floor((parent.width + 10) / (400 + 15 + 10)))

                spacing: 10

                Repeater {
                    model: AircraftManager.getNumTurboprop()

                    AircraftSelectionItem {
                        required property int index

                        title: AircraftManager.getTurbopropName(index)
                        source: "file:" + AircraftManager.getTurbopropImagePath(index)

                        onClicked: AircraftManager.selectTurboprop(index)
                    }
                }
            }

            Text {

                font.pixelSize: 40
                font.family: "Roboto Mono"
                font.bold: true

                color: "white"
                text: "Propeller"
            }

            Grid {
                width: parent.width
                height: childrenRect.height
                columns: Math.max(1, Math.floor((parent.width + 10) / (400 + 15 + 10)))

                spacing: 10

                Repeater {
                    model: AircraftManager.getNumProp()

                    AircraftSelectionItem {
                        required property int index

                        title: AircraftManager.getPropName(index)
                        source: "file:" + AircraftManager.getPropImagePath(index)

                        onClicked: AircraftManager.selectProp(index)
                    }
                }
            }

        }

    }
}
