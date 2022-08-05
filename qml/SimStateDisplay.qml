import QtQuick 2.15
import QtQuick.Controls 2.15

import SimconnectServer 1.0
import TypeEnums 1.0

import "CustomControls"

Item {
    id: stateDisplayRoot

    height: 68

    Text {
        id: stateDisplayTitle
        font.family: "Roboto"
        font.pixelSize: 20
        font.bold: true

        color: "white"
        text: "Sim"
    }

    Loader {
        id: indicatorLoader

        anchors.left: stateDisplayTitle.right
        anchors.leftMargin: 20
        anchors.verticalCenter: stateDisplayTitle.verticalCenter
        width: 24
        height: 24

        active: true
        asynchronous: true
    }

    Loader {
        id: textLoader

        anchors.left: indicatorLoader.right
        anchors.right: parent.right
        anchors.leftMargin: 15
        anchors.baseline: stateDisplayTitle.baseline

        asynchronous: true
    }

    Loader {
        id: buttonLoader

        anchors.left: stateDisplayTitle.left
        anchors.top: stateDisplayTitle.bottom

        asynchronous: true
        active: SimManager.state === SimState.WAITING_FOR_USER_RESTART

        sourceComponent: Button {

                font.family: "Roboto"
                font.pixelSize: 13
                font.weight: Font.Medium

                text: "Reconnect"

                onClicked: function() {
                    SimManager.userRestart();
                }
            }
    }

    states: [
        State {
            name: "connected"
            when: SimManager.state === SimState.CONNECTED
            PropertyChanges {
                target: indicatorLoader
                sourceComponent: connectedIndicator
            }
            PropertyChanges {
                target: textLoader
                sourceComponent: connectingText
                active: false
            }
        },
        State {
            name: "connecting"
            when: SimManager.state === SimState.CONNECTING
            PropertyChanges {
                target: indicatorLoader
                sourceComponent: connectingIndicator
            }
            PropertyChanges {
                target: textLoader
                sourceComponent: connectingText
                active: true
            }
        },
        State {
            name: "waitForUserRestart"
            when: SimManager.state === SimState.WAITING_FOR_USER_RESTART
            PropertyChanges {
                target: indicatorLoader
                sourceComponent: disconnectedIndicator
            }
            PropertyChanges {
                target: textLoader
                sourceComponent: waitForUserText
                active: true
            }
        },
        State {
            name: "unexpectedDisconnect"
            when: SimManager.state === SimState.UNEXPECTED_DISCONNECT
            PropertyChanges {
                target: indicatorLoader
                sourceComponent: disconnectedIndicator
            }
            PropertyChanges {
                target: textLoader
                sourceComponent: unexpectedDisconnectText
                active: true
            }
        },
        State {
            name: "waitForNextAttempt"
            when: SimManager.state === SimState.WAITING_FOR_NEXT_ATTEMPT
            PropertyChanges {
                target: indicatorLoader
                sourceComponent: disconnectedIndicator
            }
            PropertyChanges {
                target: textLoader
                sourceComponent: waitForAttemptText
                active: true
            }
        }
    ]

    Component {
        id: connectedIndicator

        Rectangle {
            radius: 12
            color: "green"
        }
    }

    Component {
        id: disconnectedIndicator

        Rectangle {
            radius: 12
            color: "red"
        }
    }

    Component {
        id: connectingIndicator

        LoadSpinner {
            radius: 12
        }
    }

    Component {
        id: waitForAttemptText

        Text {
            id: textItem
            anchors.baseline: parent.baseline

            font.family: "Roboto"
            font.pixelSize: 15
            font.bold: false

            color: "white"
            text: "Failed to connect, retrying in 10 seconds"

            wrapMode: Text.WordWrap

            Timer {
                id: retryTimer

                property int timeLeft: 10

                interval: 1000
                running: true
                repeat: true

                onTriggered: function() {
                    --timeLeft;
                    textItem.text = "Failed to connect, retrying in " + retryTimer.timeLeft + " seconds"
                }
            }
        }
    }

    Component {
        id: unexpectedDisconnectText

        Text {
            id: textItem
            anchors.baseline: parent.baseline

            font.family: "Roboto"
            font.pixelSize: 15
            font.bold: false

            color: "white"
            text: "Connection closed unexpectedly, attempting to reconnect in 10 seconds"

            wrapMode: Text.WordWrap

            Timer {
                id: retryTimer

                property int timeLeft: 10

                interval: 1000
                running: true
                repeat: true

                onTriggered: function() {
                    --timeLeft;
                    textItem.text = "Connection closed unexpectedly, attempting to reconnect in " + retryTimer.timeLeft + " seconds"
                }
            }
        }
    }

    Component {
        id: connectingText

        Text {
            id: textItem
            anchors.baseline: parent.baseline

            font.family: "Roboto"
            font.pixelSize: 15
            font.bold: false

            color: "white"
            text: "Connecting"

            wrapMode: Text.WordWrap

            Timer {
                id: connectingTimer

                property int numDots: 0

                interval: 500
                running: true
                repeat: true

                onTriggered: function() {
                    numDots = ++numDots % 4;
                    textItem.text = "Connecting" + ".".repeat(connectingTimer.numDots)
                }
            }
        }
    }

    Component {
        id: waitForUserText

        Text {
            id: waitForUserText
            anchors.baseline: parent.baseline

            font.family: "Roboto"
            font.pixelSize: 15
            font.bold: false

            color: "white"
            text: "Sim closed. Click \"Reconnect\" when the sim is running again"

            wrapMode: Text.WordWrap
        }
    }

}
