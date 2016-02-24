#include <QGuiApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>

#include <grpc++/create_channel.h>

#include "context.h"
#include "stateobject.h"
#include "stateproperty.h"

int main(int argc, char **argv)
{
    qmlRegisterUncreatableType<Context>("human.components", 0, 1, "Context", "Uncreatable type");

    qmlRegisterType<StateObject>("human.components", 0, 1, "StateObject");
    qmlRegisterType<StateProperty>("human.components", 0, 1, "StateProperty");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    if(app.arguments().length() < 1)
    {
        qDebug() << "Error: You must specify resourceId and resourceKey for digital self.";
        return EXIT_FAILURE;
    }

    // DigitalSelf CRDT resource info.
    QString referenceId = app.arguments().value(1);

    // gRPC / CRDT connection.
    GrpcChannel channel;
    channel.connectToHost("127.0.0.1:9600");

    qDebug() << "Creating DigitalSelf handler instance with referenceId:" << referenceId;
    Context context(referenceId, &channel);

    engine.rootContext()->setContextProperty("context", &context);
    engine.load("main.qml");

    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);
    return app.exec();
}
