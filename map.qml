import QtQuick 2.0
import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15


Item {


    Rectangle {
        width: 800
        height: 600

        Plugin {
            id: osmPlugin
            name: "osm"  // Utilise OpenStreetMap
        }

        Map {
            anchors.fill: parent
            plugin: osmPlugin
            zoomLevel: 13

            // Exemple de marqueur
            MapQuickItem {
                coordinate: QtPositioning.coordinate(48.8566, 2.3522) // Paris
                anchorPoint.x: image.width / 2
                anchorPoint.y: image.height
                sourceItem: Image {
                    source: "qrc:/icons/marker.png"  // Une icône de marqueur
                }
            }
        }
    }


}
