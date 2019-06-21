#ifndef LIVELOADER_H
#define LIVELOADER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "filewatcher.h"

class LiveLoader : public QObject
{
    Q_OBJECT
public:
    explicit LiveLoader( QQmlApplicationEngine *engine,FileWatcher *fileWatcher, QObject *parent = nullptr);
    Q_INVOKABLE void setFile(const QString &path);
    //void setEngine(QQmlApplicationEngine *engine) { m_engine = engine; }

public slots:

private:

    void update();
    QUrl m_filePath;
    bool created = false;
    QQmlApplicationEngine* m_engine;
    FileWatcher* m_fileWatcher;


signals:
    void notify();


public slots:
};

#endif // LIVELOADER_H
