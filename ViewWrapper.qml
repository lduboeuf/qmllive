import QtQuick 2.0
import QtQuick.Controls 2.2


ApplicationWindow {
    visible: true
    //id:centralPane
   width: 380
   height: 520

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
       onNotify: {
           console.log("kikou reload from QML")

           _loader.reload();
       }
   }

}
