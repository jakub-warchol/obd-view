import QtQuick 2.12
import QtQuick.Layouts 1.3

import ObdStyle 1.0
import "qrc:/gui/components"

Item {
    id: root

    ColumnLayout {
        anchors.top: parent.top
        anchors.topMargin: gaugesMargin * window.dpi
        anchors.left: parent.left
        anchors.leftMargin: gaugesMargin - 40 * window.dpi
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 65

        ElmGauge {
            id: velocity
            value: modelManager.gaugesModel.kph

            Layout.fillWidth: true
            Layout.preferredHeight: 250 * window.dpi

            Layout.alignment: Qt.AlignLeft
            minimumValue: 0
            maximumValue: 220 * window.dpi
            minRedValue: 180 * window.dpi

            units: "km/h"

            Behavior on value {
                NumberAnimation {
                    duration: 1000
                    easing.type: Easing.OutCirc//Easing.OutElastic
                }
            }
        }

        ElmGauge {
            id: tachometer
            Layout.fillWidth: false
            Layout.preferredHeight: 150 * window.dpi
            Layout.leftMargin: 50 * window.dpi
            Layout.alignment: Qt.AlignRight

            value: modelManager.gaugesModel.rpm
            minimumValue: 0
            maximumValue: 100
            minRedValue: 75

            displayedValue: value * 100
            units: "rpm"

            Behavior on value {
                NumberAnimation {
                    duration: 50
                    easing.type: Easing.OutQuad
                }
            }
        }
    }
}
