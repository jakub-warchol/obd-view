import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0
import ObdStyle 1.0

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        color: "blue"

            Image {
                id: splashImg
                property real rotCoef: 0

                anchors.centerIn: parent
                source: "image://android/ki.jpg"
                width: 200
                height: 200
                visible: false
            }

            Rectangle {
                id: rotImage
                width: splashImg.width
                height: splashImg.height
                anchors.centerIn: parent

                color: "transparent"
            }

            PropertyAnimation {
                target: splashImg
                property: "rotCoef"
                from: 0.
                to: 2.
                loops: Animation.Infinite
                duration: 2000
                running: root.visible
            }

            ShaderEffect {
                property var src: splashImg
                property real rotCoef: splashImg.rotCoef
                anchors.fill: rotImage

                vertexShader: "qrc:/resources/shaders/android_splash_screen/splash_screen_vertex.vsh"
                fragmentShader: "qrc:/resources/shaders/android_splash_screen/splash_screen_fragment.fsh"
            }
        }
}
