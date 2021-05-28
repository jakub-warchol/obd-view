#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/models/modelmanager.h"
#include "src/api/connection_manager/connectionmanager.h"
#include "src/worker/workerthread.h"
#include "src/items/map_route/maproute.h"

// 862549045729210


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // initialize model manager
    auto modelManager = ModelManager::getInstance(&app);

    // initialize connection manager
    auto connectionManager = ConnectionManager::getInstance(&app);

    // worker thread
    QScopedPointer<WorkerThread> workerThread{new WorkerThread()};

    qmlRegisterSingletonType(QUrl("qrc:/gui/ObdStyle.qml"), "ObdStyle", 1, 0, "ObdStyle");
    qmlRegisterType<MapRoute>("MapRoute", 1, 0, "MapRouteCpp");

    QQmlApplicationEngine engine;

    //  declare propierties for QML
    engine.rootContext()->setContextProperty("modelManager", modelManager);
    engine.rootContext()->setContextProperty("connectionManager", connectionManager);
    engine.rootContext()->setContextProperty("workerThread", workerThread.data());
    engine.rootContext()->setContextProperty("gaugesMargin",
                                         #if defined (Q_OS_IOS) || defined (Q_OS_ANDROID)
                                             60
                                         #else
                                             180
                                         #endif
                                             );
    engine.rootContext()->setContextProperty("mobilePlatform",
                                         #if defined (Q_OS_IOS) || defined (Q_OS_ANDROID)
                                             true
                                         #else
                                             false
                                         #endif
                                             );



    // load qml main file
    const QUrl url(QStringLiteral("qrc:/gui/pages/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // print thread's ids
    qDebug() << "gui thread:\t" << reinterpret_cast<quintptr>(QThread::currentThread());
    qDebug() << "worker thread:\t" << workerThread->workerThreadQuintptr();
    qDebug() << "\n";

    return app.exec();
}
