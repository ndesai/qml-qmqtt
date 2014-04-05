#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QtQml>
#include <QQmlContext>
#include "mqtt.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    qmlRegisterType<MQTT>("mqtt", 1, 0, "MQTT");
    viewer.setMainQmlFile(QStringLiteral("qml/mqtt/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
