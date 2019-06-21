#include <QDebug>
#include <QString>

#include "filewatcher.h"

/**
 * @brief FileWatcher::FileWatcher
 *   This class can monitor file changes in a directory and calls a callback
 *   in response
 * @param callback
 *   The callback function to be executed whenever changes are detected
 */
FileWatcher::FileWatcher(QObject *parent) : QObject(parent)
{
    QObject::connect(&mWatcher, &QFileSystemWatcher::directoryChanged, this, &FileWatcher::directoryChanged);
    QObject::connect(&mWatcher, &QFileSystemWatcher::fileChanged, this, &FileWatcher::fileChanged);

    // configure the timer to signal the changes to the callback
    mTimer.setInterval(100);
    mTimer.setSingleShot(true);

    // configure directory filters
    mDir.setFilter(QDir::Files | QDir::NoSymLinks);
    mDir.setNameFilters(QStringList() << "*.qml");


    // connect timer to callback function
    QObject::connect(&mTimer, &QTimer::timeout, [&](){
        emit qmlChanged();

    });
}

/**
 * @brief FileWatcher::addPaths
 *   Adds the paths of the files to be monitored in the current directory
 */
void FileWatcher::addPaths()
{
    QStringList entries = mDir.entryList();
    for (int i=0; i<entries.size(); i++)
    {
        entries[i].prepend(mDir.absolutePath() + "/");
    }

    mWatcher.addPaths(entries);
    //mTimer.start();
}

/**
 * @brief FileWatcher::setDirectory
 *   Set the directory to watch for changes
 * @param path
 *   Directory path
 */
void FileWatcher::setDirectory(const QString &path)
{
    qDebug() << "added directory:" << path;
    if (!mWatcher.addPath(path))
    {
        qWarning() << "Could not add path: " << path;
    }
    else
    {
        mDir.setPath(path);
        addPaths();
    }
    emit qmlChanged();
}



/**
 * @brief FileWatcher::directoryChanged
 *   Slot connected to the directoryChanged signal from internal QFileSystemWatcher
 * @param path
 *   Path of the directory where the change was detected
 */
void FileWatcher::directoryChanged(const QString &path)
{
    Q_UNUSED(path);
    addPaths();

}

QString FileWatcher::directory() const {
    return mDir.path();
}


/**
 * @brief FileWatcher::fileChanged
 *   Slot connected to the fileChanged signal from internal QFileSystemWatcher
 * @param path
 *   Path of the file where the change was detected
 */
void FileWatcher::fileChanged(const QString &path)
{
    qDebug() << "changed in dir:" << path;
    Q_UNUSED(path);
    if (!mTimer.isActive()) { //prevent called twice ( on UT )
        mTimer.start();
    }

}
