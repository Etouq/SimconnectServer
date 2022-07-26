import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15

import TypeEnums 1.0
import Flightplan 1.0

Rectangle {
    id: rowRoot

    width: row.width + 2 * rowRoot.borderWidth // 885
    height: 60


    color: "transparent"
    border.width: rowRoot.borderWidth
    border.color: "white"

    required property int index
    required property string ident
    required property string wpTypeUrl
    required property string altTypeText
    required property string dtk
    required property string dist
    required property string totDist
    required property string speed

    readonly property real cellPadding: 4
    readonly property real borderWidth: 1

    property alias isSelectedItem: selectionIndicator.visible

    FontMetrics {
        id: fontMetrics
        font.family: "Roboto Mono"
        font.bold: true
        font.pixelSize: 20
    }

    Row {
        id: row

        x: rowRoot.borderWidth
        y: rowRoot.borderWidth + rowRoot.cellPadding
        height: rowRoot.height - 2 * (rowRoot.cellPadding + rowRoot.borderWidth)

        spacing: rowRoot.cellPadding
        rightPadding: rowRoot.cellPadding
        leftPadding: rowRoot.cellPadding

        Rectangle {
            id: identCell

            readonly property real contentHeight: 60 - 2 * (rowRoot.cellPadding + rowRoot.borderWidth)

            width: 20 + identCell.contentHeight + fontMetrics.boundingRect("A".repeat(9)).width + 6 - rowRoot.cellPadding// 309
            height: parent.height

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#0093d0" }
                GradientStop { position: 0.6; color: Qt.rgba(0, 147, 208, 0) }
            }

            // Rectangle {
            //     anchors.fill: parent
            //     anchors.topMargin: 0
            //     anchors.bottomMargin: 0
            //     anchors.leftMargin: 0
            //     anchors.rightMargin: 0
            //     gradient: Gradient {
            //         GradientStop { position: 0.0; color: "#0093d0" }
            //         GradientStop { position: 0.6; color: Qt.rgba(0, 147, 208, 0) }
            //     }
            // }

            Image {
                id: wpIcon
                x: 20 - rowRoot.cellPadding
                width: parent.height
                height: parent.height
                source: rowRoot.wpTypeUrl
            }

            Text {
                id: wpIdent
                anchors.left: wpIcon.right
                anchors.verticalCenter: parent.verticalCenter

                font.pixelSize: 20
                color: "white"
                text: rowRoot.ident
            }
        }

        Rectangle {
            y: -row.y
            width: rowRoot.borderWidth
            height: rowRoot.height

            color: "white"
        }

        TableCell {
            //alt
            width: fontMetrics.boundingRect("A00000FT").width + 12// + rowRoot.cellPadding * 2 // 164
            cellPadding: rowRoot.cellPadding
            borderWidth: rowRoot.borderWidth
            text: rowRoot.altTypeText
        }

        Rectangle {
            y: -row.y
            width: rowRoot.borderWidth
            height: rowRoot.height

            color: "white"
        }

        TableCell {
            //dtk
            width: fontMetrics.boundingRect("000°").width + 12// + rowRoot.cellPadding * 2 // 92
            cellPadding: rowRoot.cellPadding
            borderWidth: rowRoot.borderWidth
            text: rowRoot.dtk
        }

        Rectangle {
            y: -row.y
            width: rowRoot.borderWidth
            height: rowRoot.height

            color: "white"
        }

        TableCell {
            //dist
            width: fontMetrics.boundingRect("00.0NM").width + 12// + rowRoot.cellPadding * 2 // 128
            cellPadding: rowRoot.cellPadding
            borderWidth: rowRoot.borderWidth
            text: rowRoot.dist + "\n" + rowRoot.totDist
        }

        Rectangle {
            y: -row.y
            width: rowRoot.borderWidth
            height: rowRoot.height

            color: "white"
        }

        TableCell {
            //spd
            width: fontMetrics.boundingRect("___KT").width + 12// + rowRoot.cellPadding * 2 // 110
            cellPadding: rowRoot.cellPadding
            borderWidth: rowRoot.borderWidth
            text: rowRoot.speed//"___KT"
        }
    }

    Rectangle {
        id: selectionIndicator
        anchors.fill: parent
        anchors.margins: rowRoot.borderWidth
        color: "transparent"
        border.width: rowRoot.cellPadding
        border.color: "#00b4ff"
        visible: false
    }

    Shape {
            id: arrow

            visible: FlightplanManager.activeLegIdx === rowRoot.index

            readonly property real offsetLeft: 0
            readonly property real offsetTop: -60
            readonly property real endOffsetTop: 0


            readonly property real arrowLeftOffset: 25
            readonly property real arrowTopOffset: 30

            readonly property real lineWidth: 5
            readonly property real lineDistance: 13
            readonly property real headWidth: 9


            readonly property real x1: offsetLeft + arrowLeftOffset
            readonly property real y1: offsetTop + arrowTopOffset
            readonly property real y2: endOffsetTop + arrowTopOffset

            ShapePath {

                fillColor: "magenta"
                strokeColor: "transparent"

                PathMove {
                    x: arrow.x1
                    y: arrow.y1 - arrow.lineWidth / 2
                }
                PathLine {
                    relativeX: 0
                    relativeY: arrow.lineWidth
                }
                PathLine {
                    relativeX: -arrow.lineDistance
                    relativeY: 0
                }
                PathLine {
                    relativeX: 0
                    y: arrow.y2 - arrow.lineWidth / 2
                }
                PathLine {
                    relativeX: arrow.lineDistance - arrow.headWidth
                    relativeY: 0
                }
                PathLine {
                    relativeX: 0
                    relativeY: -arrow.lineWidth
                }
                PathLine {
                    x: arrow.x1
                    y: arrow.y2
                }
                PathLine {
                    relativeX: -arrow.headWidth
                    relativeY: arrow.lineWidth * 1.5
                }
                PathLine {
                    relativeX: 0
                    relativeY: -arrow.lineWidth
                }
                PathLine {
                    relativeX: arrow.headWidth - arrow.lineDistance - arrow.lineWidth
                    relativeY: 0
                }
                PathLine {
                    relativeX: 0
                    y: arrow.y1 - arrow.lineWidth / 2
                }

            }
        }



}