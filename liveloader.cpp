#include "liveloader.h"
#include <QDebug>
#include <QFileInfo>
#include <QQuickWindow>
#include <QQmlContext>
#include <QQuickItem>
#include <QUrl>



LiveLoader::LiveLoader( QQmlApplicationEngine *engine, FileWatcher *fileWatcher, QObject *parent) : QObject(parent)
{

    m_fileWatcher = fileWatcher;
    m_engine = engine;
    m_engine->setOutputWarningsToStandardError(false); //don't display errors in logs

    QObject::connect(m_fileWatcher, &FileWatcher::qmlChanged, this, &LiveLoader::loadQml);
    QObject::connect(m_engine, &QQmlApplicationEngine::objectCreated, this, &LiveLoader::onLoadedQml);

    QObject::connect(m_engine, &QQmlApplicationEngine::warnings,this, &LiveLoader::handleQmlErrors);

}

void LiveLoader::setFile(const QString &path)
{
    QFileInfo fi(path);


    m_errorMsg = "";
    m_filePath = QUrl::fromLocalFile(fi.filePath());
    qDebug() << "selected file:" << m_filePath;
    //m_engine->trimComponentCache();

    created = false;
    useWrapper = false;

    m_fileWatcher->setDirectory(fi.absolutePath()); //set the directory to listen to





}

void LiveLoader::onLoadedQml(QObject *object, const QUrl &url)
{
    Q_UNUSED(url);

    if (!object){
        //something went wrong while loading qml file, let display the errors in a wrapper
        qDebug() << "something went wrong";
        startWrapper();
        emit errorMsgChanged(m_errorMsg);

    }else {
        qDebug() << "loaded:" << object->metaObject()->className();

        QQuickWindow* window = qobject_cast<QQuickWindow*>(object);
        if (!window) {
            startWrapper();
        }

        created = true;
//        for( QObject* ob: m_engine->rootObjects().first()->children()) {
//            qDebug() <<  "existing object:" << ob->metaObject()->className();
//        }
    }
}

void LiveLoader::loadQml()
{
    //qDebug() << "receive notification of filewatcher:" << m_filePath;
    //m_engine->trimComponentCache();
    m_errorMsg = "";
    m_engine->clearComponentCache();
    if (!useWrapper){ //we delete old entries and then load the new window

        if (!m_engine->rootObjects().isEmpty()){
//            for( QObject* ob: m_engine->rootObjects().first()->children()) {
//                qDebug()<< "existing:" <<  ob->metaObject()->className();
//                ob->deleteLater();
//            }
            QQuickWindow* window = qobject_cast<QQuickWindow*>(m_engine->rootObjects().first());
            if (window) {
                qDebug() << "destroy old item";
                window->close();
            }
        }


        m_engine->load(m_filePath);
    }

    emit qmlLoaded();


}




void LiveLoader::startWrapper()
{
    qDebug() << "start view wrapper";
    useWrapper = true;
    m_engine->rootContext()->setContextProperty("fileWatcher", this);
    m_engine->rootContext()->setContextProperty("sourceUrl", m_filePath);
    m_engine->load(QUrl(QStringLiteral("qrc:/ViewWrapper.qml")));
//    QQuickWindow* window = qobject_cast<QQuickWindow*>(m_engine->rootObjects().at(0));
//    if (window) {
//        QObject::connect(window, &QQuickWindow::close, [&window](){
//            window->deleteLater();
//        });

//    }

}

void LiveLoader::handleQmlErrors(const QList<QQmlError> &qmlErrors)
{
    qDebug() << "kikou errors";
    QStringList errors;
    foreach (const QQmlError& error, qmlErrors) {
        errors.append(error.toString());
    }

    if (!errors.isEmpty()){
        m_errorMsg = errors.join("\n");
        emit errorMsgChanged(m_errorMsg);
    }

}


