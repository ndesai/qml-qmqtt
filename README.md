### QML Wrapper for QMQTT

This is a qml wrapper for QMQTT
Provides a  QML

```
import mqtt 1.0

MQTT {
	id: _MQTT
	host: "mind6.com"
	port: 1883
	topic: "hello/world"
	onMessageReceived: {
		console.log("topic=", topic);
		console.log("message=", message);
	}
}

```