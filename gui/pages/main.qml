import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.0
import QtQuick.Window 2.12
import ObdStyle 1.0

import "qrc:/gui/components"

ApplicationWindow {
    id: window
    property int defaultWidth: 720
    property int defaultHeight: 1000 //1280 on phone

    property var swipeView: pages

    readonly property real dpi: mobilePlatform ? Screen.pixelDensity * 25.4 / 160 : 1

    width: defaultWidth
    minimumWidth: defaultWidth
    maximumWidth: defaultWidth

    height: defaultHeight
    minimumHeight: defaultHeight
    maximumHeight: defaultHeight

    visible: true
    title: qsTr("ELM Interface")

    Pages {
        id: pages
        anchors.fill: parent
    }

    header: Rectangle {
        id: headerRct
        width: parent.width
        height: 50
        z: 2

        color: ObdStyle.mainColor

        Label {
            anchors.centerIn: parent

            font.pointSize: 12 * window.dpi
            text: title
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        enabled: false

        TabButton {
            text: qsTr("Home")
        }

        TabButton {
            text: qsTr("Gauges")
        }

        TabButton {
            text: qsTr("Coords")
        }

        TabButton {
            text: qsTr("Errors")
        }

        TabButton {
            text: qsTr("Others")
        }

        onCurrentIndexChanged: {
            swipeView.currentIndex = currentIndex
        }
    }
}
