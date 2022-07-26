import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    height: parent.height//60 - 2 * borderWidth

    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "#0093d0"
        }
        GradientStop {
            position: 0.6
            color: Qt.rgba(0, 147, 208, 0)
        }
    }

    property alias text: textItem.text
    property alias pixelSize: textItem.font.pixelSize
    property alias textObject: textItem

    property real cellPadding: 4
    property real borderWidth: 1

    // Rectangle {
    //     anchors.fill: parent
    //     anchors.topMargin: 0
    //     anchors.bottomMargin: 0
    //     anchors.leftMargin: 0
    //     anchors.rightMargin: 0
    //     gradient: Gradient {
    //         GradientStop {
    //             position: 0.0
    //             color: "#0093d0"
    //         }
    //         GradientStop {
    //             position: 0.6
    //             color: Qt.rgba(0, 147, 208, 0)
    //         }
    //     }
    // }

    Text {
        id: textItem

        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 6// + cellPadding

        font.pixelSize: 20

        color: "white"
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        lineHeight: 0.9
    }

}
