import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: gradientButton

    leftPadding: 7.5
    rightPadding: 7.5
    bottomPadding: 7.5
    topPadding: 7.5

    leftInset: 0
    rightInset: 0
    bottomInset: 0
    topInset: 0

    background: Rectangle {

        color: gradientButton.down && gradientButton.enabled ? "#0093d0" : "black"

        Rectangle {
            anchors.fill: parent

            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#0093d0"
                }
                GradientStop {
                    position: 0.6
                    color: "#000093d0"
                }
            }
        }
    }

    contentItem: Text {
        id: buttonText

        horizontalAlignment: Text.AlignHCenter

        font.pixelSize: 18

        color: gradientButton.enabled ? "white" : "#666666"

        text: parent.text
    }

}