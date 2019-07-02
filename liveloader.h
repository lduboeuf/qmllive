#ifndef LIVELOADER_H
#define LIVELOADER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include "filewatcher.h"

class LiveLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString errorMsg MEMBER m_errorMsg NOTIFY errorMsgChanged)
public:
    explicit LiveLoader( QQmlApplicationEngine *engine,FileWatcher *fileWatcher, QObject *parent = nullptr);
    Q_INVOKABLE void setFile(const QString &path);

//    QString errorMsg() const
//        { return m_errorMsg; }

public slots:

private:
    QString m_errorMsg;
    QUrl m_filePath;
    bool created = false;
    bool useWrapper = false;
    QQmlApplicationEngine* m_engine;
    QQuickWindow* m_currentWindow;
    QQuickItem* m_errorWrapper;
    FileWatcher* m_fileWatcher;

    void loadQml();
    void startWrapper();


signals:
    void qmlLoaded();
    void errorMsgChanged(QString &error);


public slots:
    void handleQmlErrors(const QList<QQmlError> &qmlErrors);



};

#endif // LIVELOADER_H
