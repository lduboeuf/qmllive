import QtQuick 2.0
import QtQuick.Controls 2.2


ApplicationWindow {
    visible: true
    id:root
    width: 380
    height: 520
    objectName: "viewWrapper"



    onClosing: {
        console.log("close window event fired")
        connection.enabled = false
        _loader.active = false
    }


    Item {
        id:container
        anchors.fill:parent


        Loader {
            id: _loader
            active: true
            anchors.fill: container
            objectName: "loader"

            function reload() {
                source = "";
                source = sourceUrl;
                console.log("kikou source:" + sourceUrl)
            }
            source: sourceUrl

            onLoaded: {
//                console.log("kikou loaded:" + _loader.item)
//                if (_loader.item.toString() === "QQuickApplicationWindow")
//                    console.log("i'm a window")
//                else
//                    console.log("i'm an item")
            }
        }

    }


    Image{
        id:bugImg
        x: container.width - sourceSize.width -12
        y:container.height - sourceSize.height - 12
        source: "/assets/bug.png"
        fillMode: Image.Pad
        sourceSize.width: 30
        sourceSize.height: 30
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
        visible: false
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

    Connections {
        id:connection
        target: fileWatcher

        onQmlLoaded: {
            console.log("reload event")
            errorContainer.visible = false
            _loader.reload();
        }


//        onErrorMsgChanged: {
//            console.log("error fired:", fileWatcher.errorMsg)
//            //errorMsgLbl.text = fileWatcher.errorMsg
//            //bugImg.visible = true
//        }

    }


}
