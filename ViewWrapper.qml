import QtQuick 2.0
import QtQuick.Controls 2.2


ApplicationWindow {
    visible: true
    id:root
    width: 380
    height: 520
    objectName: "viewWrapper"


    Item {
        id:container
        objectName: "liveCodingContainer"
        anchors.fill:parent

    }

    Errors {
        anchors.fill: parent
    }




}
