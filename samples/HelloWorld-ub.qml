import QtQuick 2.5
import QtQuick.Controls 2.2
import Ubuntu.Components 1.3

MainView {
    id: root
    objectName: 'mainView'
    applicationName: 'livecoding.lduboeuf'
    automaticOrientation: true

    width: units.gu(45)
    height: units.gu(75)


    Page {
            anchors.fill: parent

            header: PageHeader {
                id: header
                title: i18n.tr('LiveCoding 2')
            }

            Label {
                anchors.centerIn: parent
                text: i18n.tr('Hello World')
            }

 

        }

}
