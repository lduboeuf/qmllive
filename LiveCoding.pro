TEMPLATE = app
TARGET = livecoding

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    filewatcher.cpp \
    liveloader.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    filewatcher.h \
    liveloader.h

UBUNTU_TOUCH {
    message("building for Ubuntu Touch")

    DEFINES += Q_OS_UBUNTU_TOUCH


    # figure out the current build architecture
    CLICK_ARCH=$$system(dpkg-architecture -qDEB_HOST_ARCH)

    # substitute the architecture in the manifest file
    QMAKE_SUBSTITUTES += $$PWD/packaging/ubuntu_touch/manifest.json.in
    manifest.files = packaging/ubuntu_touch/manifest.json
    manifest.path = /
    INSTALLS += manifest


    target.path = /
    click_files.path = /
    click_files.files = $$PWD/packaging/ubuntu_touch/*

    INSTALLS+=click_files
}
