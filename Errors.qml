import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id:container
    anchors.fill: parent
    objectName: "errorContainer"


    Image{
        id:bugImg
        x: container.width - sourceSize.width -12
        y:container.height - sourceSize.height - 12
        source: "/assets/bug.png"
        fillMode: Image.Pad
        sourceSize.width: 40
        sourceSize.height: 40
        visible: fileWatcher.errorMsg.length > 0

        Rectangle {
            width: parent.width / 3
            height: parent.height / 3
            radius: width / 2
            color:"red"
        }

        MouseArea {
             anchors.fill: parent
             drag.target: bugImg
             drag.axis: Drag.XAndYAxis
             drag.minimumX: 0
             drag.maximumX: container.width - bugImg.width
             drag.minimumY: 0
             drag.maximumY: container.height - bugImg.height
             onClicked: {
                 errorContainer.visible = !errorContainer.visible
             }

        }
    }


    Rectangle {
        id:errorContainer
        visible: (fileWatcher.errorMsg.length > 0)
        anchors.fill: parent
        anchors.margins: 24
        color: "lightgrey"


        Button {
            id:closeBtn
            text: "X"
            anchors.right: parent.right
            onClicked: {
                errorContainer.visible = false
            }
        }


        Label {
            id: errorMsgLbl
            anchors.top: closeBtn.bottom

            anchors.margins: 12
            width: parent.width
            wrapMode: Label.WordWrap
            text: fileWatcher.errorMsg
        }


    }
}
