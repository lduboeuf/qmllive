import QtQuick 2.0
import QtQuick.Controls 2.2


ApplicationWindow {
   visible: true
   id:root
   width: 380
   height: 520


   function showError(show){
       errorMsg.text = fileWatcher.errorMsg
       errorContainer.visible = show
   }



   Loader {
       id: _loader
       active: true

       function reload() {
           source = "";
           source = sourceUrl;
           console.log("kikou source:" + sourceUrl)
       }
       source: sourceUrl

       //anchors.centerIn: parent
   }


   Connections {
       id:connection
       target: fileWatcher

       onQmlLoaded: {
           console.log("reload event")
           showError(false)
           _loader.reload();
       }
       onErrorMsgChanged: {
           console.log("error fired:", fileWatcher.errorMsg)
           showError(true)
       }

   }

   onClosing: {
       console.log("close window event fired")
        connection.enabled = false
       _loader.active = false
   }

   Rectangle {
       id:errorContainer
       visible: false
       anchors.fill: parent
       anchors.margins: 24
       color: "#ffc107"
       opacity: 0.6


       Button {
           id:closeBtn
           text: "X"
           anchors.right: parent.right
           onClicked: {
               errorContainer.visible = false
           }
       }


       Label {
           id: errorMsg
           anchors.top: closeBtn.bottom
           anchors.margins: 12
           width: parent.width
           wrapMode: Label.WordWrap
       }


   }


}
