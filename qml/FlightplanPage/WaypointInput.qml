import QtQuick 2.15
import QtQuick.Controls 2.15
import QtPositioning 5.15

import TypeEnums 1.0
import Flightplan 1.0

import "../CustomControls"

Column {
    id: inputColumn

    property bool insertModeActive: false
    property bool editOrMoveModeActive: false
    readonly property bool validInput: identInput.acceptableInput && latInput.acceptableInput && lonInput.acceptableInput && (!alt1Input.enabled || alt1Input.acceptableInput) && (!alt2Input.enabled || alt2Input.acceptableInput) && (speedInput.acceptableInput || speedInput.text.length === 0)

    spacing: 8

    function copyWaypointData(index: int) {
        insertModeActive = false;

        const waypoint = FlightplanManager.getWaypoint(index);

        identInput.text = waypoint.ident;

        switch (waypoint.waypointType) {
            case WaypointType.AIRPORT:
                wpTypeInput.currentIndex = 0;
                break;
            case WaypointType.INTERSECTION:
                wpTypeInput.currentIndex = 1;
                break;
            case WaypointType.NDB:
                wpTypeInput.currentIndex = 2;
                break;
            case WaypointType.USER:
                wpTypeInput.currentIndex = 3;
                break;
            case WaypointType.VOR:
                wpTypeInput.currentIndex = 4;
                break;
            case WaypointType.ATC:
                wpTypeInput.currentIndex = 5;
                break;
            case WaypointType.NONE:
            default:
                wpTypeInput.currentIndex = -1;
                break;
        }

        const pos = waypoint.position;

        latInput.text = pos.latitude.toFixed(6);
        lonInput.text = pos.longitude.toFixed(6);

        switch (waypoint.altitudeType) {
            case WpAltitudeType.NONE:
                altTypeInput.currentIndex = 0;
                break;
            case WpAltitudeType.AT:
                altTypeInput.currentIndex = 1;
                break;
            case WpAltitudeType.AT_OR_BELOW:
                altTypeInput.currentIndex = 2;
                break;
            case WpAltitudeType.AT_OR_ABOVE:
                altTypeInput.currentIndex = 3;
                break;
            case WpAltitudeType.BETWEEN:
                altTypeInput.currentIndex = 4;
                break;
            default:
                altTypeInput.currentIndex = 0;
                break;
        }

        if (waypoint.altitudeType !== WpAltitudeType.NONE) {
            alt1Input.text = waypoint.alt1.toString();

            if (waypoint.altitudeType === WpAltitudeType.BETWEEN) {
                alt2Input.text = waypoint.alt2.toString();
            }
        }

        speedInput.text = waypoint.speed <= 0 ? "0" : waypoint.speed.toString();
    }

    function createWaypoint() {
        const waypoint = FlightplanManager.waypoint();

        waypoint.ident = identInput.text.toUpperCase();

        switch (wpTypeInput.currentIndex) {
            case 0:
                waypoint.waypointType = WaypointType.AIRPORT;
                break;
            case 1:
                waypoint.waypointType = WaypointType.INTERSECTION;
                break;
            case 2:
                waypoint.waypointType = WaypointType.NDB;
                break;
            case 3:
                waypoint.waypointType = WaypointType.USER;
                break;
            case 4:
                waypoint.waypointType = WaypointType.VOR;
                break;
            case 5:
                waypoint.waypointType = WaypointType.ATC;
                break;
            default:
                break;
        }

        waypoint.position = QtPositioning.coordinate(latInput.getValue(), lonInput.getValue());

        switch (altTypeInput.currentIndex) {
            case 0:
                waypoint.altitudeType = WpAltitudeType.NONE;
                break;
            case 1:
                waypoint.altitudeType = WpAltitudeType.AT;
                waypoint.alt1 = parseInt(alt1Input.text);
                break;
            case 2:
                waypoint.altitudeType = WpAltitudeType.AT_OR_BELOW;
                waypoint.alt1 = parseInt(alt1Input.text);
                break;
            case 3:
                waypoint.altitudeType = WpAltitudeType.AT_OR_ABOVE;
                waypoint.alt1 = parseInt(alt1Input.text);
                break;
            case 4:
                waypoint.altitudeType = WpAltitudeType.BETWEEN;
                waypoint.alt1 = parseInt(alt1Input.text);
                waypoint.alt2 = parseInt(alt2Input.text);
                break;
            default:
                waypoint.altitudeType = WpAltitudeType.NONE;
                break;
        }

        waypoint.speed = speedInput.text.length === 0 || parseInt(speedInput.text) === 0 ? -1 : parseInt(speedInput.text);

        return waypoint;
    }

    function appendWaypoint() {
        const waypoint = createWaypoint();

        FlightplanManager.appendWaypoint(waypoint);
    }

    function insertWaypoint(index: int) {
        const waypoint = createWaypoint();

        FlightplanManager.insertWaypoint(index, waypoint);
    }

    StyledTextInput {
        id: identInput

        placeholderText: "Ident"
        inputMethodHints: Qt.ImhUppercaseOnly

        font.capitalization: Font.AllUppercase

        validator: RegularExpressionValidator {
            regularExpression: /[A-Za-z0-9]{1,9}/
        }

        EnterKey.type: Qt.EnterKeyNext
        KeyNavigation.tab: wpTypeInput
    }

    StyledComboBox {
        id: wpTypeInput

        model: ["Airport", "Intersection", "NDB", "User", "VOR", "ATC"]

        title: "Waypoint Type"

        EnterKey.type: Qt.EnterKeyNext
        KeyNavigation.tab: latInput
    }

    StyledTextInput {
        id: latInput

        placeholderText: "Latitude"
        inputMethodHints: Qt.ImhPreferNumbers

        font.capitalization: Font.AllUppercase

        validator: RegularExpressionValidator {
            regularExpression: /[-+NSns]?(?:[1-8]?\d(?:\.\d{1,6})?|90(?:\.0{1,6})?)/
        }

        EnterKey.type: Qt.EnterKeyNext
        KeyNavigation.tab: lonInput

        function getValue()
        {
            const upperText = text.toUpperCase();
            if (upperText.startsWith("-") || upperText.startsWith("S")) {
                return -parseFloat(upperText.slice(1));
            }

            if (upperText.startsWith("+") || upperText.startsWith("N")) {
                return parseFloat(upperText.slice(1));
            }

            return parseFloat(upperText);
        }
    }

    StyledTextInput {
        id: lonInput

        placeholderText: "Longitude"
        inputMethodHints: Qt.ImhPreferNumbers

        font.capitalization: Font.AllUppercase

        validator: RegularExpressionValidator {
            regularExpression: /[-+EWew]?(?:(?:[1-9]?|1[0-7])\d(?:\.\d{1,6})?|180(?:\.0{1,6})?)/
        }

        EnterKey.type: Qt.EnterKeyNext
        KeyNavigation.tab: altTypeInput

        function getValue()
        {
            const upperText = text.toUpperCase();
            if (upperText.startsWith("-") || upperText.startsWith("W")) {
                return -parseFloat(upperText.slice(1));
            }

            if (upperText.startsWith("+") || upperText.startsWith("E")) {
                return parseFloat(upperText.slice(1));
            }

            return parseFloat(upperText);
        }
    }

    StyledComboBox {
        id: altTypeInput

        title: "Altitude Type"
        model: ["None", "At", "At or Below", "At or Above", "In Between"]

        EnterKey.type: Qt.EnterKeyNext
        KeyNavigation.tab: alt1Input
    }

    StyledTextInput {
        id: alt1Input

        enabled: altTypeInput.currentIndex != 0

        inputMethodHints: Qt.ImhDigitsOnly
        placeholderText: altTypeInput.currentIndex != 4 ? "Altitude" : "Lower Altitude"
        validator: RegularExpressionValidator { regularExpression: /-?\d{1,6}/ }

        EnterKey.type: altTypeInput.currentIndex == 4 ? Qt.EnterKeyNext : Qt.EnterKeyDone
        KeyNavigation.tab: alt2Input
    }

    StyledTextInput {
        id: alt2Input

        enabled: altTypeInput.currentIndex == 4

        inputMethodHints: Qt.ImhDigitsOnly
        placeholderText: "Upper Altitude"
        validator: RegularExpressionValidator { regularExpression: /-?\d{1,6}/ }

        EnterKey.type: Qt.EnterKeyDone
        KeyNavigation.tab: speedInput
    }

    StyledTextInput {
        id: speedInput

        inputMethodHints: Qt.ImhDigitsOnly
        placeholderText: "Speed"
        validator: RegularExpressionValidator { regularExpression: /0|[1-9]\d{0,3}/ }

        EnterKey.type: Qt.EnterKeyDone
        KeyNavigation.tab: appendButton
    }

    Button {
        id: appendButton

        enabled: inputColumn.validInput && !inputColumn.editOrMoveModeActive

        topInset: 0
        bottomInset: 0

        leftPadding: 5
        bottomPadding: 0
        topPadding: 0
        rightPadding: 5

        text: "Append"

        width: 140

        KeyNavigation.tab: insertButton

        onClicked: function() {
            inputColumn.appendWaypoint();
        }
    }

    Button {
        id: insertButton

        enabled: inputColumn.validInput && !inputColumn.editOrMoveModeActive

        topInset: 0
        bottomInset: 0

        leftPadding: 5
        bottomPadding: 0
        topPadding: 0
        rightPadding: 5

        text: inputColumn.insertModeActive ? "Cancel" : "Insert"

        width: 140

        KeyNavigation.tab: directToButton

        onClicked: function() {
            if (inputColumn.insertModeActive) {
                inputColumn.insertModeActive = false;
            } else {
                inputColumn.insertModeActive = true;
            }
        }
    }

    Button {
        id: directToButton

        enabled: inputColumn.validInput && !inputColumn.editOrMoveModeActive

        topInset: 0
        bottomInset: 0

        leftPadding: 5
        bottomPadding: 0
        topPadding: 0
        rightPadding: 5

        text: "Direct To"

        width: 140

        KeyNavigation.tab: identInput
    }
}