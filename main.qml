import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

import Qt.labs.folderlistmodel 2.2

ApplicationWindow {
    visible: true
    //id:centralPane
   width: 380
    height: 520


    Label {
        id: lblTitle
        text: qsTr("select a Qml File or the entry point of your application:")
    }


        ListView {

            anchors {
                left: parent.left
                right: parent.right
                top: lblTitle.bottom
                bottom: parent.bottom
                margins: 12
            }

            currentIndex: -1

            FolderListModel {
                id: folderModel
                folder: "file://" + sourceDir
                nameFilters: ["*.qml"]
            }

            Component {
                id: fileDelegate

                ItemDelegate {
                    width: parent.width
                    highlighted: ListView.isCurrentItem
                    //height: implicitHeight * 2
                    text: fileName

                    onClicked: {
                        console.log(folderModel.get(index, "fileURL"))
                        liveLoader.setFile(String(folderModel.get(index, "fileURL")).replace("file://", ""))
                    }
                }
            }

            model: folderModel
            delegate: fileDelegate
        }


//    Loader {
//        id: _loader
//        active: true

//        function reload() {
//            source = "";
//            source = sourceUrl;
//            console.log("kikou source:" + sourceUrl)
//        }
//        source: sourceUrl

//        anchors.centerIn: parent
//    }

//    Connections {
//        target: fileWatcher
//        onQmlChanged: {
//            console.log("kikou reload from QML")

//            _loader.reload();
//        }
//    }


}
