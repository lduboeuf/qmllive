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
    m_currentWindow = nullptr;

    m_engine->rootContext()->setContextProperty("fileWatcher", this);
    m_engine->rootContext()->setContextProperty("sourceUrl", m_filePath);

    QQmlComponent component(m_engine, QUrl("qrc:/Errors.qml"));
    m_errorWrapper = qobject_cast<QQuickItem*>(component.create());

    QObject::connect(m_fileWatcher, &FileWatcher::qmlChanged, this, &LiveLoader::loadQml);
    //QObject::connect(m_engine, &QQmlApplicationEngine::objectCreated, this, &LiveLoader::onLoadedQml);

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

    m_fileWatcher->setDirectory(fi.absolutePath()); //start watching directory


}


void LiveLoader::loadQml()
{
    //m_engine->trimComponentCache();


    m_errorMsg = "";
    emit errorMsgChanged(m_errorMsg);


    //clean existing window if not viewWrapper
    if (m_currentWindow && !useWrapper) {
        qDebug() << "destroy old item";
        delete m_currentWindow;
    }


    m_engine->clearComponentCache();
    QQmlComponent component(m_engine, m_filePath);
    QObject *item = component.create();
    if (!item) {
        //something went wrong
        qDebug() << "kikou error:" << component.errorString();
        m_errorMsg = component.errorString();
        //start wrapper to display error
        if (!useWrapper) startWrapper();
    }else{

        //window item ?
        QQuickWindow* window = qobject_cast<QQuickWindow*>(item);
        if (window){
            //qDebug() << "i'm a window";
            //make sure that we do not have a wrapper
            if (useWrapper && m_currentWindow){
                delete m_currentWindow;
                useWrapper = false;
                //qDebug() << "destroy wrapper";
            }
            m_currentWindow = window;
            QQuickItem *root = window->contentItem();
            m_errorWrapper->setParentItem(root);

        }else{
            //qDebug() << "i'm an item";

            QQuickItem *itemToDisplay = qobject_cast<QQuickItem*>(item);

            if (!useWrapper) startWrapper();
            QQuickItem *loader = m_currentWindow->findChild<QQuickItem*>("liveCodingContainer");

            //any already loaded child ? -> delete them
            for( QObject* ob: loader->childItems()) {
                delete ob; //delete root item
            }

            itemToDisplay->setParentItem(loader);
            //item->setParent(loader);

            //            for( QObject* ob: loader->childItems()) {
            //                   qDebug()<< "existing:" <<  ob->metaObject()->className();
            //                   for( QObject* obc: ob->children()) {
            //                          qDebug()<< "existing-child:" <<  obc->metaObject()->className();
            //                   }
            //            }
        }



    }



    emit errorMsgChanged(m_errorMsg);



}




void LiveLoader::startWrapper()
{
    qDebug() << "start view wrapper";
    useWrapper = true;
    QQmlComponent component(m_engine, QUrl("qrc:/ViewWrapper.qml"));
    QQuickWindow *object = qobject_cast<QQuickWindow*>(component.create());
    QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);

    m_currentWindow = object;
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


