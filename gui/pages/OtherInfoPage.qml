import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import ObdStyle 1.0

Item {
    id: root

    ListView {
        id: otherDataLv
        anchors.fill: parent
        anchors.margins: 12 * window.dpi

        spacing: 10

        ScrollBar.vertical: ScrollBar{
            parent: otherDataLv.parent
            anchors.top: otherDataLv.top
            anchors.left: otherDataLv.right
            anchors.bottom: otherDataLv.bottom
        }

        delegate: Rectangle {
            id: delegate
            height: 40 * window.dpi
            width: parent.width
            radius: 10 * window.dpi
            z: 3
            enabled: availabled

            color: ObdStyle.bgTileColor
            opacity: 0.9

            NumberAnimation on enabled {
                duration: 500
            }

            layer {
                enabled: true
                effect: InnerShadow {
                    anchors.fill: delegate

                    color: "#b0000000"
                    radius: 8.0
                    samples: 16
                    spread: 0.5
                    horizontalOffset: -3
                    verticalOffset: 3
                    source: delegate
                }
            }

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 10 * window.dpi
                anchors.rightMargin: 10 * window.dpi
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                spacing: 40

                Image {
                    id: dataIconImg
                    opacity: availabled ? 1 : 0.5

                    source: dataIconSrc
                    cache: true

                    layer {
                        enabled: true
                        effect: ShaderEffect {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            property variant src: dataIconImg
                            fragmentShader: "qrc:/resources/shaders/diagnostic_icons/black_icon_fragment.fsh"
                        }
                    }
                }

                Label {
                    id: dataDscLbl
                    Layout.fillWidth: true

                    font {
                        italic: true
                        pointSize: 16 * window.dpi
                    }

                    text: dataDsc
                }

                Label {
                    id: dataValueLbl
                    Layout.rightMargin: 5 * window.dpi

                    font {
                        bold: true
                        pointSize: 16 * window.dpi
                    }

                    text: dataValue

                    NumberAnimation on text {
                        duration: 500
                    }
                }
            }
        }

        model: modelManager.otherDataModel

        displaced: Transition {
            NumberAnimation {properties: "x, y"; duration: 500}
        }
    }
}

