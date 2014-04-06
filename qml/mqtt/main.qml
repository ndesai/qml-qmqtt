import QtQuick 2.0
import mqtt 1.0
Rectangle {
    width: 320
    height: 568
    color: "#f2f2f2"
    MQTT {
        id: _MQTT
        host: "mind6.com"
        port: 1883
        topic: "hello/world"
        onMessageReceived: {;
            _ListModel_Messages.append({"message":message});
        }
        onDisconnected: {
            _MQTT.connect();
        }
    }
    ListModel {
        id: _ListModel_Messages
    }
    Rectangle {
        radius: 5
        color: "#ffffff"
        anchors.fill: _ListView
    }
    ListView {
        id: _ListView
        clip: true
        anchors.fill: parent
        anchors.topMargin: 20
        anchors.leftMargin: 20; anchors.rightMargin: 20
        anchors.bottomMargin: 250
        highlightMoveDuration: 450
        cacheBuffer: 10000
        model: _ListModel_Messages
        onCountChanged: if(count>1) currentIndex=count-1; else currentIndex = 0;
        delegate: Rectangle {
            height: 60
            width: ListView.view.width
            radius: 5
            Text {
                anchors.fill: parent
                anchors.margins: 15
                color: "#000000"
                text: model.message
                wrapMode: Text.WordWrap
            }
            Rectangle {
                width: parent.width
                height: 1
                color: "#f1f1f1"
                anchors.bottom: parent.bottom
            }
        }
    }

    Rectangle {
        anchors.fill: _TextArea
        color: "#ffffff"
        radius: 5
        anchors.margins: -15
    }

    TextEdit {
        id: _TextArea
        anchors.bottom: _Rectangle_Submit.top
        anchors.bottomMargin: 20
        anchors.leftMargin: 35
        anchors.rightMargin: 35
        anchors.left: parent.left
        anchors.right: parent.right
        height: 140
        font.pixelSize: 17
        Keys.onEnterPressed: _Rectangle_Submit.action();
    }

    Rectangle {
        id: _Rectangle_Submit
        radius: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.right: parent.right
        color: _MouseArea_Button.pressed ? "#3BAFDA" : "#4FC1E9"
        height: 50
        Text {
            id: _Text_BuyNow
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            font.family: "HelveticaNeue"
            wrapMode: Text.WordWrap
            font.pixelSize: 17
            maximumLineCount: 3
            elide: Text.ElideRight
            font.letterSpacing: -0.45
            color: "#ffffff"
            text: qsTr("Send Message");
        }
        MouseArea {
            id: _MouseArea_Button
            anchors.fill: parent
            onClicked: _Rectangle_Submit.action();
        }
        function action()
        {
            _MQTT.publishMessage(_TextArea.text);
            _TextArea.text = "";
            Qt.inputMethod.hide();
        }
    }
}
