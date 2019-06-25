import QtQuick 2.9

Item {

    property alias name: txt.text
    width:200
    height: 200
    Text {
        id:txt
        text: "hello there"
    }

    Rectangle {
        anchors.fill: parent
        color:"red"    
    }
}


