/*
  based on https://forum.qt.io/topic/113743/circulargauge and https://doc.qt.io/qt-5/styling-circulargauge.html
  */

import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Extras 1.0
import QtQuick.Controls.Styles 1.0

import ObdStyle 1.0


CircularGauge {
    id: control

    property int minRedValue
    property int displayedValue: value
    property string units: ""

    style: CircularGaugeStyle {
        id: controlStyle

        tickmarkInset: -15
        minorTickmarkInset: tickmarkInset
        labelStepSize: 20
        labelInset: -30


        needle: Rectangle {
            y: outerRadius * 0.15 * window.dpi
            implicitWidth: outerRadius * 0.03 * window.dpi
            implicitHeight: outerRadius * 0.9 * window.dpi
            antialiasing: true
            color: "#e5e5e5"
        }

        foreground: Item {
            Rectangle {
                width: outerRadius * 0.2 * window.dpi
                height: width * window.dpi
                radius: width / 2 * window.dpi
                color: "#e5e5e5"
                anchors.centerIn: parent

                Label {
                    anchors.top: parent.top
                    anchors.topMargin: (outerRadius + 20) * window.dpi
                    anchors.left: parent.left
                    anchors.leftMargin: -30 * window.dpi

                    text: control.displayedValue + " " + control.units
                    font.pointSize: 14 * window.dpi
                    color: control.value >= control.minRedValue ? "#e34c22" : "#e5e5e5"
                }
            }
        }

        tickmarkLabel: Text {
            font.pixelSize: Math.max(6, outerRadius * 0.1) * window.dpi
            text: styleData.value
            color: styleData.value >= control.minRedValue ? "#e34c22" : "#e5e5e5"
            antialiasing: true
        }

        tickmark: Rectangle {
            visible: styleData.value < control.minRedValue || styleData.value % 10 == 0
            implicitWidth: outerRadius * 0.02 * window.dpi
            antialiasing: true
            implicitHeight: outerRadius * 0.06 * window.dpi
            color: styleData.value >= control.minRedValue ? "#e34c22" : "#e5e5e5"
        }

        minorTickmark: Rectangle {
            implicitWidth: outerRadius * 0.01 * window.dpi
            antialiasing: true
            implicitHeight: outerRadius * 0.03 * window.dpi
            color: styleData.value >= control.minRedValue ? "#e34c22" : "#e5e5e5"
        }
    }

}
