import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import ObdStyle 1.0

Item {
    id: root

    Component {
        id: delegate

        Item {
            height: 40 * window.dpi
            width: parent.width

            Rectangle {
                id: delegateRct
                anchors.fill: parent
                radius: 10 * window.dpi
                z:3

                color: ObdStyle.bgTileColor
                opacity: 0.9

                layer {
                    enabled: true
                    effect: InnerShadow {
                        id: shadow
                        anchors.fill: delegateRct

                        color: "#b0000000"
                        radius: 8.0
                        samples: 16
                        spread: 0.5
                        horizontalOffset: -3
                        verticalOffset: 3
                        source: delegateRct
                    }
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 10 * window.dpi
                    anchors.rightMargin: 10 * window.dpi
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    spacing: 20
                    opacity: 1 - codeDscFullLbl.opacity

                    Label {
                        id: timeLbl

                        font.pointSize: 16 * window.dpi
                        text: time
                    }

                    Label {
                        id: codeNoLbl

                        font {
                            bold: true
                            pointSize: 16 * window.dpi
                        }

                        text: codeNo
                    }

                    Label {
                        id: codeDscLbl
                        Layout.fillWidth: true
                        Layout.preferredWidth: 200 * window.dpi
                        Layout.maximumWidth: 350 * window.dpi

                        font {
                            italic: true
                            pointSize: 16 * window.dpi
                        }

                        text: codeDsc
                        elide: Text.ElideRight
                    }
                }

                Label {
                    id: codeDscFullLbl
                    anchors.fill: parent
                    anchors.leftMargin: 10 * window.dpi
                    anchors.rightMargin: 10 * window.dpi
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignLeft
                    opacity: 0

                    text: codeDsc
                    font {
                        italic: true
                        pointSize: 14 * window.dpi
                    }

                    Behavior on opacity {
                        NumberAnimation {duration: 750}
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    enabled: codeDscLbl.truncated

                    onClicked: {
                        codeDscFullLbl.opacity = codeDscFullLbl.opacity === 0 ? 1 : 0
                    }
                }
            }
        }
    }

    ListView {
        id: errorLv
        anchors.fill: parent
        anchors.margins: 12 * window.dpi

        readonly property int animationDuration: 500

        spacing: 10

        ScrollBar.vertical: ScrollBar{
            parent: errorLv.parent
            anchors.top: errorLv.top
            anchors.left: errorLv.right
            anchors.bottom: errorLv.bottom
        }

        delegate: delegate
        model: modelManager.errorModel

        add: Transition {
            id: addTransition
            ParallelAnimation {
                NumberAnimation {property: "opacity"; from: 0.1; to: 0.9; duration: errorLv.animationDuration}
                NumberAnimation {property: "x"; from: -100; duration: errorLv.animationDuration}
                NumberAnimation {property: "y"; from: -100; duration: errorLv.animationDuration}
            }
        }

        displaced: Transition {
            NumberAnimation {properties: "x, y"; duration: errorLv.animationDuration}
        }

        remove: Transition {
            id: removeTransition
            SequentialAnimation {
                NumberAnimation {property: "z"; to: 10; duration: errorLv.animationDuration * 0.5}
                ParallelAnimation {
                    NumberAnimation {property: "opacity"; from: 0.9; to: 0.1; duration: errorLv.animationDuration}
                    NumberAnimation {property: "x"; to: root.width; duration:  errorLv.animationDuration}
                    NumberAnimation {property: "y"; to: 1000; duration: errorLv.animationDuration}
                }
            }
        }
    }
}
