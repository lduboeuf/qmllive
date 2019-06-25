#ifndef LIVELOADER_H
#define LIVELOADER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "filewatcher.h"

class LiveLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString errorMsg READ errorMsg)
public:
    explicit LiveLoader( QQmlApplicationEngine *engine,FileWatcher *fileWatcher, QObject *parent = nullptr);
    Q_INVOKABLE void setFile(const QString &path);

    QString errorMsg() const
        { return m_errorMsg; }

public slots:

private:
    QString m_errorMsg;
    QUrl m_filePath;
    bool created = false;
    bool useWrapper = false;
    QQmlApplicationEngine* m_engine;
    FileWatcher* m_fileWatcher;


    void onLoadedQml(QObject *object, const QUrl &url);
    void loadQml();
    void startWrapper();


signals:
    void qmlLoaded();
    void errorMsgChanged(QString errorMsg);


public slots:
    void handleQmlErrors(const QList<QQmlError> &qmlErrors);



};

#endif // LIVELOADER_H
