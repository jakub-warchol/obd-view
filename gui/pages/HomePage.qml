import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import ObdStyle 1.0
import "qrc:/gui/components"
Item {
    id: root

    //TODO: check the internet before IMEI and before every thingspeak request (and push notification if there is no connection)
    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: window.height / 8 * window.dpi

        spacing: 20

        TextField {
            id: codeFld

            Layout.preferredHeight: 70 * window.dpi
            Layout.preferredWidth: 300 * window.dpi
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            padding: 15

            horizontalAlignment: TextInput.AlignHCenter
            verticalAlignment: TextInput.AlignVCenter
            text: connectionManager.imeiNumber
            placeholderText: qsTr("Enter IMEI code")
            font.pointSize: 15 * window.dpi

            inputMethodHints: Qt.ImhDigitsOnly

            background: Rectangle {
                anchors.fill: parent

                color: "transparent"
                radius: 5 * window.dpi
                border.color: ObdStyle.mainColor
            }

            validator: RegExpValidator {
                regExp: /\d{15}/
            }

            onTextChanged: {
                if(connectBtn.connected) {
                    connectBtn.connected = false
                }
            }
        }

        RowLayout {
            id: connectRow
            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            spacing: 20

            Label {
                font.pointSize: 12 * window.dpi
                text: qsTr("Press the Connect Button to get live data from the car")
            }

            Button {
                id: connectBtn
                z: 0
                property bool connected: false

                text: !connected ? qsTr("Connect") : qsTr("Connected")
                enabled: codeFld.acceptableInput && !connected

                onPressed: {
                    console.log("connect")
                    zBtnAnimation.start()
                    obdLoader.mode = 1

                    connectionManager.imeiNumber = codeFld.text
                    connectionManager.checkImei()
                }

                SequentialAnimation {
                    id: zBtnAnimation

                    NumberAnimation {
                        target: connectBtn
                        property: "z"
                        from: 0
                        to: 10
                        duration: 500
                    }

                    NumberAnimation {
                        target: connectBtn
                        property: "z"
                        from: 10
                        to: 0
                        duration: 500
                    }
                }
            }
        }

        ObdLoader {
            id: obdLoader
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.leftMargin: -30 * window.dpi

            loaderColor: ObdStyle.mainColor

            Connections {
                target: connectionManager

                function onConnectionFinished(imeiFound) {
                    swipeView.interactive = imeiFound
                    tabBar.enabled = imeiFound
                    connectBtn.connected = imeiFound
                    obdLoader.mode = imeiFound ? 0 : 2

                    if(imeiFound) {
                        workerThread.startWorkerThread(connectionManager.channelId)
                    }
                }
            }
        }
    }

}
