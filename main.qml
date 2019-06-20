import QtQuick 2.9
import QtQuick.Window 2.2

import Qt.labs.folderlistmodel 2.2

Item {
//    visible: true
    width: 380
    height: 520

//    ListView {
//        width: 200; height: 400

//        FolderListModel {
//            id: folderModel
//            folder: "file://" + sourceDir
//            nameFilters: ["*.qml"]
//        }

//        Component {
//            id: fileDelegate
//            Text { text: fileName
//                Component.onCompleted: {console.log("hello:" + fileName)}
//            }
//        }

//        model: folderModel
//        delegate: fileDelegate
//    }

    Loader {
        id: _loader
        active: true

        function reload() {
            source = "";
            source = sourceUrl;
            console.log("kikou source:" + sourceUrl)
        }
        source: sourceUrl

        anchors.centerIn: parent
    }

    Connections {
        target: fileWatcher
        onQmlChanged: _loader.reload();
    }

    Component.onCompleted: {
        console.log("kikou completed:" + sourceUrl)
    }
}
