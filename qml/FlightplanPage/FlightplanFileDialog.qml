import QtQuick 2.15
import QtQuick.Dialogs 1.3

import Flightplan 1.0

FileDialog {
    id: fileDialog

    title: "Please choose a file"
    folder: shortcuts.home
    visible: false

    nameFilters: "pln files (*.PLN *.pln)"

    onAccepted: function() {
        FlightplanManager.readFromFile(decodeURIComponent(fileDialog.fileUrl.toString().replace(/^(file:\/{3})/,"")));
    }

}