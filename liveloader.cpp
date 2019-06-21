#include "liveloader.h"
#include <QDebug>
#include <QFileInfo>
#include <QQuickWindow>
#include <QQmlContext>
#include <QUrl>



LiveLoader::LiveLoader( QQmlApplicationEngine *engine, FileWatcher *fileWatcher, QObject *parent) : QObject(parent)
{

    m_fileWatcher = fileWatcher;
    m_engine = engine;

    QObject::connect(m_fileWatcher, &FileWatcher::qmlChanged, this, &LiveLoader::update);
    QObject::connect(m_engine, &QQmlApplicationEngine::objectCreated, [&](){ created = true;});
}

void LiveLoader::setFile(const QString &path)
{
    QFileInfo fi(path);

    m_filePath = QUrl::fromLocalFile(fi.filePath());
    qDebug() << "selected file:" << m_filePath;

    m_engine->load(m_filePath);
    m_fileWatcher->setDirectory(fi.absolutePath());

      QQuickWindow* window = qobject_cast<QQuickWindow*>(m_engine->rootObjects().at(0));
      if (!window) {
          qDebug() << "use view wrapper";
          m_engine->rootContext()->setContextProperty("fileWatcher", this);
          //m_engine->rootContext()->setContextProperty("sourceDir", fi.baseName());
          m_engine->rootContext()->setContextProperty("sourceUrl", m_filePath);
          m_engine->load(QUrl(QStringLiteral("qrc:/ViewWrapper.qml")));

      }


}

void LiveLoader::update()
{
    qDebug() << "update fired";
    if (created){
        m_engine->clearComponentCache();
        QQuickWindow* window = qobject_cast<QQuickWindow*>(m_engine->rootObjects().at(0));
        if (window) {
            qDebug() << "kikou close";
            window->deleteLater();
            m_engine->load(m_filePath);
        }

        emit notify();
    }
}


