import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Window 2.15

ComboBox {
    id: root
    width: 140

    leftPadding: 5
    bottomPadding: 5
    topPadding: 5
    rightPadding: 5

    property bool overrideEnterHandler: false
    property string title: ""



    Keys.onUpPressed: {
        if (root.count > 1) {
            if (root.currentIndex > 0)
                root.currentIndex--;
            else
                root.currentIndex = root.count - 1;
        }
    }

    Keys.onDownPressed: {
        if (root.count > 1) {
            if (root.currentIndex < root.count - 1)
                root.currentIndex++;
            else
                root.currentIndex = 0;
        }
    }


    Keys.onEnterPressed: {
        if (!overrideEnterHandler)
            KeyNavigation.tab.forceActiveFocus()
    }

    Keys.onReturnPressed: {
        if (!overrideEnterHandler)
            KeyNavigation.tab.forceActiveFocus()
    }

    onActivated: {
        if (!overrideEnterHandler)
            KeyNavigation.tab.forceActiveFocus()
    }


}
