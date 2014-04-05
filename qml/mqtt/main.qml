import QtQuick 2.0
import mqtt 1.0
Rectangle {
    width: 320
    height: 568
    MQTT {
        id: mqtt
        host: "mind6.com"
        port: 1883
        topic: "hello/world"
        onMessageReceived: {;
            _ListModel_Messages.append({"message":message});
            _ListView.positionViewAtEnd();
        }
    }
    ListModel {
        id: _ListModel_Messages
    }
    ListView {
        id: _ListView
        anchors.fill: parent
        model: _ListModel_Messages
        delegate: Rectangle {
            height: 60
            width: ListView.view.width
            Text {
                anchors.fill: parent
                anchors.margins: 15
                color: "#000000"
                text: model.message
            }
            border.width: 1
            border.color: "#cccccc"
        }
    }
}
