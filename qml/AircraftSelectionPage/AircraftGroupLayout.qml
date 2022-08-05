import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Shapes 1.15

GridLayout {
    id: aircraftGroupLayout

    property bool expanded: true

    required property Shape collapseToggle


    columnSpacing: 10
    rowSpacing: 10

    states: [
        State {
            name: "" // expanded = default
            when: aircraftGroupLayout.expanded
            PropertyChanges {
                target: aircraftGroupLayout
                visible: true
                height: undefined
            }
            PropertyChanges {
                target: aircraftGroupLayout.collapseToggle
                rotation: 0
            }
        },
        State {
            name: "collapsed"
            when: !aircraftGroupLayout.expanded
            PropertyChanges {
                target: aircraftGroupLayout
                visible: false
                height: 0
            }
            PropertyChanges {
                target: aircraftGroupLayout.collapseToggle
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
                    target: aircraftGroupLayout
                    property: "clip"
                    value: true
                }
                ParallelAnimation {
                    RotationAnimation {
                        target: aircraftGroupLayout.collapseToggle
                        direction: RotationAnimation.Counterclockwise
                        duration: 300
                        easing.type: Easing.InOutCubic
                    }
                    NumberAnimation {
                        target: aircraftGroupLayout
                        property: "height"
                        duration: 500
                        easing.type: Easing.InOutCubic
                    }
                }
                PropertyAction {
                    target: aircraftGroupLayout
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
                    target: aircraftGroupLayout
                    property: "visible"
                    value: true
                }
                ParallelAnimation {
                    RotationAnimation {
                        target: aircraftGroupLayout.collapseToggle
                        direction: RotationAnimation.Clockwise
                        duration: 300
                        easing.type: Easing.InOutCubic
                    }
                    NumberAnimation {
                        target: aircraftGroupLayout
                        property: "height"
                        duration: 500
                        easing.type: Easing.InOutCubic
                    }
                }
                PropertyAction {
                    target: aircraftGroupLayout
                    property: "clip"
                    value: false
                }
            }
        }
    ]
}