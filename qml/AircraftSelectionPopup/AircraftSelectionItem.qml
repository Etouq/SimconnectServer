import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {

    property alias title: aircraftTitle.text
    property alias source: aircraftThumb.source

    readonly property real minHeight: aircraftThumb.height + 7.5 + aircraftTitle.height + 1

    color: clickRegion.containsPress ? "#0093d0" : "white"//"#1A1D21"

    signal clicked()

    MouseArea {
        id: clickRegion
        anchors.fill: parent

        cursorShape: Qt.PointingHandCursor

        onClicked: parent.clicked()
    }

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0; color: "#0093d0" }
            GradientStop { position: 0.6; color: "#000093d0" }
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

        color: "white"

        wrapMode: Text.WordWrap

    }
}

// Button {

//     property alias title: aircraftTitle.text
//     property alias source: aircraftThumb.source

//     property real desiredHeight: aircraftThumb.height + bottomPadding - topInset

//     leftPadding: 7.5
//     rightPadding: 7.5
//     bottomPadding: 7.5
//     topInset: -aircraftTitle.height - 1

//     background: Rectangle {
//         color: parent.down ? "#0093d0" : "white"//"#1A1D21"

//         Rectangle {
//             anchors.fill: parent
//             gradient: Gradient {
//                 GradientStop { position: 0; color: "#0093d0" }
//                 GradientStop { position: 0.6; color: "#000093d0" }
//             }
//         }
//     }



//     contentItem: Image {
//         id: aircraftThumb

//         //anchors.bottom: parent.bottom
//         //anchors.bottomMargin: 7.5
//         //anchors.horizontalCenter: parent.horizontalCenter

//         width: parent.width
//         height: width * 144 / 400
//         sourceSize.width: 600
//         sourceSize.height: 216

//         fillMode: Image.PreserveAspectFit
//     }

//     Text {
//         anchors.centerIn: parent

//         font.pixelSize: 18
//         font.family: "Roboto Mono"
//         font.bold: true

//         color: "white"

//         text: `height: ${aircraftThumb.height}\nparent: ${parent.height}\nratio: ${aircraftThumb.width / aircraftThumb.height}`
//     }

//     Text {
//         id: aircraftTitle
//         anchors.bottom: aircraftThumb.top
//         //anchors.top: parent.top
//         //anchors.topMargin: 1

//         width: parent.width
//         horizontalAlignment: Text.AlignHCenter
//         verticalAlignment: Text.AlignVCenter

//         font.pixelSize: 18
//         font.family: "Roboto Mono"
//         font.bold: true

//         color: "white"

//         wrapMode: Text.WordWrap

//     }
// }