import QtQuick 2.12
import QtLocation 5.12
import QtPositioning 5.12

import MapRoute 1.0
import ObdStyle 1.0
import "qrc:/gui/components"

Item {
    id: root

    Component.onCompleted: {
        workerThread.mapRoute = mapCpp
    }

    MapRouteCpp {
        id: mapCpp

        onNewPointAdded: {
            mapPolyline.addCoordinate(newPoint)
        }
    }

    Plugin {
        id: mapPlugin
        name: "osm"

        PluginParameter {name: "osm.mapping.providersrepository.disabled"; value: "true"}
    }

    Map {
        anchors.fill: parent
        anchors.margins: 10 * window.dpi
        plugin: mapPlugin

        center: currentPos.coordinate
        zoomLevel: 17

        // enable gestures
        gesture {
            enabled: true
            preventStealing: true

            acceptedGestures: MapGestureArea.PinchGesture       |
                              MapGestureArea.PanGesture         |
                              MapGestureArea.FlickGesture       |
                              MapGestureArea.RotationGesture    |
                              MapGestureArea.TiltGesture
        }

        MapPolyline {
            id: mapPolyline

            line {
                width: 5 * window.dpi
                color: ObdStyle.mainColor
            }

            path: mapCpp.coords
        }

        MapQuickItem {
            id: currentPos
            coordinate: mapPolyline.path.length === 0 ? QtPositioning.coordinate(50.01701, 20.99055) : mapPolyline.path[mapPolyline.path.length - 1]
            visible: mapPolyline.path.length !== 0

            sourceItem: MapMarker {
                id: marker
                width: 50 * window.dpi
                height: width
                anchors.centerIn: parent
                animationTime: 1000
            }           
        }
    }
}
