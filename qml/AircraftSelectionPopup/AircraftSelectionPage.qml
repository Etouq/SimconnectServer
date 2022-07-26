import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

import SimconnectServer 1.0

import "../CustomControls"

Item {
    id: aircraftPageRoot

    signal backClicked()

    GradientButton {
        id: backButton
        text: "Back"

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10

        onClicked: aircraftPageRoot.backClicked()
    }

    ScrollView {

        anchors {
            top: backButton.bottom
            right: parent.right
            bottom: parent.bottom
            left: parent.left

            margins: 20
        }

        contentWidth: availableWidth
        contentHeight: thumbColumn.height


        clip: true

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        Column {
            id: thumbColumn
            width: parent.width

            spacing: 8

            // n_max = ⌊(width + spacing) / (minWidth + spacing)⌋
            readonly property int thumbnailColumnCount: Math.max(1, Math.floor((thumbColumn.width + 10) / (300 + 10)))

            // Text {

            //     font.pixelSize: 40
            //     font.family: "Roboto Mono"
            //     font.bold: true

            //     color: "white"
            //     text: "Jet"

            //     bottomPadding: 8

            //     MouseArea {
            //         anchors.fill: parent

            //         onClicked: tempId.expanded = !tempId.expanded
            //     }
            // }

            Label {

                width: parent.width

                leftPadding: 40

                font.pixelSize: 40
                font.family: "Roboto Mono"
                font.bold: true

                color: "white"
                text: "Jet"


                background: Rectangle {
                    color: Material.primary
                }

                Shape {
                    id: collapseToggle

                    width: 40
                    height: 40
                    anchors.verticalCenter: parent.verticalCenter

                    ShapePath {
                        fillColor: "white"
                        joinStyle: ShapePath.RoundJoin

                        PathMove {
                            x: 5
                            y: 22
                        }
                        PathLine {
                            x: 35
                            y: 22
                        }
                        PathLine {
                            x: 20
                            y: 37
                        }
                    }
                }


                MouseArea {
                    anchors.fill: parent

                    onClicked: jetLayout.expanded = !jetLayout.expanded
                }
            }

            GridLayout {
                id: jetLayout
                width: parent.width

                property bool expanded: true

                states: [
                    State {
                        name: "" // expanded = default
                        when: jetLayout.expanded
                        PropertyChanges {
                            target: jetLayout
                            visible: true
                            height: undefined
                        }
                        PropertyChanges {
                            target: collapseToggle
                            rotation: 00
                        }
                    },
                    State {
                        name: "collapsed"
                        when: !jetLayout.expanded
                        PropertyChanges {
                            target: jetLayout
                            visible: false
                            height: 0
                        }
                        PropertyChanges {
                            target: collapseToggle
                            rotation: 270
                        }
                    }
                ]

                transitions: [
                    Transition {
                        from: ""
                        to: "collapsed"
                        SequentialAnimation {
                            PropertyAction {
                                target: jetLayout
                                property: "clip"
                                value: true
                            }
                            ParallelAnimation {
                                RotationAnimation {
                                    target: collapseToggle
                                    direction: RotationAnimation.Counterclockwise
                                    duration: 200
                                }
                                NumberAnimation {
                                    target: jetLayout
                                    property: "height"
                                    duration: 500
                                }
                            }
                            PropertyAction {
                                target: jetLayout
                                property: "visible"
                                value: false
                            }
                        }
                    },
                    Transition {
                        from: "collapsed"
                        to: ""
                        SequentialAnimation {
                            PropertyAction {
                                target: jetLayout
                                property: "visible"
                                value: true
                            }
                            ParallelAnimation {
                                RotationAnimation {
                                    target: collapseToggle
                                    direction: RotationAnimation.Clockwise
                                    duration: 200
                                }
                                NumberAnimation {
                                    target: jetLayout
                                    property: "height"
                                    duration: 500
                                }
                            }
                            PropertyAction {
                                target: jetLayout
                                property: "clip"
                                value: false
                            }
                        }
                    }
                ]

                columns: thumbColumn.thumbnailColumnCount

                columnSpacing: 10
                rowSpacing: 10

                Repeater {
                    model: AircraftManager.getNumJets()

                    AircraftSelectionItem {
                        required property int index

                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Layout.minimumHeight: minHeight
                        Layout.minimumWidth: 300

                        title: AircraftManager.getJetName(index)
                        source: "file:" + AircraftManager.getJetImagePath(index)

                        onClicked: function() { console.log(`clicked ${title}`); AircraftManager.selectJet(index)}
                    }
                }
            }

            Label {

                width: parent.width

                leftPadding: 40

                font.pixelSize: 40
                font.family: "Roboto Mono"
                font.bold: true

                color: "white"
                text: "Turboprop"

                topInset: 4

                background: Rectangle {
                    color: Material.primary
                }

                Shape {
                    id: turbopropCollapseToggle

                    width: 40
                    height: 40
                    anchors.verticalCenter: parent.verticalCenter

                    ShapePath {
                        fillColor: "white"
                        joinStyle: ShapePath.RoundJoin

                        PathMove {
                            x: 5
                            y: 22
                        }
                        PathLine {
                            x: 35
                            y: 22
                        }
                        PathLine {
                            x: 20
                            y: 37
                        }
                    }
                }


                MouseArea {
                    anchors.fill: parent

                    onClicked: turbopropLayout.expanded = !turbopropLayout.expanded
                }
            }

            GridLayout {
                id: turbopropLayout
                width: parent.width

                property bool expanded: true

                columns: thumbColumn.thumbnailColumnCount

                columnSpacing: 10
                rowSpacing: 10

                Repeater {
                    model: AircraftManager.getNumTurboprop()

                    AircraftSelectionItem {
                        required property int index

                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Layout.minimumHeight: minHeight
                        Layout.minimumWidth: 300

                        title: AircraftManager.getTurbopropName(index)
                        source: "file:" + AircraftManager.getTurbopropImagePath(index)

                        onClicked: AircraftManager.selectTurboprop(index)
                    }
                }

                states: [
                    State {
                        name: "" // expanded = default
                        when: turbopropLayout.expanded
                        PropertyChanges {
                            target: turbopropLayout
                            visible: true
                            height: undefined
                        }
                        PropertyChanges {
                            target: turbopropCollapseToggle
                            rotation: 00
                        }
                    },
                    State {
                        name: "collapsed"
                        when: !turbopropLayout.expanded
                        PropertyChanges {
                            target: turbopropLayout
                            visible: false
                            height: 0
                        }
                        PropertyChanges {
                            target: turbopropCollapseToggle
                            rotation: 270
                        }
                    }
                ]

                transitions: [
                    Transition {
                        from: ""
                        to: "collapsed"
                        SequentialAnimation {
                            PropertyAction {
                                target: turbopropLayout
                                property: "clip"
                                value: true
                            }
                            ParallelAnimation {
                                RotationAnimation {
                                    target: turbopropCollapseToggle
                                    direction: RotationAnimation.Counterclockwise
                                    duration: 200
                                }
                                NumberAnimation {
                                    target: turbopropLayout
                                    property: "height"
                                    duration: 500
                                }
                            }
                            PropertyAction {
                                target: turbopropLayout
                                property: "visible"
                                value: false
                            }
                        }
                    },
                    Transition {
                        from: "collapsed"
                        to: ""
                        SequentialAnimation {
                            PropertyAction {
                                target: turbopropLayout
                                property: "visible"
                                value: true
                            }
                            ParallelAnimation {
                                RotationAnimation {
                                    target: turbopropCollapseToggle
                                    direction: RotationAnimation.Clockwise
                                    duration: 200
                                }
                                NumberAnimation {
                                    target: turbopropLayout
                                    property: "height"
                                    duration: 500
                                }
                            }
                            PropertyAction {
                                target: turbopropLayout
                                property: "clip"
                                value: false
                            }
                        }
                    }
                ]
            }

            Label {
                width: parent.width

                leftPadding: 40

                font.pixelSize: 40
                font.family: "Roboto Mono"
                font.bold: true

                color: "white"
                text: "Propeller"

                topInset: 4

                background: Rectangle {
                    color: Material.primary
                }

                Shape {
                    id: propCollapseToggle

                    width: 40
                    height: 40
                    anchors.verticalCenter: parent.verticalCenter

                    ShapePath {
                        fillColor: "white"
                        joinStyle: ShapePath.RoundJoin

                        PathMove {
                            x: 5
                            y: 22
                        }
                        PathLine {
                            x: 35
                            y: 22
                        }
                        PathLine {
                            x: 20
                            y: 37
                        }
                    }
                }


                MouseArea {
                    anchors.fill: parent

                    onClicked: propLayout.expanded = !propLayout.expanded
                }
            }

            GridLayout {
                id: propLayout
                width: parent.width

                property bool expanded: true

                columns: thumbColumn.thumbnailColumnCount

                columnSpacing: 10
                rowSpacing: 10

                Repeater {
                    model: AircraftManager.getNumProp()

                    AircraftSelectionItem {
                        required property int index

                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Layout.minimumHeight: minHeight
                        Layout.minimumWidth: 300

                        title: AircraftManager.getPropName(index)
                        source: "file:" + AircraftManager.getPropImagePath(index)

                        onClicked: AircraftManager.selectProp(index)
                    }
                }

                states: [
                    State {
                        name: "" // expanded = default
                        when: propLayout.expanded
                        PropertyChanges {
                            target: propLayout
                            visible: true
                            height: undefined
                        }
                        PropertyChanges {
                            target: propCollapseToggle
                            rotation: 00
                        }
                    },
                    State {
                        name: "collapsed"
                        when: !propLayout.expanded
                        PropertyChanges {
                            target: propLayout
                            visible: false
                            height: 0
                        }
                        PropertyChanges {
                            target: propCollapseToggle
                            rotation: 270
                        }
                    }
                ]

                transitions: [
                    Transition {
                        from: ""
                        to: "collapsed"
                        SequentialAnimation {
                            PropertyAction {
                                target: propLayout
                                property: "clip"
                                value: true
                            }
                            ParallelAnimation {
                                RotationAnimation {
                                    target: propCollapseToggle
                                    direction: RotationAnimation.Counterclockwise
                                    duration: 200
                                }
                                NumberAnimation {
                                    target: propLayout
                                    property: "height"
                                    duration: 500
                                }
                            }
                            PropertyAction {
                                target: propLayout
                                property: "visible"
                                value: false
                            }
                        }
                    },
                    Transition {
                        from: "collapsed"
                        to: ""
                        SequentialAnimation {
                            PropertyAction {
                                target: propLayout
                                property: "visible"
                                value: true
                            }
                            ParallelAnimation {
                                RotationAnimation {
                                    target: propCollapseToggle
                                    direction: RotationAnimation.Clockwise
                                    duration: 200
                                }
                                NumberAnimation {
                                    target: propLayout
                                    property: "height"
                                    duration: 500
                                }
                            }
                            PropertyAction {
                                target: propLayout
                                property: "clip"
                                value: false
                            }
                        }
                    }
                ]
            }

        }

    }
}
