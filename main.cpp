#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "appenum.h"
#include "serialport.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    SerialPort *serialPort = new SerialPort(&app);
    QStringList serialPortList = serialPort->portList();

    engine.rootContext()->setContextProperty("SerialPort", serialPort);
    qmlRegisterType<AppEnum>("AppEnum", 1, 0, "AppEnum");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
