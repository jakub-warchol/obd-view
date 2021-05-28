import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import ObdStyle 1.0
import "qrc:/"

Item {
    id: root

    property int mode: 0
    property alias loaderColor: loader.color

    readonly property var _labelsText: [qsTr(""), qsTr("Checking IMEI number..."), qsTr("IMEI not found")]

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 250 * window.dpi
        spacing: 50

        FishSpinner {
            id: loader
            Layout.fillHeight: true
            Layout.fillWidth: true

            useDouble: true
            running: mode === 1
            opacity: mode === 1 ? 1 : 0
        }

        Label {
            Layout.fillWidth: true
            horizontalAlignment: Qt.AlignHCenter

            font.pointSize: 12
            text: _labelsText[mode]
            opacity: mode !== 0 ? 1 : 0
        }
    }

}
