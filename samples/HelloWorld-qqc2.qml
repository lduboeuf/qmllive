import QtQuick 2.5
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3


ApplicationWindow {
    id: root
    objectName: 'mainView'
    visible:true
    width: 360
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


    Page {
            anchors.fill: parent

            Label {
                anchors.centerIn: parent
                text: qsTr('Hello World')
            }

 

        }

}
