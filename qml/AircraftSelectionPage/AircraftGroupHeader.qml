import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

import SimconnectServer 1.0

Label {

    leftPadding: 40

    font.pixelSize: 40
    font.family: "Roboto Mono"
    font.bold: true

    color: "white"

    property alias collapseToggle: __collapseToggle

    background: Rectangle {
        color: Material.primary
    }

    Shape {
        id: __collapseToggle

        width: 40
        height: 40
        anchors.verticalCenter: parent.verticalCenter

        ShapePath {
            fillColor: "white"
            joinStyle: ShapePath.RoundJoin

            PathMove {
                x: 5
                y: 18
            }
            PathLine {
                relativeX: 30
                relativeY: 0
            }
            PathLine {
                relativeX: -15
                relativeY: 15
            }
        }
    }
}
