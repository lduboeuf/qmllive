#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <QQuickView>
#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QQmlContext>
#include <QQuickWindow>
//#include <QQmlEngine>

#include "filewatcher.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //QQuickView view;

    const QDir DIRECTORY("/home/phablet/Documents/dev/qml");
    //const QDir DIRECTORY("/home/lionel/dev/qt/testqt");

    const QUrl SOURCE_URL = QUrl::fromLocalFile(DIRECTORY.filePath("main.qml"));

    FileWatcher watcher;
    watcher.setDirectory(DIRECTORY.absolutePath());
   qDebug() << SOURCE_URL;
   qDebug() << DIRECTORY.path();

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("fileWatcher", &watcher);
    engine.rootContext()->setContextProperty("sourceDir", DIRECTORY.path());
    engine.rootContext()->setContextProperty("sourceUrl", SOURCE_URL);
    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.load(QUrl(QStringLiteral("/home/phablet/Documents/dev/qml/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    //TODO see https://stackoverflow.com/questions/55147206/hot-reload-qml-when-using-applicationwindow
    //https://forum.qt.io/topic/102523/reload-a-loader-on-button-click/10
    QObject::connect(&watcher, &FileWatcher::qmlChanged,
            [&engine, SOURCE_URL](){
        QQuickWindow* window = qobject_cast<QQuickWindow*>(engine.rootObjects().at(0));
        if (window) {
            window->close();
        }

        engine.clearComponentCache();
        engine.load(SOURCE_URL);


    });



//    view.setSource(SOURCE_URL);
//    view.setWidth(600);
//    view.setHeight(400);
//    view.show();

//    FileWatcher watcher([&engine, SOURCE_URL](){
//        engine.clearComponentCache();
//        engine.rootContext()->setContextProperty("update", true);
//        //engine.load(SOURCE_URL);
//        //view.engine()->clearComponentCache();
//        //view.setSource(SOURCE_URL);
//    });



    return app.exec();
}
