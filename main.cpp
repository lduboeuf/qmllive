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
//#include <QQmlEngine>

#include "filewatcher.h"
#include "liveloader.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //QQuickView view;

    //const QDir DIRECTORY("/home/phablet/Documents/dev/qml");
    const QDir DIRECTORY("/home/lionel/dev/qt/testqt");

    const QUrl SOURCE_URL = QUrl::fromLocalFile(DIRECTORY.filePath("main.qml"));

    FileWatcher watcher;
    //watcher.setDirectory(DIRECTORY.absolutePath());
   qDebug() << SOURCE_URL;
   qDebug() << DIRECTORY.absolutePath();

    QQmlApplicationEngine engine;
    QQmlApplicationEngine engine2;


    //watcher.setEngine(&engine2);
    LiveLoader liveLoader(&engine2, &watcher);

    engine.rootContext()->setContextProperty("liveLoader", &liveLoader);
    engine.rootContext()->setContextProperty("sourceDir", DIRECTORY.path());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

   //engine2.load(QStringLiteral("file:///home/lionel/dev/qt/testqt/main.qml"));

    if (engine.rootObjects().isEmpty())
        return -1;

//    QQuickWindow* window = qobject_cast<QQuickWindow*>(engine2.rootObjects().at(0));
//    if (!window) {
//        qDebug() << "use view wrapper";
//        engine2.rootContext()->setContextProperty("fileWatcher", &watcher);
//        engine2.rootContext()->setContextProperty("sourceDir", DIRECTORY.path());
//        engine2.rootContext()->setContextProperty("sourceUrl", SOURCE_URL);
//        engine2.load(QUrl(QStringLiteral("qrc:/ViewWrapper.qml")));

//    }





//    //TODO see https://stackoverflow.com/questions/55147206/hot-reload-qml-when-using-applicationwindow
//    //https://forum.qt.io/topic/102523/reload-a-loader-on-button-click/10
//    QObject::connect(&watcher, &FileWatcher::qmlChanged,
//            [&engine2, SOURCE_URL](){

//        //engine2.clearComponentCache();

//        QQuickWindow* window = qobject_cast<QQuickWindow*>(engine2.rootObjects().at(0));
//        if (window) {
//            qDebug() << "kikou close";
//            window->deleteLater();
//            engine2.load(SOURCE_URL);
//        }

//        qDebug() << "kikou reload";


//    });






    return app.exec();
}
