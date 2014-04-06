#ifndef MQTT_H
#define MQTT_H

#include <QObject>
#include "qmqtt.h"
#include <QDebug>
#include <QUuid>

#define DEBUG if(1) qDebug() << __PRETTY_FUNCTION__

class MQTT : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString topic READ topic WRITE setTopic NOTIFY topicChanged)

    QString m_host;

    int m_port;

    QString m_topic;

public:
    explicit MQTT(QObject *parent = 0);

    QString host() const
    {
        return m_host;
    }

    int port() const
    {
        return m_port;
    }

    QString topic() const
    {
        return m_topic;
    }

signals:

    void hostChanged(QString arg);
    void portChanged(int arg);
    void topicChanged(QString arg);
    // custom signals
    void messageReceived(QString topic, QString message);
    // pass-thru signals
    void connected();
    void error(QAbstractSocket::SocketError);
    void connacked(quint8 ack);
    void published(QMQTT::Message &message);
    void pubacked(quint8 type, quint16 msgid);
    void received(const QMQTT::Message &message);
    void subscribed(const QString &topic);
    void subacked(quint16 mid, quint8 qos);
    void unsubscribed(const QString &topic);
    void unsubacked(quint16 mid);
    void pong();
    void disconnected();

public slots:

    void setHost(QString arg)
    {
        if (m_host != arg) {
            m_host = arg;
            emit hostChanged(arg);
        }
    }
    void setPort(int arg)
    {
        if (m_port != arg) {
            m_port = arg;
            emit portChanged(arg);
        }
    }
    void setTopic(QString arg)
    {
        if (m_topic != arg) {
            m_topic = arg;
            emit topicChanged(arg);
        }
    }

    // custom slots
    void processReceivedMessage(const QMQTT::Message &arg)
    {
        DEBUG << QString::fromLatin1(arg.payload());
        emit messageReceived(arg.topic(),
                             QString::fromLatin1(arg.payload()));
    }

    void subscribedToTopic(QString topic)
    {
        DEBUG << "topic is " << topic;
    }

    void subscribeToTopic(quint8 ack)
    {
        DEBUG << "qos = " << ack;
        if(!m_topic.isEmpty())
        {
            this->client->subscribe(m_topic, 0);
        }
    }

    void publishMessage(QString message)
    {
        if(!message.isEmpty() && this->client->isConnected())
        {
            QMQTT::Message msg;
            msg.setTopic(m_topic);
            msg.setPayload(message.toLatin1());
            this->client->publish(msg);
        }
    }

    // pass-thru slots
    void connect()
    {
        if(this->client)
            this->client->connect();
    }
    quint16 publish(QMQTT::Message &message)
    {
        if(this->client)
            return this->client->publish(message);
        return 0;
    }
    void puback(quint8 type, quint16 msgid)
    {
        if(this->client)
            this->client->puback(type, msgid);
    }

    quint16 subscribe(const QString &topic, quint8 qos)
    {
        if(this->client)
            return this->client->subscribe(topic, qos);
        return 0;
    }

    void unsubscribe(const QString &topic)
    {
        if(this->client)
            this->client->unsubscribe(topic);
    }

    void ping()
    {
        if(this->client)
            this->client->ping();
    }
    void disconnect()
    {
        if(this->client)
            this->client->disconnect();
    }


private slots:
    void initializeConnection();

private:
    QMQTT::Client *client;
};
#endif // MQTT_H
