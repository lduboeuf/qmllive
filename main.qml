import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

import Qt.labs.folderlistmodel 2.2

ApplicationWindow {
    visible: true
    width: 380
    height: 520

    header: ToolBar {
        RowLayout {
            spacing: 20
            anchors.fill: parent

            Label {
                anchors.centerIn: parent
                text: qsTr("LiveCoding")
            }

        }
    }


    Column {
        id: headerTitle
        anchors.margins: 12
        spacing: 12
        Label {
            text: qsTr("Select a Qml File or the entry point of your application:")
        }


        Row {
            id:folderTitleContainer
            height: lblFolder.implicitHeight * 2

            ToolButton {
                enabled: folderModel.rootFolder  !== folderModel.folder
                anchors.verticalCenter: parent.bottom
                opacity: (enabled) ? 1 : 0.2
                contentItem: Image{
                    source: "/assets/back.svg"
                    fillMode: Image.Pad
                    sourceSize.width: folderTitleContainer.height  * 0.4
                    sourceSize.height: folderTitleContainer.height  * 0.4
                    rotation: 90
                }

                onClicked: {
                    console.log(folderModel.folder, sourceDir)
                    if (folderModel.parentFolder != ""){
                        folderModel.folder = folderModel.parentFolder;
                    }
                }
            }

            Label {
                id:lblFolder
                anchors.leftMargin: 12
                anchors.verticalCenter: parent.bottom
                text: folderModel.folder
            }



        }

        Rectangle {
            width: parent.width
            height: 1
            color:"grey"
        }


    }




    ListView {

        anchors {
            left: parent.left
            right: parent.right
            top: headerTitle.bottom
            bottom: parent.bottom
            margins: 12
        }

        currentIndex: -1

        FolderListModel {
            id: folderModel
            rootFolder: "file://" + sourceDir
            folder: "file://" + sourceDir
            nameFilters: ["*.qml"]
        }

        Component {
            id: fileDelegate

            ItemDelegate {
                width: parent.width
                highlighted: ListView.isCurrentItem
                //height: implicitHeight * 2
                contentItem: RowLayout {
                    Image {
                        id:folderImg
                        anchors.left: parent.left
                        source: (folderModel.isFolder(index)) ? "/assets/folder.svg" : "/assets/file.svg"
                    }
                    Label {
                        anchors.left: folderImg.right
                        anchors.leftMargin: 24
                        text: fileName
                    }



                }

                //text: fileName

                onClicked: {
                    if (!folderModel.isFolder(index)) {
                        console.log(folderModel.get(index, "fileURL"))
                        liveLoader.setFile(String(folderModel.get(index, "fileURL")).replace("file://", ""))
                    }else{
                        folderModel.folder = folderModel.get(index, "fileURL")
                    }
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
