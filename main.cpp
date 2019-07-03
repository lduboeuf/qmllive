#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <QQuickView>
#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QQmlContext>
#include <QQuickWindow>
#include <QQuickItem>
#include <QQmlComponent>
#include <QStandardPaths>
//#include <QQmlEngine>

#include "filewatcher.h"
#include "liveloader.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

#ifdef Q_OS_UBUNTU_TOUCH
    const QDir DIRECTORY(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0]);
#else
    const QDir DIRECTORY(QDir::homePath());

#endif
    //const QUrl SOURCE_URL = QUrl::fromLocalFile(DIRECTORY.filePath("main.qml"));

    FileWatcher watcher;
    //qDebug() << SOURCE_URL;
    qDebug() << DIRECTORY.absolutePath();

    QQmlApplicationEngine engine;
    QQmlApplicationEngine engine2; //engine responsible for displaying selected qml files



    LiveLoader liveLoader(&engine2, &watcher);

    engine.rootContext()->setContextProperty("liveLoader", &liveLoader);
    engine.rootContext()->setContextProperty("sourceDir", DIRECTORY.path());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));




    if (engine.rootObjects().isEmpty())
        return -1;



    return app.exec();
}
