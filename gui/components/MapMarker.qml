import QtQuick 2.12
import ObdStyle 1.0

Item {
    id: root
    property int animationTime: 1000

    QtObject {
        id: inner

        readonly property color markerColor: "#e98603"
    }

    Rectangle {
        id: ringRct
        width: parent.width
        height: width
        radius: width / 2
        anchors.centerIn: parent

        color: "transparent"
        border {
            width: 1
            color: inner.markerColor
        }

        Rectangle {
            anchors.fill: parent
            radius: parent.radius
            color: inner.markerColor
            opacity: 0.1
        }
    }

    Rectangle {
        id: markerRct
        width: parent.width / 2
        height: width
        radius: width / 2
        anchors.centerIn: parent

        color: inner.markerColor
    }

    ParallelAnimation {
        loops: Animation.Infinite
        running: true

        NumberAnimation {
            target: markerRct
            property: "opacity"
            from: 0.2
            to: 1

            duration: root.animationTime

            easing.type: Easing.Linear
        }

        NumberAnimation {
            target: ringRct
            property: "scale"
            from: 0.1
            to: 2

            duration: root.animationTime

            easing.type: Easing.Linear
        }
    }
}
