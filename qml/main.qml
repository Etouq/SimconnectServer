import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQml 2.15

import SimconnectServer 1.0
import TypeEnums 1.0
import Flightplan 1.0
import "AircraftSelectionPage"
import "CustomControls"
import "FlightplanPage"

ApplicationWindow {
    width: 800
    height: 500
    visible: true

    minimumWidth: 600
    minimumHeight: 185

    StackView {
        id: appStack
        anchors.fill: parent
        initialItem: homePage

        popEnter: Transition {
            YAnimator {
                from: -appStack.height
                to: 0
                duration: 400
                easing.type: Easing.OutCubic
            }
        }

        popExit: Transition {
            YAnimator {
                from: 0
                to: appStack.height
                duration: 400
                easing.type: Easing.OutCubic
            }
        }

        pushEnter: Transition {
            YAnimator {
                from: appStack.height
                to: 0
                duration: 400
                easing.type: Easing.OutCubic
            }
        }

        pushExit: Transition {
            YAnimator {
                from: 0
                to: -appStack.height
                duration: 400
                easing.type: Easing.OutCubic
            }
        }
    }

    Component {
        id: homePage

        Homepage {

            onSelectAircraftClicked: function() {
                appStack.push(aircraftPage)
            }

            onActivateFlightplanPage: function() {
                appStack.push(flightplanPage)
            }
        }
    }

    Component {
        id: flightplanPage

        FlightplanPage {

            onBackClicked: function() {
                appStack.pop()
            }
        }
    }

    Component {
        id: aircraftPage

        AircraftSelectionPage {

            onBackClicked: function() {
                appStack.pop()
            }
        }
    }




}
