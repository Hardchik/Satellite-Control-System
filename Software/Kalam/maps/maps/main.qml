import QtQuick 2.6
import QtQuick.Window 2.2;
import QtPositioning 5.6;
import QtLocation 5.9
import Qt3D.Input 2.1
import QtQuick.Controls 2.2;


Item {
    width: Qt.platform.os == "android" ? Screen.width : 200
    height: Qt.platform.os == "android" ? Screen.height : 200
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter {
             name: 'osm.mapping.highdpi_tiles'
            value: !!1      }
    }

    Connections{

        target: gmap
        onGetLat : mapmarker.center.latitude = lat

    }
    Connections{

        target: gmap
        onGetLang : mapmarker.center.longitude = lang

    }
    Connections{

        target: gmap
        onGetLang : map.center = QtPositioning.coordinate(mapmarker.center.latitude,mapmarker.center.longitude,150);



    }

    Map {
        id: map
        anchors.fill: parent
        anchors.rightMargin: -15
        anchors.bottomMargin: -10
        anchors.leftMargin: 15
        anchors.topMargin: 10
        plugin: mapPlugin
        center: QtPositioning.coordinate() // NSUT
        zoomLevel: 14
        activeMapType: supportedMapTypes[2]




        MapCircle {

            id: mapmarker
                center {
                    latitude: 28.6078
                    longitude: 77.0406


                }
                radius: 50.0
                color: 'green'
                border.width: 3
        }




    }

}
